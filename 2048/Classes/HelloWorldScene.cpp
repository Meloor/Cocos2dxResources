/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "CardSprite.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
	auto scene = Scene::create();
	auto layer = HelloWorld::create();
	scene->addChild(layer);
    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	if (!Layer::init())
	{
		return false;
	}
	score = 0;//初始化游戏分数
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//添加背景
	auto  layerColorBG = LayerColor::create(Color4B(180, 170, 160, 255));
	this->addChild(layerColorBG);
	//中文分数标签
	auto dic = Dictionary::createWithContentsOfFile("fonts/2048.xml");
	auto str = (String*)(dic->objectForKey("score"));
	scoreLabel = Label::createWithTTF(str->getCString(), "fonts/STLITI.ttf", 60);
	scoreLabel->setPosition(Vec2(visibleSize.width / 5, visibleSize.height - 60));
	this->addChild(scoreLabel);
	//分数值标签：
	scoreValueLabel = Label::createWithTTF(
		String::createWithFormat("%d",score)->getCString(), "fonts/Marker Felt.ttf", 60);
	scoreValueLabel->setPosition(Vec2(visibleSize.width*2/ 5, visibleSize.height - 60));
	scoreValueLabel->setAnchorPoint(Vec2(0, 0.5));
	this->addChild(scoreValueLabel);
	//添加触摸绑定事件
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	//添加卡片
	createCards(visibleSize);
	//生成随机数
	autoCreateCardNumber();
	autoCreateCardNumber();
}
void  HelloWorld::createCards(Size size) {
	//求出单元格高度
	float lon = (size.width - 20) / 4;//左右方向多出20像素
	//布局好card后剩余的高度
	float rest_height = size.height - lon * 4;
	//int arr[4][4] = {{2,2,4,8},
	//				{ 0,2,4,8 },
	//				{ 0,2,4,8 },
	//				{ 2,4,2,2 }};
	int arr[4][4] = {0};
	//4*4的单元格,（x,y）索引card,同opengl坐标系
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			auto card = CardSprite::createCardSprite(2 * x, lon, lon);
			//左边留出10像素(加上card边界留了7.5,左边总共留了17.5像素)，y轴方向上的空白上下各一半
			card->setNumber(arr[y][x]);
			//card->setPosition(Vec2(lon*x + 10, lon*y - rest_height / 2 ));//(0,0)在左下角
			card->setPosition(Vec2(lon*x + 10, size.height-lon*y - rest_height / 2-lon));//(0,0)在左上角
			this->addChild(card);
			//添加卡片到二维数组中
			cardArr[y][x] = card;//保证遍历x就是遍历左右方向的格子就行。
		}
	}
}

bool  HelloWorld::onTouchBegan(Touch *touch, Event *unused_event) {
	beginP = touch->getLocation();
	return true;
}
void  HelloWorld::onTouchEnded(Touch *touch, Event *unused_event) {
	endP = touch->getLocation();

	Vec2 chaP = beginP - endP;//起点减去终点
	float chaX = chaP.x;
	float chaY = chaP.y;
	float minDistance = 5;//最小距离，灵敏度

	//如果x方向上的移动距离大于y方向上的移动距离，则是左右移动，否则上下移动
	if (abs(chaX) > abs(chaY)) {
		if (chaX  > minDistance) {//begin在end右边，向左滑
			if (doLeft()) {//return了true表示发生了移动或者合并(表示还有空格)，这时才要生成随机数
				autoCreateCardNumber();
				doCheckGameOver();
			}
		}
		else if(chaX < -minDistance){
			if(doRight()){
				autoCreateCardNumber();
				doCheckGameOver();
			}
		}
	}
	else {//opengl坐标系原点在左下角,越往上坐标越大
		if (chaY  > minDistance) {//first在end的上边，向下滑
			if (doDown()) {
				autoCreateCardNumber();
				doCheckGameOver();
			}
				
		}
		else if(chaY < -minDistance){
			if(doUp()){
				autoCreateCardNumber();
				doCheckGameOver();
			}
		}
	}
}

bool  HelloWorld::doLeft() {
	log("go left");
	/*
	理一下游戏的逻辑，往左划时
	step1:所有的card都会往左移（跳过值为0的card),在左边互相紧靠。
	step2:肯定是左边的先合并，如果有相同的就合并，合并后又会有空card,空card后面的card要填补空card的位置。
	先移动，再合并:
	4202->4220->4400->8000, 移动阶段：从左往右遍历，如果格子非空且其左边为空，就把格子向左移动一个
	4002->移动阶段：
	0204->移动阶段：从左往右遍历，如果格子a为空，那么从这个格子往右找，直到找到一个非空的格子b，然后a=b,b=0，继续往右找下一个空的格子。
	4220->合并阶段：此时所有格子都在左边相邻，从左往右遍历，有一对相同的就合并->4400,之后可能在左边会出现新的可合并格子对，所以需要重新从左边找起
	4220->4400->8000
	4420->8200
	4422->8220->8400->
	2222->4220->4400->8000
	2222合并->4022移动->4220合并->4400合并->8000, 合并之后不需要立马移动，因为后面还可能出现可合并对
	2222合并->4022合并->4040移动->4400合并->8000
	可以这样，合并时忽略空格，直到没有可合并的才做最后的移动
	
	
	*/
	int merge_num = 0;//合并次数
	int move_num = 0;//移动次数
	for (int y = 0; y < 4; y++) {//遍历每一行
		/*
		x = 0:2222->4022	2248->4048->8008->16000
		x = 2:4022->4040	
		x = 0:8000	
		*/	
		bool isdo = false;//一次滑动最多合并一次	
		for (int x = 0; x < 4; x++) {
			if (cardArr[y][x]->getNumber() > 0) {//非空格子x
				for (int nx = x + 1; nx < 4; nx++) {
					if (cardArr[y][nx] != 0) {//找下一个非空格子
						if (cardArr[y][x]->getNumber() == cardArr[y][nx]->getNumber()) {//相等
							//进行合并操作
							cardArr[y][x]->setNumber(cardArr[y][x]->getNumber() * 2);
							cardArr[y][nx]->setNumber(0);
							//增加分数
							score += cardArr[y][x]->getNumber();
							scoreValueLabel->setString(String::createWithFormat("%d", score)->getCString());

							isdo = true;
							merge_num++;
						}
						else {//和它紧靠的非空格子如果和它不想等就不能合并
							break;
						}
					}

					
				}
			}
		}
		//移动
		/*	从左往右遍历，如果格子a为空，那么从这个格子往右找，直到找到一个非空的格子b，
			然后a = b, b = 0，继续往右找下一个空的格子。
		*/
		for (int x = 0; x < 4; x++) {
			if (cardArr[y][x]->getNumber()==0) {//找一个空格
				for (int nx = x + 1; nx < 4; nx++) {
					if (cardArr[y][nx]->getNumber() > 0) {//找一个非空
						cardArr[y][x]->setNumber(cardArr[y][nx]->getNumber());
						cardArr[y][nx]->setNumber(0);
						move_num++;
						break;//空格被填充后直接break
					}
				}
			}
		}
	}
	return merge_num>0||move_num>0;//合并或移动过就返回true
}
bool  HelloWorld::doRight() {
	log("go right");
	int merge_num = 0;
	int move_num = 0;
	for (int y = 0; y < 4; y++) {//遍历每一行
		//合并
		bool isdo = false;
		for (int x = 3; x >=0; x--) {
			if (cardArr[y][x]->getNumber() > 0) {//非空格子x
				for (int nx = x - 1; nx>=0; nx--) {//找下一个非空且和x相同的格子
					if (/*cardArr[y][nx]!=0&&*/cardArr[y][x]->getNumber() == cardArr[y][nx]->getNumber()) {
						//进行合并操作
						cardArr[y][x]->setNumber(cardArr[y][x]->getNumber() * 2);
						cardArr[y][nx]->setNumber(0);
						//增加分数
						score += cardArr[y][x]->getNumber();
						scoreValueLabel->setString(String::createWithFormat("%d", score)->getCString());

						isdo = true;
						merge_num++;
					}
				}
			}
		}
		//移动
		for (int x = 3; x >=0; x--) {
			if (cardArr[y][x]->getNumber() == 0) {//找一个空格
				for (int nx = x - 1; nx >=0; nx--) {
					if (cardArr[y][nx]->getNumber() > 0) {//找一个非空
						cardArr[y][x]->setNumber(cardArr[y][nx]->getNumber());
						cardArr[y][nx]->setNumber(0);
						move_num++;
						break;//空格被填充后直接break
					}
				}
			}
		}
	}
	return merge_num>0 || move_num>0;
}
bool  HelloWorld::doUp() {
	log("go up");
	int merge_num = 0;
	int move_num = 0;
	for (int x = 0; x < 4; x++) {//遍历每一列
		/*合并*/
		bool isdo = false;

		for (int y = 0; y < 4; y++) {
			if (cardArr[y][x]->getNumber() > 0) {//非空格子y
				for (int ny = y + 1; ny < 4; ny++) {//找下一个非空且和y相同的格子
					if (/*cardArr[y][nx]!=0&&*/cardArr[y][x]->getNumber() == cardArr[ny][x]->getNumber()) {
						//进行合并操作
						cardArr[y][x]->setNumber(cardArr[y][x]->getNumber() * 2);
						cardArr[ny][x]->setNumber(0);
						//增加分数
						score += cardArr[y][x]->getNumber();
						scoreValueLabel->setString(String::createWithFormat("%d", score)->getCString());

						isdo = true;
						merge_num++;
					}
				}
			}
		}

		/*移动*/
		for (int y = 0; y < 4; y++) {
			if (cardArr[y][x]->getNumber() == 0) {//找一个空格
				for (int ny = y + 1; ny < 4; ny++) {
					if (cardArr[ny][x]->getNumber() > 0) {//找一个非空
						cardArr[y][x]->setNumber(cardArr[ny][x]->getNumber());
						cardArr[ny][x]->setNumber(0);
						move_num++;
						break;//空格被填充后直接break
					}
				}
			}
		}
	}
	return merge_num>0 || move_num>0;
}
bool  HelloWorld::doDown() {
	log("go down");
	int merge_num = 0;
	int move_num = 0;
	for (int x = 0; x < 4; x++) {//遍历每一列
		//合并
		bool isdo = false;
		for (int y = 3; y >=0; y--) {
			if (cardArr[y][x]->getNumber() > 0) {//非空格子y
				for (int ny = y - 1; ny >=0; ny--) {//找下一个非空且和y相同的格子
					if (/*cardArr[y][nx]!=0&&*/cardArr[y][x]->getNumber() == cardArr[ny][x]->getNumber()) {
						//进行合并操作
						cardArr[y][x]->setNumber(cardArr[y][x]->getNumber() * 2);
						cardArr[ny][x]->setNumber(0);
						//增加分数
						score += cardArr[y][x]->getNumber();
						scoreValueLabel->setString(String::createWithFormat("%d", score)->getCString());

						isdo = true;
						merge_num++;
					}
				}
			}
		}
		//移动
		for (int y = 3;y>=0; y--) {
			if (cardArr[y][x]->getNumber() == 0) {//找一个空格
				for (int ny = y-1; ny >=0; ny--) {
					if (cardArr[ny][x]->getNumber() > 0) {//找一个非空
						cardArr[y][x]->setNumber(cardArr[ny][x]->getNumber());
						cardArr[ny][x]->setNumber(0);
						move_num++;
						break;//空格被填充后直接break
					}
				}
			}
		}
	}
	return merge_num>0||move_num>0;
}
//如果格子被占满了还生成就会陷入死循环，所以应该在合并过或移动过（表示有空格）后才能随机生成数字
void HelloWorld::autoCreateCardNumber()
{
	int y, x;
	do {
		y = CCRANDOM_0_1() * 4;//[0,1]*4 ->[0,4],
		x = CCRANDOM_0_1() * 4;
		if (y == 4)y = 3;//如果刚好等于4就会出错
		if (x == 4)x = 3;
	} while (cardArr[y][x]->getNumber() > 0);//如果改格子非空就继续随机下一个点

	cardArr[y][x]->setNumber(CCRANDOM_0_1() * 10 < 1 ? 4 : 2);//4的概率约10%
}

void HelloWorld::doCheckGameOver()
{
	bool isGameOver = true;
	//判断每个格子，还有空格，游戏可以继续
	//或者可以和其周边的格子合并，可以，那么游戏可以继续
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			if ((cardArr[y][x]->getNumber() == 0) ||
				(y-1 >= 0 && (cardArr[y][x]->getNumber() == cardArr[y - 1][x]->getNumber())) ||
				(y+1 <= 3 && (cardArr[y][x]->getNumber() == cardArr[y + 1][x]->getNumber())) ||
				(x-1 >= 0 && (cardArr[y][x]->getNumber() == cardArr[y][x - 1]->getNumber())) ||
				(x+1 <= 3 && (cardArr[y][x]->getNumber() == cardArr[y][x + 1]->getNumber()))
				) {
				isGameOver = false;
				break;
			}			
		}
	}
	if (isGameOver) {//如果游戏结束，就重新加载场景
		auto scene = HelloWorld::createScene();
		auto tsc = TransitionFade::create(1, scene);
		Director::getInstance()->replaceScene(tsc);
	}
}

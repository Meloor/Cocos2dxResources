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

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//添加背景
	auto  layerColorBG = LayerColor::create(Color4B(180, 170, 160, 255));
	this->addChild(layerColorBG);
	//添加触摸绑定事件
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	//添加卡片
	createCards(visibleSize);
}
void  HelloWorld::createCards(Size size) {
	//求出单元格高度
	float lon = (size.width - 20) / 4;//左右方向多出20像素
	//布局好card后剩余的高度
	float rest_height = size.height - lon * 4;
	int arr[4][4] = {{2,2,4,8},
					{ 0,2,4,8 },
					{ 0,2,4,8 },
					{ 0,0,4,8 }};
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
			cardArr[x][y] = card;//保证遍历x就是遍历左右方向的格子就行。
		}
	}
}

bool  HelloWorld::onTouchBegan(Touch *touch, Event *unused_event) {
	Point touchP0 = touch->getLocation();
	firstX = touchP0.x;
	firstY = touchP0.y;
	return true;
}
void  HelloWorld::onTouchEnded(Touch *touch, Event *unused_event) {
	Point touchP0 = touch->getLocation();
	endX = firstX - touchP0.x;
	endY = firstY - touchP0.y;
	
	//如果x方向上的移动距离大于y方向上的移动距离，则是左右移动，否则上下移动
	if (abs(endX) > abs(endY)) {
		if (endX + 5 > 0) {//first在end右边，向左滑
			doLeft();
		}
		else {
			doRight();
		}
	}
	else {//opengl坐标系原点在左下角,越往上坐标越大
		if (endY + 5 > 0) {//first在end的上边，向下滑，这里为什么要+5？？？
			doDown();
		}
		else {
			doUp();
		}
	}

}

bool  HelloWorld::doLeft() {
	log("go left");
	/*
	理一下游戏的逻辑，往左划时
	step1:所有的card都会往左移（跳过值为0的card),在左边互相紧靠。
	step2:肯定是左边的先合并，如果有相同的就合并，合并后又会有空card,空card后面的card要填补空card的位置。
	*/
	bool isdo = false;
	for (int y = 0; y < 4; y++) {
		//bool flag = true;
		//while (flag) {
		//	int x_num = 4;
		//	for (int x = 0; x < x_num; x++) {
		//		//如果这个格子为空，后面的都往前移
		//		if (cardArr[x][y]->getNumber() == 0) {
		//			for (int x1 = x + 1; x1 < x_num; x1++) 
		//				cardArr[x1 - 1][y]->setNumber(cardArr[x1][y]->getNumber());		
		//			cardArr[3][y]->setNumber(0);
		//			x_num--;//移动后，最后一个是空，后面无需再判断了
		//		}
		//		//如果格子非空，那么判断合并，用if而不用else是因为移动后可能非空
		//		if(cardArr[x][y]->getNumber() != 0){
		//			for (int x1 = x + 1; x1 < x_num; x1++) {
		//				if (cardArr[x][y]->getNumber() == cardArr[x1][y]->getNumber()) {
		//					cardArr[x][y]->setNumber(cardArr[x][y]->getNumber() * 2);
		//					cardArr[x1][y]->setNumber(0);
		//				}
		//				else break;//不相等就啥也不做
		//			}
		//		}
		//	}
		//}


		for (int x = 0; x < 4; x++) {//合并到x
			//遍历到x,card从右往前移，与x最近的(x+1)先和x进行迭代判断
			//判断到底是要进行迭代还是清空
			for (int x1 = x + 1; x1 < 4; x1++) {//x1是被合并的格子
				if (cardArr[x1][y]->getNumber()>0) {//x1非空
					//x为空，x1移动到x的位置，x1原位置置空
					//例子，x=0,x1=1,[0,2,2,2],向左滑动后[2,0,2,2],x1=2,[4,0,0,2],x1=3,[4,0,0,2]
					//x为空只会在里层for中出现一次，第一次过后就会被设置为非空。
					if (cardArr[x][y]->getNumber() <= 0) {
						cardArr[x][y]->setNumber(cardArr[x1][y]->getNumber());
						cardArr[x1][y]->setNumber(0);
						//x--;//然后下一个x1判断时会读取cardArr[-1][y]产生中断，如[0,2,4,8]
						//log("x=%d", x);		
						isdo = true;
					}//x非空，判断是否与x相同,相同则合并到x
					else if(cardArr[x][y]->getNumber() == cardArr[x1][y]->getNumber()){
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber()*2);
						//合并到x后，x1置为空，然后下一个x1与x进行判断，如果相同会继续合并
						//如[2,2,4,4]合并的最终结果为[8,0,0,4]
						cardArr[x1][y]->setNumber(0);
						isdo = true;
					}//x非空且和x1不同，什么都不做，x1停在原处
				}//x1为空什么都不做
			}
		}
	}
	return isdo;
}
bool  HelloWorld::doRight() {
	log("go right");
	return true;
}
bool  HelloWorld::doUp() {
	log("go up");
	return true;
}
bool  HelloWorld::doDown() {
	log("go down");
	return true;
}
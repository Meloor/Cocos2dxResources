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

#include "Scene3.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* Scene3::createScene()
{
	auto scene = Scene::create();
	auto layer = Scene3::create();
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
bool Scene3::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	setTouchEnabled(true);//开启层触摸事件
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);//单点触摸

												  //中文标题标签
	auto dic = Dictionary::createWithContentsOfFile("fonts/test.xml");
	auto str_en = String::createWithFormat("ch%d", 3);
	auto str_ch = (String*)(dic->objectForKey(str_en->getCString()));
	auto label = Label::create();
	label->setString(str_ch->getCString());
	label->setSystemFontSize(40);
	label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 100));
	this->addChild(label);

	//返回菜单
	MenuItemFont::setFontName("Arial");
	MenuItemFont::setFontSize(40);
	auto backItem = MenuItemFont::create("Back", CC_CALLBACK_1(Scene3::backMenuCallback, this));
	auto mn = Menu::create(backItem, NULL);
	mn->alignItemsVertically();
	mn->setPosition(Vec2(visibleSize.width - 70, 40));
	this->addChild(mn);

	initPhysics();
	scheduleUpdate();

	return true;
}
//游戏循环，代码固定
void Scene3::update(float dt)
{
	float timestep = 0.03f;//舍弃dt(不稳定)，设置了一个常量
	int32 velocityIterations = 8;//速度的迭代
	int32 positionIterations = 1;//位移的迭代

	world->Step(timestep, velocityIterations, positionIterations);
	//把物理世界中的所有物体取出来
	for (b2Body* b = world->GetBodyList(); b; b = b->GetNext()) {
		if (b->GetUserData() != nullptr) {
			auto sprite = (Sprite*)b->GetUserData();
			//物体与精灵位置同步
			sprite->setPosition(Vec2(b->GetPosition().x*
				PTM_RATIO, b->GetPosition().y*PTM_RATIO));
			//物体与精灵的旋转同步，物理世界的物体育精灵的旋转方向是相反的。
			//弧度转成角度
			sprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
		}
	}
}

void Scene3::initPhysics()
{
	Size s = Director::getInstance()->getVisibleSize();
	b2Vec2 gravity;//设置重力
	gravity.Set(0.0f, -10.0f);

	world = new b2World(gravity);//创建物理世界
								 //允许物体休眠，物体静止状态时，休眠，需要碰撞检测等时
								 //才唤醒，以便减少绘制的次数
	world->SetAllowSleeping(true);
	world->SetContinuousPhysics(true);//开启连续物理测试


	b2BodyDef gBodyDef;//指定物理世界边界
	gBodyDef.position.Set(0, 0);//创建地面物体结构体
	b2Body* gBody = world->CreateBody(&gBodyDef);//创建地面物体
	b2EdgeShape gBox;//定义个有边的形状

					 //定义底部，物理世界为米，因此需要进行转换
	gBox.Set(b2Vec2(0, 0), b2Vec2(s.width / PTM_RATIO, 0));
	//使用夹 具固定形状到物体，参数1是形状，参数2是密度，
	//下边无需考虑重量，所以设置为0;
	gBody->CreateFixture(&gBox, 0);

	//定义项部
	gBox.Set(b2Vec2(0, s.height / PTM_RATIO), b2Vec2(s.width / PTM_RATIO, s.height / PTM_RATIO));
	gBody->CreateFixture(&gBox, 0);
	//左边
	gBox.Set(b2Vec2(0, 0), b2Vec2(0, s.height / PTM_RATIO));
	gBody->CreateFixture(&gBox, 0);
	//右边
	gBox.Set(b2Vec2(s.width / PTM_RATIO, 0), b2Vec2(s.width / PTM_RATIO, s.height / PTM_RATIO));
	gBody->CreateFixture(&gBox, 0);
}

bool Scene3::onTouchBegan(Touch * touch, Event * event)
{
	Vec2 p2 = touch->getLocation();//获取触摸点的opengl坐标
	this->addNewSpriteAtPos(p2);
	return true;
}

void Scene3::addNewSpriteAtPos(Vec2 pos)
{
	log("create sprite");
	//创建精灵A
	auto spA = Sprite::create("boxA2.png");
	spA->setPosition(pos);
	this->addChild(spA);
	//动态物体定义A
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;//结构体类型为动态类型
	bodyDef.position.Set(pos.x / PTM_RATIO, pos.y/PTM_RATIO);
	b2Body* bodyA = world->CreateBody(&bodyDef);
	bodyA->SetUserData(spA);//绑定精灵
	//创建精灵B
	auto spB = Sprite::create("boxB2.png");
	spB->setPosition(pos+Vec2(100,-100));
	this->addChild(spB);

	//动态物体定义B
	bodyDef.type = b2_dynamicBody;//结构体类型为动态类型
	Vec2 posB = spB->getPosition();
	bodyDef.position.Set(posB.x / PTM_RATIO, posB.y/PTM_RATIO);
	b2Body* bodyB = world->CreateBody(&bodyDef);
	bodyB->SetUserData(spB);//绑定精灵


	//形状
	b2PolygonShape dynamicBox;//2m的盒子
	dynamicBox.SetAsBox(1, 1);//边长的一半是1m

	//动态夹具定义
	b2FixtureDef FixtureDef;
	FixtureDef.shape = &dynamicBox;//设置夹具形状
	FixtureDef.density = 1.0f;//设置密度
	FixtureDef.friction = 0.3f;//摩擦系数

	//将夹具固定到物体上
	bodyA->CreateFixture(&FixtureDef);
	bodyB->CreateFixture(&FixtureDef);

	//距离关节定义
	b2DistanceJointDef jointDef;
	jointDef.Initialize(bodyA, bodyB, bodyA->GetWorldCenter(), bodyB->GetWorldCenter());
	jointDef.collideConnected = true;

	bodyA->GetWorld()->CreateJoint(&jointDef);//bodyA,bodB都可以getWorld
}

void Scene3::nextMenuCallback(Ref* pSender) {

}

void Scene3::backMenuCallback(Ref * pSender)
{
	Director::getInstance()->popScene();
}

Scene3::~Scene3()
{
	//delete(world);//容易造成野指针
	CC_SAFE_DELETE(world);
}





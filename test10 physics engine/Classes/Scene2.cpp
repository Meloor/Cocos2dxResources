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

#include "Scene2.h"
#include "SimpleAudioEngine.h"
#define TAG 100
USING_NS_CC;

Scene* Scene2::createScene()
{
	//auto scene = Scene::create();
	auto scene = Scene::createWithPhysics();
	auto layer = Scene2::create();
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
bool Scene2::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin =  Director::getInstance()->getVisibleOrigin();

	setTouchEnabled(true);//开启层触摸事件
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);//单点触摸

	//返回菜单
	MenuItemFont::setFontName("Arial");
	MenuItemFont::setFontSize(40);
	auto backItem = MenuItemFont::create("Back",CC_CALLBACK_1(Scene2::backMenuCallback,this));
	auto mn = Menu::create(backItem, NULL);
	mn->alignItemsVertically();
	mn->setPosition(Vec2(visibleSize.width - 70, 40));
	this->addChild(mn);
	//标题标签
	auto dic = Dictionary::createWithContentsOfFile("fonts/test.xml");
	auto str_en = String::createWithFormat("ch%d", 2);
	auto str_ch = (String*)(dic->objectForKey(str_en->getCString()));
	auto label = Label::create();
	label->setString(str_ch->getCString());
	label->setSystemFontSize(40);
	label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 100));
	this->addChild(label);

	//物理世界也是一个物体，第一个参数是大小，第二个参数是材质，第三个是厚度，默认为1.0f
	auto body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 0.5);
	auto edgeNode = Node::create();//创建一个游戏中的节点
	edgeNode->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	//通过函数将物理世界的形状与游戏中的节点关联起来，同步起来
	//不需要使用update游戏循环来设置角度和速度等，因为使用了底层封装的物理引擎API
	edgeNode->setPhysicsBody(body);
	//edgeNode->setTag(-1);
	this->addChild(edgeNode);

	return true;
}

void Scene2::onEnter()
{
	Layer::onEnter();
	lis = EventListenerPhysicsContact::create();
	lis->onContactBegin = [](PhysicsContact& contact) {
		log("onContactBegin");
		auto spA = (Sprite*)contact.getShapeA()->getBody()->getNode();
		auto spB = (Sprite*)contact.getShapeB()->getBody()->getNode();
		//if (spA && spA->getTag() == TAG && spB && spB->getTag == TAG) {
		//if (spA&&spA->getTag() >= 0 && spB&&spB->getTag() >= 0) {
		if (spA && spB) {//只要和其他物体发生了碰撞，tag的值就+1，tag值大于0就是绿色，等于0就是白色
			spA->setTag(spA->getTag() + 1);
			spB->setTag(spB->getTag() + 1);
			if(spA->getTag()>0)spA->setColor(Color3B::GREEN);
			if (spA->getTag()>0)spB->setColor(Color3B::GREEN);
		}
		return true;
	};
	lis->onContactPreSolve = [](PhysicsContact& contact, PhysicsContactPreSolve& solve) {
		log("onContactPreSolve");
		return true;
	};
	//注意，此函数无返回值
	lis->onContactPostSolve = [](PhysicsContact& contact,const PhysicsContactPostSolve& solve) {
		log("onContactPostSolve");
	};
	lis->onContactSeparate = [](PhysicsContact& contact) {
		log("onContactSeparate");
		auto spA = (Sprite*)contact.getShapeA()->getBody()->getNode();
		auto spB = (Sprite*)contact.getShapeB()->getBody()->getNode();
		//if (spA&&spA->getTag() == TAG && spB&&spB->getTag == TAG) {
		//if (spA&&spA->getTag()>=0 && spB&&spB->getTag() >= 0) {
		if (spA && spB){
			spA->setTag(spA->getTag() - 1);
			spB->setTag(spB->getTag() - 1);
			if (spA->getTag()<=0)spA->setColor(Color3B::WHITE);
			if (spB->getTag()<=0)spB->setColor(Color3B::WHITE);
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(lis,1);
}

void Scene2::onExit()
{
	Layer::onExit();
	Director::getInstance()->getEventDispatcher()->removeEventListener(lis);
}

bool Scene2::onTouchBegan(Touch * touch, Event * event)
{
	Vec2 p2 = touch->getLocation();//获取触摸点的opengl坐标
	this->addNewSpriteAtPos(p2);
	return true;
}

void Scene2::addNewSpriteAtPos(Vec2 pos)
{
	auto sp = Sprite::create("BoxA2.png");
	sp->setTag(0);//把标签放进去为了判断是否是该物体碰撞??好像没有关系
	auto body = PhysicsBody::createBox(sp->getContentSize());

	//开启碰撞检测必须设置Bitmask掩码
	//是否进行碰撞检测要看Bitmask掩码，掩码进行“位与”运算 ，如果结果是非零
	//则两个物体可以碰撞，否则不能碰撞，默认值是0x1
	body->setContactTestBitmask(0x1);//a,b物体是同一种，所以位与结果不为零

	sp->setPhysicsBody(body);
	sp->setPosition(pos);
	this->addChild(sp);
}

void Scene2::nextMenuCallback(Ref* pSender){
	
}

void Scene2::backMenuCallback(Ref * pSender)
{
	Director::getInstance()->popScene();
}





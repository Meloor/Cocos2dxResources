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
/*

	ActionInstant
	ActionInterval
	ActionCombination
	ActionSpeedControl
	ActionFunctionCall
	GridAction
	Animation

*/
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "ActionInstantTestScene.h"
#include "ActionIntervalTestScene.h"
#include "ActionCombinationTestScene.h"
#include "ActionSpeedControlTestScene.h"
#include "ActionFunctionCallTestScene.h"
#include "GridActionTestScene.h"
#include "AnimationTestScene.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
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
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto label = Label::createWithTTF("--Actions--", "fonts/arial.ttf", 48);
	label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - label->getContentSize().height*0.5));
	this->addChild(label);
	
	MenuItemFont::setFontName("fonts/arial.ttf");//是系统字体还是自带字体
	MenuItemFont::setFontSize(44);
	MenuItemFont *item1 = MenuItemFont::create("ActionInstant",
		CC_CALLBACK_1(HelloWorld::ActionInstantCallback, this));
	MenuItemFont *item2 = MenuItemFont::create("ActionInterval",
		CC_CALLBACK_1(HelloWorld::ActionIntervalCallback, this));
	MenuItemFont *item3 = MenuItemFont::create("ActionCombination",
		CC_CALLBACK_1(HelloWorld::ActionCombinationCallback, this));
	MenuItemFont *item4 = MenuItemFont::create("ActionSpeedControl",
		CC_CALLBACK_1(HelloWorld::ActionSpeedControlCallback, this));
	MenuItemFont *item5 = MenuItemFont::create("ActionFunctionCall",
		CC_CALLBACK_1(HelloWorld::ActionFunctionCallCallback, this));
	MenuItemFont *item6 = MenuItemFont::create("GridAction",
		CC_CALLBACK_1(HelloWorld::GridActionCallback, this));
	MenuItemFont *item7 = MenuItemFont::create("Animation",
		CC_CALLBACK_1(HelloWorld::AnimationCallback, this));

	auto mn = Menu::create(item1, item2,item3,item4,item5,item6,item7, NULL);
	mn->alignItemsVertically();//设置菜单项垂直对齐
	mn->alignItemsVerticallyWithPadding(30);//设置间隔宽度
	this->addChild(mn, 1);
    return true;
}
void HelloWorld::ActionInstantCallback(Ref* pSender) {
	auto sc = ActionInstantTest::createScene();
	auto reScene = TransitionJumpZoom::create(1.0f, sc);
	//Director::getInstance()->replaceScene(reScene);//replace
	Director::getInstance()->pushScene(reScene);//push
}
void HelloWorld::ActionIntervalCallback(Ref* pSender) {
	auto sc = ActionIntervalTest::createScene();
	auto reScene = TransitionJumpZoom::create(1.0f, sc);
	//Director::getInstance()->replaceScene(reScene);//replace
	Director::getInstance()->pushScene(reScene);//push
}
void HelloWorld::ActionCombinationCallback(Ref* pSender) {
	auto sc = ActionCombinationTest::createScene();
	auto reScene = TransitionJumpZoom::create(1.0f, sc);
	//Director::getInstance()->replaceScene(reScene);//replace
	Director::getInstance()->pushScene(reScene);//push
}
void HelloWorld::ActionSpeedControlCallback(Ref* pSender) {
	auto sc = ActionSpeedControlTest::createScene();
	auto reScene = TransitionJumpZoom::create(1.0f, sc);
	//Director::getInstance()->replaceScene(reScene);//replace
	Director::getInstance()->pushScene(reScene);//push
}
void HelloWorld::ActionFunctionCallCallback(Ref* pSender) {
	auto sc = ActionFunctionCallTest::createScene();
	auto reScene = TransitionJumpZoom::create(1.0f, sc);
	//Director::getInstance()->replaceScene(reScene);//replace
	Director::getInstance()->pushScene(reScene);//push
}
void HelloWorld::GridActionCallback(Ref* pSender) {
	auto sc = GridActionTest::createScene();
	auto reScene = TransitionJumpZoom::create(1.0f, sc);
	//Director::getInstance()->replaceScene(reScene);//replace
	Director::getInstance()->pushScene(reScene);//push
}
void HelloWorld::AnimationCallback(Ref* pSender) {
	auto sc = AnimationTest::createScene();
	auto reScene = TransitionJumpZoom::create(1.0f, sc);
	//Director::getInstance()->replaceScene(reScene);//replace
	Director::getInstance()->pushScene(reScene);//push
}


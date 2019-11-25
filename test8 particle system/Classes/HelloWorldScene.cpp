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
#include "Scene1.h"
#include "Scene2.h"
#include "Scene3.h"
#include "Scene4.h"
#include "Scene5.h"
#include "SimpleAudioEngine.h"

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
	if (!Scene::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//4个场景，帧动画，打火机，内置粒子系统，使用代码，plist
	//读取xml文件
	auto dic = Dictionary::createWithContentsOfFile("fonts/cn.xml");
	String* str[5];
	for (int i = 0; i < 5; i++) {
		auto st = String::createWithFormat("scene%d", i+1);
		str[i] = (String*)(dic->objectForKey(st->getCString()));
	}
	MenuItemFont::setFontName("Arial");
	MenuItemFont::setFontSize(40);
	MenuItemFont *item1 = MenuItemFont::create(str[0]->getCString(),
		CC_CALLBACK_1(HelloWorld::menuItem1Callback, this));
	MenuItemFont *item2 = MenuItemFont::create(str[1]->getCString(),
		CC_CALLBACK_1(HelloWorld::menuItem2Callback, this));
	MenuItemFont *item3 = MenuItemFont::create(str[2]->getCString(),
		CC_CALLBACK_1(HelloWorld::menuItem3Callback, this));
	MenuItemFont *item4 = MenuItemFont::create(str[3]->getCString(),
		CC_CALLBACK_1(HelloWorld::menuItem4Callback, this));
	MenuItemFont *item5 = MenuItemFont::create(str[4]->getCString(),
		CC_CALLBACK_1(HelloWorld::menuItem4Callback, this));

	auto menu = Menu::create(item1, item2, item3, item4,item5, NULL);
	menu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	menu->alignItemsVertically();
	this->addChild(menu);

	return true;
}
void HelloWorld::menuItem1Callback(Ref* pSender) {
	auto sc = Scene1::createScene();
	auto reScene = TransitionJumpZoom::create(1.0f, sc);
	Director::getInstance()->pushScene(reScene);
}
void HelloWorld::menuItem2Callback(Ref* pSender) {
	auto sc = Scene2::createScene();
	auto reScene = TransitionJumpZoom::create(1.0f, sc);
	Director::getInstance()->pushScene(reScene);
}
void HelloWorld::menuItem3Callback(Ref* pSender) {
	auto sc = Scene3::createScene();
	auto reScene = TransitionJumpZoom::create(1.0f, sc);
	Director::getInstance()->pushScene(reScene);
}
void HelloWorld::menuItem4Callback(Ref* pSender) {
	auto sc = Scene4::createScene();
	auto reScene = TransitionJumpZoom::create(1.0f, sc);
	Director::getInstance()->pushScene(reScene);
}

void HelloWorld::menuItem5Callback(Ref* pSender) {
	auto sc = Scene5::createScene();
	auto reScene = TransitionJumpZoom::create(1.0f, sc);
	Director::getInstance()->pushScene(reScene);
}


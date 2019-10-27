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
#include "ActionFunctionCallTestScene.h"
#include "ActionFunctionCallTest2Scene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* ActionFunctionCallTest2::createScene()
{
    return ActionFunctionCallTest2::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in ActionFunctionCallTest2Scene.cpp\n");
}

// on "init" you need to initialize your instance
bool ActionFunctionCallTest2::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Vec2 center = Vec2(visibleSize.width / 2, visibleSize.height / 2);

	MenuItemImage * backMenuItem = MenuItemImage::create(
		"Back-up.png",
		"Back-down.png",
		CC_CALLBACK_1(ActionFunctionCallTest2::goBackCallback, this));
	auto backMenu = Menu::create(backMenuItem, NULL);
	backMenu->setAnchorPoint(Vec2(0.5f, 0.5f));
	backMenu->setPosition(Vec2(100, visibleSize.height - 50));
	this->addChild(backMenu);
	/******************************************************************/
	//背景
	auto bg = Sprite::create("Background800x480.png");
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(bg);
	//飞机
	plane = Sprite::create("Plane.png");
	plane->setPosition(center);
	this->addChild(plane);
	//go
	MenuItemImage * goMenuItem = MenuItemImage::create(
		"Go-up.png",
		"Go-down.png",
		CC_CALLBACK_1(ActionFunctionCallTest2::goCallback, this));
	auto goMenu = Menu::create(goMenuItem, NULL);
	goMenu->setAnchorPoint(Vec2(0.5f, 0.5f));
	goMenu->setPosition(Vec2(visibleSize.width/2, 50));
	this->addChild(goMenu);


	return true;
}


void ActionFunctionCallTest2::goBackCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
}
void ActionFunctionCallTest2::goCallback(Ref* pSender)
{
	log("go_layer tag = %d", this->getTag());
	switch (this->getTag())
	{
	case func:onCallFunc(this); break;
	case funcN:onCallFuncN(this); break;
	default:
		break;
	}
}
void ActionFunctionCallTest2::onCallFunc(Ref* pSender) {
	auto ac1 = MoveBy::create(2, Vec2(100, 100));
	auto ac2 = ((FiniteTimeAction*)ac1)->reverse();

	auto acf = CallFunc::create(CC_CALLBACK_0(ActionFunctionCallTest2::callBack1, this));
	auto seq = Sequence::create(ac1, acf, ac2, NULL);

	plane->runAction(Sequence::create(seq, NULL));
}
void ActionFunctionCallTest2::onCallFuncN(Ref* pSender) {
	auto ac1 = MoveBy::create(2, Vec2(100, 100));
	auto ac2 = ((FiniteTimeAction*)ac1)->reverse();

	auto acf = CallFuncN::create(CC_CALLBACK_1(ActionFunctionCallTest2::callBack2, this));
	auto seq = Sequence::create(ac1, acf, ac2, NULL);

	plane->runAction(Sequence::create(seq, NULL));
}
void ActionFunctionCallTest2::callBack1() {
	plane->runAction(TintBy::create(0.5, 255, 0, 255));
}
//它传的参数不是this（也就是这个场景)吗，为什么可以转换成sprite
void ActionFunctionCallTest2::callBack2(Ref* pSender) {
	Sprite *sp = (Sprite*)pSender;
	sp->runAction(TintBy::create(1, 255, 0, 255));
}

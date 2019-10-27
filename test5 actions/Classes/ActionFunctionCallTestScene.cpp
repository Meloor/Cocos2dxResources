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

Scene* ActionFunctionCallTest::createScene()
{
    return ActionFunctionCallTest::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in ActionFunctionCallTestScene.cpp\n");
}

// on "init" you need to initialize your instance
bool ActionFunctionCallTest::init()
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
	/*************************************************************/
	//±³¾°
	auto bg = Sprite::create("Background800x480.png");
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(bg);
	//·µ»Ø²Ëµ¥
	MenuItemImage * backMenuItem = MenuItemImage::create(
		"Back-up.png",
		"Back-down.png",
		CC_CALLBACK_1(ActionFunctionCallTest::goBackCallback, this));
	auto backMenu = Menu::create(backMenuItem, NULL);
	backMenu->setAnchorPoint(Vec2(0.5f, 0.5f));
	backMenu->setPosition(Vec2(100, visibleSize.height - 50));
	this->addChild(backMenu);
	/*************************************************************/

	//²Ëµ¥
	auto p1 = Label::createWithBMFont("fonts/fnt2.fnt", "CallFunc");
	auto p2 = Label::createWithBMFont("fonts/fnt2.fnt", "CallFuncN");


	auto m1 = MenuItemLabel::create(p1, CC_CALLBACK_1(ActionFunctionCallTest::goCallback, this));
	auto m2 = MenuItemLabel::create(p2, CC_CALLBACK_1(ActionFunctionCallTest::goCallback, this));

	m1->setTag(func);
	m2->setTag(funcN);


	auto mn = Menu::create(m1, m2, NULL);
	mn->setPosition(center);
	mn->alignItemsVertically();
	this->addChild(mn);
	return true;
}


void ActionFunctionCallTest::goBackCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
}
void ActionFunctionCallTest::goCallback(Ref* pSender)
{
	MenuItem *mitem = (MenuItem*)pSender;
	log("item tag = %d", mitem->getTag());

	auto sc = Scene::create();
	auto layer = ActionFunctionCallTest2::create();
	sc->addChild(layer);
	layer->setTag(mitem->getTag());

	auto reScene = TransitionJumpZoom::create(1.0f, sc);
	//Director::getInstance()->replaceScene(reScene);//replace
	Director::getInstance()->pushScene(reScene);//push
}



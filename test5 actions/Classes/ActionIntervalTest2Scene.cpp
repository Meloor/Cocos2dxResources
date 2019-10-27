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
#include "ActionIntervalTestScene.h"
#include "ActionIntervalTest2Scene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* ActionIntervalTest2::createScene()
{
    return ActionIntervalTest2::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in ActionIntervalTest2Scene.cpp\n");
}

// on "init" you need to initialize your instance
bool ActionIntervalTest2::init()
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
	//±³¾°
	auto bg = Sprite::create("Background (2).png");
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(bg);
	//·µ»Ø²Ëµ¥
	MenuItemImage * backMenuItem = MenuItemImage::create(
		"Back-up (2).png",
		"Back-down (2).png",
		CC_CALLBACK_1(ActionIntervalTest2::goBackCallback, this));
	auto backMenu = Menu::create(backMenuItem, NULL);
	backMenu->setAnchorPoint(Vec2(0.5f, 0.5f));
	backMenu->setPosition(Vec2(100, visibleSize.height - 50));
	this->addChild(backMenu);
	/******************************************************************/
	//½ÇÉ«
	sprite = Sprite::create("hero.png");
	sprite->setPosition(center);
	this->addChild(sprite);
	//go
	MenuItemImage * goMenuItem = MenuItemImage::create(
		"Go-up (2).png",
		"Go-down (2).png",
		CC_CALLBACK_1(ActionIntervalTest2::goCallback, this));
	auto goMenu = Menu::create(goMenuItem, NULL);
	goMenu->setAnchorPoint(Vec2(0.5f, 0.5f));
	goMenu->setPosition(Vec2(visibleSize.width-100, 50));
	this->addChild(goMenu);


	return true;
}


void ActionIntervalTest2::goBackCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
}
void ActionIntervalTest2::goCallback(Ref* pSender)
{
	log("go_layer tag = %d", this->getTag());
	auto visibleSize = Director::getInstance()->getVisibleSize();
	ccBezierConfig bezier;
	bezier.controlPoint_1 = Vec2(0, visibleSize.height / 2);
	bezier.controlPoint_2 = Vec2(300, -visibleSize.height / 2);
	bezier.endPosition = Vec2(100, 100);
	switch (this->getTag())
	{
	case kMoveTo:
		sprite->runAction(MoveTo::create(2,Vec2(visibleSize.width-50,
			visibleSize.height-50)));
		break;
	case kMoveBy:
		sprite->runAction(MoveBy::create(2,Vec2(-50,-50)));
		break;
	case kJumpTo:
		sprite->runAction(JumpTo::create(2,Vec2(150,150),30,5));
		break;
	case kJumpBy:
		sprite->runAction(JumpBy::create(2,Vec2(100,100),30,5));
		break;
	case kBezierBy:
		sprite->runAction(BezierBy::create(3,bezier));
		break;
	case kScaleTo:
		sprite->runAction(ScaleTo::create(2,4));
		break;
	case kScaleBy:
		sprite->runAction(ScaleBy::create(2,0.5));
		break;
	case kRotateTo:
		sprite->runAction(RotateTo::create(2,180));
		break;
	case kRotateBy:
		sprite->runAction(RotateBy::create(2,-180));
		break;
	case kBlinkTo:
		sprite->runAction(Blink::create(3,5));
		break;
	case kTintTo:
		sprite->runAction(TintTo::create(2,255,0,0));
		break;
	case kTintBy:
		sprite->runAction(TintBy::create(0.5,0,255,255));
		break;
	case kFadeTo:
		sprite->runAction(FadeTo::create(1,180));
		break;
	case kFadeIn:
		sprite->runAction(FadeIn::create(1));
		break;
	case kFadeOut:
		sprite->runAction(FadeOut::create(1));
		break;
	default:
		break;
	}
}

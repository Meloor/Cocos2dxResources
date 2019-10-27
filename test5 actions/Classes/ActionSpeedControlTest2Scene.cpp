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
#include "ActionSpeedControlTestScene.h"
#include "ActionSpeedControlTest2Scene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* ActionSpeedControlTest2::createScene()
{
    return ActionSpeedControlTest2::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in ActionSpeedControlTest2Scene.cpp\n");
}

// on "init" you need to initialize your instance
bool ActionSpeedControlTest2::init()
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
		CC_CALLBACK_1(ActionSpeedControlTest2::goBackCallback, this));
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
		CC_CALLBACK_1(ActionSpeedControlTest2::goCallback, this));
	auto goMenu = Menu::create(goMenuItem, NULL);
	goMenu->setAnchorPoint(Vec2(0.5f, 0.5f));
	goMenu->setPosition(Vec2(visibleSize.width - 100, 50));
	this->addChild(goMenu);
	return true;
}


void ActionSpeedControlTest2::goBackCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
}
void ActionSpeedControlTest2::goCallback(Ref* pSender)
{
	log("tag = %i", this->getTag());

	auto ac1 = (FiniteTimeAction*)MoveBy::create(2, Vec2(200, 0));
	auto ac2 = (FiniteTimeAction*)ac1->reverse();
	auto ac = Sequence::create(ac1, ac2, NULL);

	switch (this->getTag()) {
	case kEaseIn:
		sprite->runAction(EaseIn::create(ac, 3)); break;
	case kEaseOut:
		sprite->runAction(EaseOut::create(ac, 3)); break;
	case kEaseInOut:
		sprite->runAction(EaseInOut::create(ac, 3)); break;
	case kEaseSineIn:
		sprite->runAction(EaseSineIn::create(ac)); break;
	case kEaseSineOut:
		sprite->runAction(EaseSineOut::create(ac)); break;
	case kEaseSineInOut:
		sprite->runAction(EaseSineInOut::create(ac)); break;
	case kEaseExponentialIn:
		sprite->runAction(EaseExponentialIn::create(ac)); break;
	case kEaseExpoentialOut:
		sprite->runAction(EaseExponentialOut::create(ac)); break;
	case kEaseExpoentialInOut:
		sprite->runAction(EaseExponentialInOut::create(ac)); break;
	case kSpeed:
		sprite->runAction(EaseIn::create(ac,(CCRANDOM_0_1()*5))); break;
	}
}
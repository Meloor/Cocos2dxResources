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

#include "AnimationTestScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* AnimationTest::createScene()
{
    return AnimationTest::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in AnimationTestScene.cpp\n");
}

// on "init" you need to initialize your instance
bool AnimationTest::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//·µ»Ø²Ëµ¥
	MenuItemImage * backMenuItem = MenuItemImage::create(
		"Back-up (2).png",
		"Back-down (2).png",
		CC_CALLBACK_1(AnimationTest::goBackCallback, this));
	auto backMenu = Menu::create(backMenuItem, NULL);
	backMenu->setAnchorPoint(Vec2(0.5f, 0.5f));
	backMenu->setPosition(Vec2(100, visibleSize.height - 50));
	this->addChild(backMenu,1);
	//
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("run.plist");
	auto bg = Sprite::createWithSpriteFrameName("background.png");
	bg->setAnchorPoint(Vec2::ZERO);
	this->addChild(bg, 0);

	sprite = Sprite::createWithSpriteFrameName("h1.png");
	sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(sprite);

	isPlaying = false;
	
	auto go = Sprite::createWithSpriteFrameName("go.png");
	auto stop = Sprite::createWithSpriteFrameName("stop.png");

	auto goItem = MenuItemSprite::create(go, go);
	auto stopItem = MenuItemSprite::create(stop, stop);
	
	auto toggleItem = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(AnimationTest::onAction,this),goItem,stopItem,NULL);
	toggleItem->setPosition(Vec2(visibleSize.width-100, 50));
	
	auto mn = Menu::create(toggleItem, NULL);
	mn->setPosition(Vec2::ZERO);
	this->addChild(mn);
	
	
	return true;
}


void AnimationTest::onAction(Ref* pSender) {
	if (!isPlaying) {
		Animation* animation = Animation::create();
		for (int i = 1; i <= 4; i++) {
			auto frameName = __String::createWithFormat("h%d.png", i);
			log("frameName = %s", frameName->getCString());
			SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()
				->getSpriteFrameByName(frameName->getCString());
			animation->addSpriteFrame(spriteFrame);
		}

		animation->setDelayPerUnit(0.15f);
		animation->setRestoreOriginalFrame(true);
		Animate* action = Animate::create(animation);
		sprite->runAction(RepeatForever::create(action));

		isPlaying = true;
	}
	else {
		sprite->stopAllActions();
		isPlaying = false;
	}
}
void AnimationTest::goBackCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
}
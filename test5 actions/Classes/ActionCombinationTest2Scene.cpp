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
#include "ActionCombinationTestScene.h"
#include "ActionCombinationTest2Scene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* ActionCombinationTest2::createScene()
{
    return ActionCombinationTest2::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in ActionCombinationTest2Scene.cpp\n");
}

// on "init" you need to initialize your instance
bool ActionCombinationTest2::init()
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
		CC_CALLBACK_1(ActionCombinationTest2::goBackCallback, this));
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
		CC_CALLBACK_1(ActionCombinationTest2::goCallback, this));
	auto goMenu = Menu::create(goMenuItem, NULL);
	goMenu->setAnchorPoint(Vec2(0.5f, 0.5f));
	goMenu->setPosition(Vec2(visibleSize.width - 100, 50));
	this->addChild(goMenu);
	return true;
}


void ActionCombinationTest2::goBackCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
}
void ActionCombinationTest2::goCallback(Ref* pSender)
{
	log("tag = %i", this->getTag());
	switch(this->getTag()){
	case kSequence:
		this->onSequence(pSender); break;
	case kSpawn:
		this->onSpawn(pSender); break;
	case kRepeate:
		this->onRepeat(pSender); break;
	case kRepeateForever:
		this->onRepeatForever(pSender); break;
	case kReverse:
		this->onReverse(pSender); break;
	}
}

void ActionCombinationTest2::onSequence(Ref* pSender) {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2  p = Vec2(visibleSize.width / 2, 200);
	FiniteTimeAction* ac[5];
	ac[0] = (FiniteTimeAction*)sprite->runAction(Place::create(p));
	ac[1] = (FiniteTimeAction*)sprite->runAction(MoveTo::create(2,
		Vec2(visibleSize.width - 130,visibleSize.height - 200)));
	ac[2] = (FiniteTimeAction*)sprite->runAction(JumpBy::create(2,
		Vec2(8, 8), 6, 3));
	ac[3] = (FiniteTimeAction*)sprite->runAction(Blink::create(2, 3));
	ac[4] = (FiniteTimeAction*)sprite->runAction(TintBy::create(0.5, 0, 255, 255));

	sprite->runAction(Sequence::create(ac[0], ac[1], ac[2], ac[3], ac[4], ac[0], NULL));
}
void ActionCombinationTest2::onSpawn(Ref* pSender) {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2  p = Vec2(visibleSize.width / 2, 200);

	sprite->setRotation(0);
	sprite->setPosition(p);

	FiniteTimeAction* ac[2];
	ac[0] = (FiniteTimeAction*)sprite->runAction(MoveTo::create(2,
		Vec2(visibleSize.width - 100, visibleSize.height - 100)));
	ac[1] = (FiniteTimeAction*)sprite->runAction(RotateTo::create(2, 40));

	sprite->runAction(Spawn::create(ac[0], ac[1], NULL));
}
void ActionCombinationTest2::onRepeat(Ref* pSender) {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2  p = Vec2(visibleSize.width / 2, 200);

	sprite->setRotation(0);
	sprite->setPosition(p);

	FiniteTimeAction* ac[4];
	ac[0] = (FiniteTimeAction*)sprite->runAction(MoveTo::create(2,
		Vec2(visibleSize.width - 100, visibleSize.height - 100)));
	ac[1] = (FiniteTimeAction*)sprite->runAction(JumpBy::create(2,
		Vec2(10, 10), 20, 5));
	ac[2] = (FiniteTimeAction*)sprite->runAction(JumpBy::create(2,
		Vec2(-50, -50), 20, 3));
	ac[3] = Sequence::create(ac[0], ac[1], ac[2], NULL);
	sprite->runAction(Repeat::create(ac[3], 3));

}
void ActionCombinationTest2::onRepeatForever(Ref* pSender) {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2  p = Vec2(visibleSize.width / 2, 500);

	sprite->setRotation(0);
	sprite->setPosition(p);

	ccBezierConfig bezier;
	bezier.controlPoint_1 = Vec2(0, visibleSize.height / 2);
	bezier.controlPoint_2 = Vec2(10, -visibleSize.height / 2);
	bezier.endPosition = Vec2(10, 20);

	auto ac1 = (FiniteTimeAction*)sprite->runAction(BezierBy::create(2,bezier));
	auto ac2 = (FiniteTimeAction*)sprite->runAction(TintBy::create(0.5,0,255,255));
	auto ac1Reverse = (FiniteTimeAction*)ac1->reverse();
	auto ac2Repeat = (FiniteTimeAction*)sprite->runAction(Repeat::create(ac2,4));
	auto ac3 = (FiniteTimeAction*)sprite->runAction(Spawn::create(ac1,ac2Repeat,NULL));
	auto ac4 = (FiniteTimeAction*)sprite->runAction(Spawn::create(ac1Reverse,ac2Repeat,NULL));

	auto seq = Sequence::create(ac3, ac4, NULL);
	sprite->runAction(RepeatForever::create(seq));
}
void ActionCombinationTest2::onReverse(Ref* pSender) {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2  p = Vec2(visibleSize.width / 2, 300);

	sprite->setRotation(0);
	sprite->setPosition(p);

	auto ac1 = (FiniteTimeAction*)sprite->runAction(MoveBy::create(2,Vec2(40,60)));
	auto ac2 = ac1->reverse();
	auto seq = Sequence::create(ac1, ac2, NULL);
	sprite->runAction(Repeat::create(seq, 2));

}

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

#include "Scene1.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* Scene1::createScene()
{
    return Scene1::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in Scene1Scene.cpp\n");
}

// on "init" you need to initialize your instance
bool Scene1::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//返回菜单
	MenuItemFont::setFontName("Arial");
	MenuItemFont::setFontSize(40);
	MenuItemFont *item1 = MenuItemFont::create("back",
		CC_CALLBACK_1(Scene1::menuItem1Callback, this));
	auto menu = Menu::create(item1, NULL);
	menu->setPosition(Vec2(visibleSize.width -50,50));
	this->addChild(menu);

	//从文件创建精灵帧动画
	Animation* animation = Animation::create();
	for (int i = 1; i <= 17; i++) {
		auto frameName = __String::createWithFormat("fire/campFire%02d.png", i);
		log("frameName = %s", frameName->getCString());
		animation->addSpriteFrameWithFileName(frameName->getCString());
	}

	animation->setDelayPerUnit(0.08f);
	animation->setRestoreOriginalFrame(true);
	Animate* action = Animate::create(animation);
	//创建精灵
	auto sprite = Sprite::create("fire/campFire02.png");
	sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	sprite->runAction(RepeatForever::create(action));//使用动画
	this->addChild(sprite);

	return true;
}
void Scene1::menuItem1Callback(Ref* pSender) {
	Director::getInstance()->popScene();
}

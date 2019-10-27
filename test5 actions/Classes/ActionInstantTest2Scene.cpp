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
#include "ActionInstantTestScene.h"
#include "ActionInstantTest2Scene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* ActionInstantTest2::createScene()
{
    return ActionInstantTest2::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in ActionInstantTest2Scene.cpp\n");
}

// on "init" you need to initialize your instance
bool ActionInstantTest2::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
	hiddenFlag = true;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Vec2 center = Vec2(visibleSize.width / 2, visibleSize.height / 2);

	MenuItemImage * backMenuItem = MenuItemImage::create(
		"Back-up.png",
		"Back-down.png",
		CC_CALLBACK_1(ActionInstantTest2::goBackCallback, this));
	auto backMenu = Menu::create(backMenuItem, NULL);
	backMenu->setAnchorPoint(Vec2(0.5f, 0.5f));
	backMenu->setPosition(Vec2(100, visibleSize.height - 50));
	this->addChild(backMenu);
	/******************************************************************/
	//±³¾°
	auto bg = Sprite::create("Background800x480.png");
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(bg);
	//·É»ú
	plane = Sprite::create("Plane.png");
	plane->setPosition(center);
	this->addChild(plane);
	//go
	MenuItemImage * goMenuItem = MenuItemImage::create(
		"Go-up.png",
		"Go-down.png",
		CC_CALLBACK_1(ActionInstantTest2::goCallback, this));
	auto goMenu = Menu::create(goMenuItem, NULL);
	goMenu->setAnchorPoint(Vec2(0.5f, 0.5f));
	goMenu->setPosition(Vec2(visibleSize.width/2, 50));
	this->addChild(goMenu);


	return true;
}


void ActionInstantTest2::goBackCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
}
void ActionInstantTest2::goCallback(Ref* pSender)
{
	log("go_layer tag = %d", this->getTag());
	auto visibleSize = Director::getInstance()->getVisibleSize();

	Vec2  p = Vec2(CCRANDOM_0_1()*visibleSize.width,
		CCRANDOM_0_1()*visibleSize.height);

	switch (this->getTag())
	{
	case PLACE_TAG:
		plane->runAction(Place::create(p));
		break;
	case FLIPX_TAG:
		plane->runAction(FlipX::create(true));
		break;
	case FLIPY_TAG:
		plane->runAction(FlipY::create(true));
		break;
	case HIDE_TAG:
		if (hiddenFlag) {
			plane->runAction(Hide::create());
			hiddenFlag = false;
		}
		else {
			plane->runAction(Show::create());
			hiddenFlag = true;
		}		
		break;
	case TOGGLE_TAG:
		plane->runAction(ToggleVisibility::create());
		break;
	default:
		break;
	}
}

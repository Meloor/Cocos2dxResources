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

#include "Scene2.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* Scene2::createScene()
{
    return Scene2::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in Scene2Scene.cpp\n");
}

// on "init" you need to initialize your instance
bool Scene2::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	MenuItemFont::setFontName("Arial");
	MenuItemFont::setFontSize(40);
	MenuItemFont *item1 = MenuItemFont::create("back",
		CC_CALLBACK_1(Scene2::menuItem1Callback, this));
	auto menu = Menu::create(item1, NULL);
	menu->setPosition(Vec2(visibleSize.width - 50, 50));
	this->addChild(menu);

	//Ìí¼Ó´ò»ð»ú
	auto bg = Sprite::create("zippo.png");
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(bg);


	auto  p = ParticleFire::create();
	//p->setPosition(Director::getInstance()->convertToGL(Vec2(270, 380)));
	p->setPosition(Vec2(550, 400));
	this->addChild(p);
	return true;
}

void Scene2::menuItem1Callback(Ref* pSender) {
	Director::getInstance()->popScene();
}

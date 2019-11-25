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

#include "Scene3.h"
#include "Scene3a.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* Scene3::createScene()
{
    return Scene3::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in Scene3Scene.cpp\n");
}

// on "init" you need to initialize your instance
bool Scene3::init()
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
		CC_CALLBACK_1(Scene3::menuItem1Callback, this));
	auto menu = Menu::create(item1, NULL);
	menu->setPosition(Vec2(visibleSize.width - 50, 50));
	this->addChild(menu);

	//创建菜单
	Label* label[11];
	MenuItem* item[11];
	std::string str[11] = { "Explosion",
					   "Fire",
					   "FireWorks",
					   "Flower",
					   "Galaxy",
					   "Meteor",
					   "Rain",
					   "Smoke",
					   "Snow",
					   "Spiral",
					   "Sun"};
	for (int i = 0; i < 11; i++) {
		label[i] = Label::createWithBMFont("fonts/fnt8.fnt",str[i].c_str());
		item[i] = MenuItemLabel::create(label[i], CC_CALLBACK_1(Scene3::onClickMenu, this));
		item[i]->setTag(kExplosion+i);
	}
	auto mn = Menu::create(item[0], item[1], item[2], item[3], item[4], item[5],
		item[6], item[7], item[8], item[9], item[10], NULL);
	mn->alignItemsInColumns(2, 2, 2, 2, 2, 1, NULL);
	this->addChild(mn);

	return true;
}
void Scene3::menuItem1Callback(Ref* pSender) {
	Director::getInstance()->popScene();
}

void Scene3::onClickMenu(Ref* pSender) {
	MenuItem * nmitem = (MenuItem*)pSender;

	auto sc = Scene::create();
	auto layer = Scene3a::create();
	layer->setTag(nmitem->getTag());
	sc->addChild(layer);

	auto reScene = TransitionSlideInR::create(1.0f, sc);
	Director::getInstance()->pushScene(reScene);
}


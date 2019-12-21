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

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Scene1.h"
#include "Scene2.h"
#include "Scene3.h"
#include "Scene4.h"
#include "Scene5.h"
#include "Scene6.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
	auto scene = Scene::create();
	auto layer = HelloWorld::create();
	scene->addChild(layer);
    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin =  Director::getInstance()->getVisibleOrigin();

	//²Ëµ¥
	auto dic = Dictionary::createWithContentsOfFile("fonts/test.xml");
	MenuItemLabel* item[6];
	for (int i = 0; i < 6; i++) {
		auto str_en = String::createWithFormat("ch%d", i+1);
		auto str_ch = (String*)(dic->objectForKey(str_en->getCString()));
		auto label = Label::create();
		label->setString(str_ch->getCString());
		label->setSystemFontSize(40);
		item[i] = MenuItemLabel::create(label,
			CC_CALLBACK_1(HelloWorld::nextMenuCallback, this));
		item[i]->setTag(i+1);
	}
	auto mn = Menu::create(item[0], item[1], item[2], item[3], item[4], item[5], NULL);
	mn->alignItemsVertically();
	this->addChild(mn);

	return true;
}

void HelloWorld::nextMenuCallback(Ref* pSender){
	MenuItemFont* item = (MenuItemFont*)pSender;
	Scene* scene;
	switch (item->getTag()) {
	case 1:
		scene = Scene1::createScene(); break;
	case 2:
		scene = Scene2::createScene(); break;
	case 3:
		scene = Scene3::createScene(); break;
	case 4:
		scene = Scene4::createScene(); break;
	case 5:
		scene = Scene5::createScene(); break;
	case 6:
		scene = Scene6::createScene(); break;
	}
	auto reScene = TransitionFade::create(1.0f, scene);
	Director::getInstance()->pushScene(reScene);
}

void HelloWorld::backMenuCallback(Ref * pSender)
{

}





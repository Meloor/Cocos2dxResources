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

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
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
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    /*3.4ʵ�� ��Ϸ���ó���*/
	auto bg = Sprite::create("menu/setting-back.png");
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(bg);
	//��Ч����
	auto soundOnMenuItem = MenuItemImage::create("menu/on.png", "menu/on.png");
	auto soundOffMenuItem = MenuItemImage::create("menu/off.png", "menu/off.png");
	auto soundToggleMenuItem = MenuItemToggle::createWithCallback
		(CC_CALLBACK_1(HelloWorld::menuCloseCallback, this),
		soundOnMenuItem,
		soundOffMenuItem,
		NULL);
	soundToggleMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(804, 224)));
	//auto mn = Menu::create(soundToggleMenuItem, NULL);
	//mn->setPosition(Vec2::ZERO);
	//this->addChild(mn);
	//���ֿ���
	auto musicOnMenuItem = MenuItemImage::create("menu/on.png", "menu/on.png");
	auto musicOffMenuItem = MenuItemImage::create("menu/off.png", "menu/off.png");
	auto musicToggleMenuItem = MenuItemToggle::createWithCallback
		(CC_CALLBACK_1(HelloWorld::menuCloseCallback, this),
			musicOnMenuItem,
			musicOffMenuItem,
			NULL);
	musicToggleMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(820, 362)));
	//auto mn2 = Menu::create(musicToggleMenuItem, NULL);
	//mn2->setPosition(Vec2::ZERO);
	//this->addChild(mn2);
	//ok��
	auto okMenuItem = MenuItemImage::create("menu/ok-up.png", "menu/ok-down.png");
	okMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(600, 500)));
	auto mn3 = Menu::create(soundToggleMenuItem, musicToggleMenuItem, okMenuItem, NULL);
	mn3->setPosition(Vec2::ZERO);
	this->addChild(mn3);

	return true;
}
void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

EventCustom customEndEvent("game_scene_close_event");
_eventDispatcher->dispatchEvent(&customEndEvent);


}

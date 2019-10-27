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
#include "SettingScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    //return HelloWorld::create();
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

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


	/*开始场景**************************************/
	//设置背景
	auto bg = Sprite::create("background.png");
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(bg,1);
	
	//auto pm = Sprite::create("pokemons/small/tapu koko.png");
	//pm->setScale(1.5f);
	//pm->setPosition(Vec2(300, 320));
	//this->addChild(pm, 1);

	//纹理缓存的方法创建卡噗鸣鸣
	auto cache = Director::getInstance()->getTextureCache()->addImage("pokemons/small/tapu koko.png");
	//指定纹理和裁剪矩形区域来创建精灵
	auto pm = Sprite::create();
	pm->setTexture(cache);
	pm->setTextureRect(Rect(33, 0, 230, 300));
	//创建时直接用纹理缓存来初始化，第三个参数是是否旋转纹理，默认false不旋转
	//auto tree2 = Sprite::createWithTexture(cache,Rect(73, 72, 182, 270),false);
	pm->setScale(1.5f);
	pm->setPosition(Vec2(300, 320));
	this->addChild(pm, 1);

	//设置标签
	auto label = Label::createWithTTF("Pokemon","fonts/arial.ttf",80);
	label->setAnchorPoint(Vec2(0.5f, 0.5f));
	label->setPosition(Vec2(visibleSize.width / 2 -100, visibleSize.height - 80));
	this->addChild(label,1);

	auto label1 = Label::createWithTTF("start", "fonts/arial.ttf", 56);
	label1->setPosition(Vec2(800+130,470));
	this->addChild(label1, 1);

	auto label2 = Label::createWithTTF("setting", "fonts/arial.ttf", 56);
	label2->setPosition(Vec2(660 + 180,265));
	this->addChild(label2, 1);

	auto label3 = Label::createWithTTF("help", "fonts/arial.ttf", 56);
	label3->setAnchorPoint(Vec2(0.5f, 0.5f));
	label3->setPosition(Vec2(960 + 130,160));
	this->addChild(label3, 1);

	//菜单
	auto startSpriteNormal = Sprite::create("pokemons/small/pikachu.png");
	auto startSpriteSelected = Sprite::create("pokemons/small/pikachu2.png");
	MenuItemSprite * startMenuItem = MenuItemSprite::create(startSpriteNormal,
															startSpriteSelected,
															CC_CALLBACK_1(HelloWorld::menuItemStartCallback,this));
	//startMenuItem->setPosition(Director::getInstance()->convertToGL(Point(700,170)));
	startMenuItem->setPosition(Vec2(800, 470));
	MenuItemImage * settingMenuItem = MenuItemImage::create(
								"pokemons/small/starmie.png",
								"pokemons/small/starmie2.png",
								CC_CALLBACK_1(HelloWorld::menuItemSettingCallback,this));
	//settingMenuItem->setPosition(Director::getInstance()->convertToGL(Point(560,375)));
	settingMenuItem->setPosition(Vec2(660, 265));
	MenuItemImage * helpMenuItem = MenuItemImage::create(
								"pokemons/small/togepi.png",
								"pokemons/small/togepi2.png",
								CC_CALLBACK_1(HelloWorld::menuItemHelpCallback,this));
	//helpMenuItem->setPosition(Director::getInstance()->convertToGL(Point(860,480)));
	helpMenuItem->setPosition(Vec2(960,160));
	Menu * mu = Menu::create(startMenuItem,settingMenuItem,helpMenuItem,NULL);
	mu->setPosition(Point::ZERO);
	this->addChild(mu,2);

	log("HelloWorld init");
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
void HelloWorld::menuItemStartCallback(Ref* pSender) {
	log("Touch Start Menu Item ");
}
void  HelloWorld::menuItemSettingCallback(Ref* pSender) {
	auto sc = Setting::createScene();
	auto reScene = TransitionJumpZoom::create(1.0f, sc);
	//Director::getInstance()->replaceScene(reScene);
	Director::getInstance()->pushScene(reScene);
	//log("Touch Setting Menu Item ");
}
void  HelloWorld::menuItemHelpCallback(Ref* pSender) {
	log("Touch Help Menu Item ");
}

void HelloWorld::onEnter() {
	Layer::onEnter();
	log("HelloWorld onEnter");
}
void HelloWorld::onEnterTransitionDidFinish() {
	Layer::onEnterTransitionDidFinish();
	log("HelloWorld onEnterTransitionDidFinish");
}
void HelloWorld::onExit() {
	Layer::onExit();
	log("HelloWorld onExit");
}
void HelloWorld::onExitTransitionDidStart() {
	Layer::onExitTransitionDidStart();
	log("HelloWorld onExitTransitionDidStart");
}
void HelloWorld::cleanup() {
	Layer::cleanup();
	log("HelloWorld cleanup");
}



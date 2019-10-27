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

#include "SettingScene.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
USING_NS_CC;

Scene* Setting::createScene()
{
    //return Setting::create();
	auto scene = Scene::create();
	auto layer = Setting::create();
	scene->addChild(layer);
	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in SettingScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Setting::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
	//if(!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();





    /*3.4实例 游戏设置场景*/
	auto bg = Sprite::create("background.png");
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(bg,0);	

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

	//使用精灵帧缓存创建胖丁和皮皮
	//创建精灵帧缓存
	SpriteFrameCache *frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("pokemons/small/pokemons.plist");
	//通过名字去访问精灵帧缓存中的精灵帧
	auto pm1 = Sprite::createWithSpriteFrameName("jigglypuff.png");
	pm1->setPosition(Vec2(800, 450));
	this->addChild(pm1, 1);
	//先获取精灵帧缓存中的精灵帧，再由精灵帧来创建精灵
	SpriteFrame* pm2SF = frameCache->getSpriteFrameByName("clefairy.png");
	auto pm2 = Sprite::createWithSpriteFrame(pm2SF);
	pm2->setPosition(Vec2(800, 300));
	this->addChild(pm2,1);

	//标签
	auto label = Label::createWithTTF("Pokemon", "fonts/arial.ttf",80);
	label->setAnchorPoint(Vec2(0.5f, 0.5f));
	label->setPosition(Vec2(visibleSize.width/2-100, visibleSize.height-80));
	this->addChild(label, 1);

	auto label1 = Label::createWithTTF("sound", "fonts/arial.ttf", 56);
	label1->setPosition(Vec2(950,450));
	this->addChild(label1, 1);

	auto label2 = Label::createWithTTF("effect", "fonts/arial.ttf", 56);
	label2->setPosition(Vec2(950,300));
	this->addChild(label2, 1);

	auto label3 = Label::createWithTTF("back", "fonts/arial.ttf", 56);
	label3->setAnchorPoint(Vec2(0.5f, 0.5f));
	label3->setPosition(Vec2(780,80));
	this->addChild(label3, 1);

	//音效开关
	auto soundOnMenuItem = MenuItemImage::create("pokemons/small/poke ball.png", "pokemons/small/poke ball2.png");
	auto soundOffMenuItem = MenuItemImage::create("pokemons/small/poke ball.png", "pokemons/small/poke ball2.png");
	auto soundToggleMenuItem = MenuItemToggle::createWithCallback
		(CC_CALLBACK_1(Setting::menuItemSoundCallback, this),
		soundOnMenuItem,
		soundOffMenuItem,
		NULL);
	soundToggleMenuItem->setPosition(Vec2(1100, 450));
	//auto mn = Menu::create(soundToggleMenuItem, NULL);
	//mn->setPosition(Vec2::ZERO);
	//this->addChild(mn);
	//音乐开关
	auto musicOnMenuItem = MenuItemImage::create("pokemons/small/poke ball.png", "pokemons/small/poke ball2.png");
	auto musicOffMenuItem = MenuItemImage::create("pokemons/small/poke ball.png", "pokemonssmall//poke ball2.png");
	auto musicToggleMenuItem = MenuItemToggle::createWithCallback
		(CC_CALLBACK_1(Setting::menuItemEffectCallback, this),
			musicOnMenuItem,
			musicOffMenuItem,
			NULL);
	
	musicToggleMenuItem->setPosition(Vec2(1100, 300));
	//musicToggleMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(820, 362)));
	//auto mn2 = Menu::create(musicToggleMenuItem, NULL);
	//mn2->setPosition(Vec2::ZERO);
	//this->addChild(mn2);
	//ok键
	//auto okMenuItem = MenuItemImage::create("menu/ok-up.png", "menu/ok-down.png");
	auto okMenuItem = MenuItemImage::create("pokemons/small/pikachu.png", "pokemons/small/pikachu2.png",
			CC_CALLBACK_1(Setting::backCallback, this));
	//okMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(600, 500)));
	okMenuItem->setPosition(Vec2(640, 100));
	auto mn3 = Menu::create(soundToggleMenuItem, musicToggleMenuItem, okMenuItem, NULL);
	mn3->setPosition(Vec2::ZERO);
	this->addChild(mn3,1);


	log("Setting init");
	return true;
}
void Setting::menuCloseCallback(Ref* pSender)
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

void  Setting::backCallback(Ref* pSender) {
	Director::getInstance()->popScene();
	//auto sc = HelloWorld::createScene();
	//auto reScene = TransitionJumpZoom::create(1.0f, sc);
	//Director::getInstance()->replaceScene(reScene);
	log("Touch back Menu Item ");
}
void  Setting::menuItemSoundCallback(Ref* pSender) {
	log("Touch Sound Menu Item ");
}
void  Setting::menuItemEffectCallback(Ref* pSender) {
	log("Touch Effect Menu Item ");
}

void Setting::onEnter() {
	Layer::onEnter();
	log("Setting onEnter");
}
void Setting::onEnterTransitionDidFinish() {
	Layer::onEnterTransitionDidFinish();
	log("Setting onEnterTransitionDidFinish");
}
void Setting::onExit() {
	Layer::onExit();
	log("Setting onExit");
}
void Setting::onExitTransitionDidStart() {
	Layer::onExitTransitionDidStart();
	log("Setting onExitTransitionDidStart");
}
void Setting::cleanup() {
	Layer::cleanup();
	log("Setting cleanup");
}


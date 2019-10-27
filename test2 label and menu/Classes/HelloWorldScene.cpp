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

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin =  Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
	//各种标签
	//后三个参数分别是画布的大小，横向对其方式，纵向对其方弿有默认值（看下方），所以常常会省略
	/*LabelTTF**************************************/
	//auto label = LabelTTF::create("Hello World","Arial",64,
	//	Size::ZERO,
	//	TextHAlignment::CENTER,
	//	TextVAlignment::TOP);
	//
	//label->setPosition(Vec2(origin.x+visibleSize.width/2,
	//	origin.y+visibleSize.height - label->getContentSize().height));
	//this->addChild(label,1);
	/*图集*********************************/
	//auto label = LabelAtlas::create("HelloWorld","fonts/tuffy_bold_italic-charmap.png",48,65,' ');
	//label->setPosition(Vec2(origin.x+visibleSize.width/2,
	//	origin.y+visibleSize.height - label->getContentSize().height));
	//this->addChild(label,1);
	/*LabelBMFont位图字体标签************/
	//auto label = LabelBMFont::create("Hello World","fonts/BMFont.fnt");
	//label->setPosition(Vec2(origin.x+visibleSize.width/2,
	//	origin.y+visibleSize.height - label->getContentSize().height));
	//this->addChild(label,1);

	/*实例4.23Label***********************************************/
	auto label1 = Label::createWithSystemFont("Hello World1","Arial",36);
	label1->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height -100));
	this->addChild(label1,1);

	auto label2 = Label::createWithTTF("Hello World2","fonts/Marker Felt.ttf",36);
	label2->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height -200));
	this->addChild(label2,1);

	auto label3 = Label::createWithBMFont("fonts/BMFont.fnt","Hello World3");
	label3->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height -300));
	this->addChild(label3,1);
	
	//ttfcongig配置文件是一个结构体，可以配置更多的属性，比如描边，阴影，闪烁筿//	第三个参数是字符集，如utf-8,Dynamic（动态）表示根据系统动态去查找
	TTFConfig ttfconfig("fonts/Marker Felt.ttf",36,GlyphCollection::DYNAMIC);
	auto label4 = Label::createWithTTF(ttfconfig,"Hello World4");
		label4->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height -400));
	this->addChild(label4,1);

	ttfconfig.outlineSize = 4;
	auto label5= Label::createWithTTF(ttfconfig,"Hello World5");
		label5->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height -500));
	label5->enableShadow(Color4B(255,255,255,128),Size(4,-4));
	this->addChild(label5,1); 
	/*实例4.2.5中文乱码问题******************************************/

	//需要将源码问题转换为utf-8格式
	//auto label1 = LabelTTF::create("中国","Arial",30);
	//label1->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height -100));
	//this->addChild(label1,1);

	//
	//auto label2 = LabelBMFont::create("中国","fonts/bitmapFontChinese.fnt");
	//label2->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height -200));
	//this->addChild(label2,1);

	//auto label3 = Label::createWithBMFont("fonts/bitmapFontChinese.fnt","中国");
	//label3->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height -300));
	//this->addChild(label3,1);

	//TTFConfig ttfconfig("fonts/simhei.ttf",36,GlyphCollection::DYNAMIC);
	//auto label4 = Label::createWithTTF(ttfconfig,"您好，美好的一天",
	//									TextHAlignment::CENTER,
	//									visibleSize.width);
	//label4->setPosition(Vec2(origin.x+visibleSize.width/2,
	//	origin.y+visibleSize.height -400));
	//this->addChild(label4,1);

	/*文本菜单***************************************************************/
	//MenuItemFont::setFontName("Arial");
	//MenuItemFont::setFontSize(86);
	//MenuItemFont *item1 = MenuItemFont::create("Start",
	//	CC_CALLBACK_1(HelloWorld::menuItem1CallBack,this));

	//MenuItemAtlasFont *item2 = MenuItemAtlasFont::create("Help",
	//	"menu/tuffy_bold_italic-charmap.png",48,65,' ',
	//	CC_CALLBACK_1(HelloWorld::menuItem2CallBack,this));

	//auto mn = Menu::create(item1,item2,NULL);
	//mn->alignItemsVertically();
	//mn->alignItemsVerticallyWithPadding(30);
	//this->addChild(mn,1);

	/*精灵菜单**************************************/
	//设置背景
	//auto bg = Sprite::create("menu/setting-back.png");
	//bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	//this->addChild(bg,1);

	//auto startSpriteNormal = Sprite::create("menu/start-up.png");
	//auto startSpriteSelected = Sprite::create("menu/start-down.png");
	//MenuItemSprite * startMenuItem = MenuItemSprite::create(startSpriteNormal,
	//														startSpriteSelected,
	//														CC_CALLBACK_1(HelloWorld::menuItemStartCallback,this));
	//startMenuItem->setPosition(Director::getInstance()->convertToGL(Point(700,170)));

	//MenuItemImage * settingMenuItem = MenuItemImage::create(
	//							"menu/setting-up.png",
	//							"menu/setting-down.png",
	//							CC_CALLBACK_1(HelloWorld::menuItemHelpCallback,this));
	//settingMenuItem->setPosition(Director::getInstance()->convertToGL(Point(560,375)));

	//MenuItemImage * helpMenuItem = MenuItemImage::create(
	//							"menu/help-up.png",
	//							"menu/help-down.png",
	//							CC_CALLBACK_1(HelloWorld::menuItemHelpCallback,this));
	//helpMenuItem->setPosition(Director::getInstance()->convertToGL(Point(860,480)));

	//Menu * mu = Menu::create(startMenuItem,settingMenuItem,helpMenuItem,NULL);
	//mu->setPosition(Point::ZERO);
	//this->addChild(mu,2);

	/*开关菜单******************************************************************/
	/*3.4实例 游戏设置场景*/
	//auto bg = Sprite::create("menu/setting-back.png");
	//bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	//this->addChild(bg,1);
	////音效开兿
	//auto soundOnMenuItem = MenuItemImage::create("menu/on.png", "menu/on.png");
	//auto soundOffMenuItem = MenuItemImage::create("menu/off.png", "menu/off.png");
	//auto soundToggleMenuItem = MenuItemToggle::createWithCallback
	//	(CC_CALLBACK_1(HelloWorld::menuItemSoundCallback, this),
	//	soundOnMenuItem,
	//	soundOffMenuItem,
	//	NULL);
	//soundToggleMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(804, 224)));
	////auto mn = Menu::create(soundToggleMenuItem, NULL);
	////mn->setPosition(Vec2::ZERO);
	////this->addChild(mn,2);
	//////音乐开兿
	//auto musicOnMenuItem = MenuItemImage::create("menu/on.png", "menu/on.png");
	//auto musicOffMenuItem = MenuItemImage::create("menu/off.png", "menu/off.png");
	//auto musicToggleMenuItem = MenuItemToggle::createWithCallback
	//	(CC_CALLBACK_1(HelloWorld::menuItemMusicCallback, this),
	//		musicOnMenuItem,
	//		musicOffMenuItem,
	//		NULL);
	//musicToggleMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(820, 362)));
	////auto mn2 = Menu::create(musicToggleMenuItem, NULL);
	////mn2->setPosition(Vec2::ZERO);
	////this->addChild(mn2,2);
	//////ok锿
	//auto okMenuItem = MenuItemImage::create("menu/ok-up.png", "menu/ok-down.png");
	//okMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(600, 500)));
	//auto mn3 = Menu::create(soundToggleMenuItem, musicToggleMenuItem, okMenuItem, NULL);
	//mn3->setPosition(Vec2::ZERO);
	//this->addChild(mn3,2);

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
void HelloWorld::menuItemCallback(Ref* pSender){
	//auto sprite = Sprite::create("pichu.png");
	//sprite->setPosition(Vec2(origin.x+100,
	//	origin.y+100));
	//this->addChild(sprite,1);
}
void HelloWorld::menuItem1Callback(Ref* pSender){
	MenuItem * item = (MenuItem*)pSender;
	log("Touch Start Menu Item %p",item);
	//log("Touch Start Menu Item ");
}
void HelloWorld::menuItem2Callback(Ref* pSender){
	MenuItem * item = (MenuItem*)pSender;
	log("Touch Help Menu Item %p",item);
	//log("Touch Help Menu Item ");
}

void HelloWorld:: menuItemStartCallback(Ref* pSender){
		log("Touch Start Menu Item ");
}
void HelloWorld::menuItemSettingCallback(Ref* pSender){
		log("Touch Setting Menu Item ");
}
void HelloWorld::menuItemHelpCallback(Ref* pSender){
		log("Touch Help Menu Item ");
}
void HelloWorld::menuItemSoundCallback(Ref* pSender){
		log("Touch Sound Menu Item ");
}
void HelloWorld::menuItemMusicCallback(Ref* pSender){
		log("Touch Music Menu Item ");
}


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

#include "SuspandLayer.h"
#include "MainGame.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* SuspandLayer::createScene()
{
    //return SuspandLayer::create();
	auto scene = Scene::create();
	auto layer = SuspandLayer::create();
	scene->addChild(layer);
	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in SuspandLayerScene.cpp\n");
}

// on "init" you need to initialize your instance
bool SuspandLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//获取到截屏得到的图片路径
	auto bg_name = FileUtils::getInstance()->getWritablePath() + "suspand.png";
	auto spr_bg = Sprite::create(bg_name);
	spr_bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(spr_bg);
	//添加恢复游戏按钮
	auto dictionary = Dictionary::createWithContentsOfFile("fonts/text.xml");
	auto btn_label = Label::create();
	btn_label->setString(((String*)(dictionary->objectForKey("back_game")))->getCString());
	btn_label->setSystemFontSize(40);
	auto start_menu = MenuItemLabel::create(btn_label,CC_CALLBACK_1(SuspandLayer::startPlay,this));

	auto menu = Menu::create(start_menu, NULL);
	menu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(menu);

    return true;
}
void SuspandLayer::startPlay(Ref * ref) {
	//恢复游戏
	Director::getInstance()->popScene();
}


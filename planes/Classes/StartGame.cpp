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

#include "StartGame.h"
#include "MainGame.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* StartGame::createScene()
{
    //return StartGame::create();
	auto scene = Scene::create();
	auto layer = StartGame::create();
	scene->addChild(layer);
	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in StartGameScene.cpp\n");
}

// on "init" you need to initialize your instance
bool StartGame::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//游戏背景
	auto spr_bg = Sprite::create("ui/bg.png");
	spr_bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(spr_bg);
    
	//读取xml
	auto dic = Dictionary::createWithContentsOfFile("fonts/text.xml");
	auto str = (String*)(dic->objectForKey("title"));
	auto title = Label::create();
	title->setString(str->getCString());
	title->setSystemFontSize(60);
	title->setColor(Color3B(174.0f, 111.0f, 23.0f));
	title->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - title->getContentSize().height));
	this->addChild(title);

	//创建帧动画
	auto animation = Animation::create();
	for (int i = 1; i <= 4; i++) {
		auto spr_name = String::createWithFormat("ui/start%d.png",i);
		animation->addSpriteFrameWithFile(spr_name->getCString());
	}
	animation->setDelayPerUnit(0.3f);
	animation->setLoops(-1);

	////创建精灵
	auto sprite = Sprite::create("ui/start1.png");
	sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(sprite);
	sprite->runAction(Animate::create(animation));

	//添加游戏开始按钮
	str = (String*)(dic->objectForKey("play"));
	auto btn_label = Label::create();
	btn_label->setString(str->getCString());
	btn_label->setSystemFontSize(40);

	auto start_menu = MenuItemLabel::create(btn_label,CC_CALLBACK_1(StartGame::startPlay,this));

	auto menu = Menu::create(start_menu, NULL);
	menu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 4));
	this->addChild(menu);

    return true;
}
void StartGame::startPlay(Ref * ref) {
	Director::getInstance()->replaceScene(TransitionFadeTR::create(0.5, MainGame::createScene()));
}


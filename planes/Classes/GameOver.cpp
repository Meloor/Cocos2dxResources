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

#include "GameOver.h"
#include "MainGame.h"
#include "SimpleAudioEngine.h"
#include "StartGame.h"
USING_NS_CC;

Scene* GameOver::createScene()
{
    //return GameOver::create();
	auto scene = Scene::create();
	auto layer = GameOver::create();
	scene->addChild(layer);
	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GameOverScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameOver::init()
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
	auto dictionnary = Dictionary::createWithContentsOfFile("fonts/text.xml");
	//分数设置*********************************************************************/
	//分数标签
	auto label_score = Label::create();
	label_score->setString(((String*)(dictionnary->objectForKey("score")))->getCString());
	label_score->setSystemFontSize(40);
	label_score->setAnchorPoint(Vec2(0.5, 0.5));
	label_score->setPosition(Vec2(visibleSize.width/2-label_score->getContentSize().width/2,
		visibleSize.height - label_score->getContentSize().height*4));
	this->addChild(label_score);
	//最高分标签
	auto label_best_score = Label::create();
	label_best_score->setString(((String*)(dictionnary->objectForKey("best_score")))->getCString());
	label_best_score->setSystemFontSize(40);
	label_best_score->setAnchorPoint(Vec2(0.5, 0.5));
	label_best_score->setPosition(Vec2(visibleSize.width / 2 - label_best_score->getContentSize().width / 2,
		visibleSize.height - label_score->getContentSize().height *5));
	this->addChild(label_best_score);
	//当前分标签
	auto label_score_num_ = Label::create();
	label_score_num_->setSystemFontSize(30);
	label_score_num_->setAnchorPoint(Vec2(0, 0.5));
	label_score_num_->setPosition(Vec2(visibleSize.width / 2 + 10,
		visibleSize.height - label_score->getContentSize().height * 4));
	this->addChild(label_score_num_);
	//最高分标签
	auto label_best_score_num_ = Label::create();
	label_best_score_num_->setSystemFontSize(30);
	label_best_score_num_->setAnchorPoint(Vec2(0, 0.5));
	label_best_score_num_->setPosition(Vec2(visibleSize.width / 2 + 10,
		visibleSize.height - label_score->getContentSize().height * 5));
	this->addChild(label_best_score_num_);

	//设置最高分
	int score_win = UserDefault::getInstance()->getIntegerForKey("best_score", 0);
	label_best_score_num_->setString(String::createWithFormat("%d", score_win)->getCString());
	//设置当前分
	int score = UserDefault::getInstance()->getIntegerForKey("score", 0);
	label_score_num_->setString(String::createWithFormat("%d", score)->getCString());
	//-------------------------------------分数end----------------------------------------------------

	//添加游戏开始按钮
	auto btn_label = Label::create();
	auto str = (String*)(dictionnary->objectForKey("back_menu"));
	btn_label->setString(str->getCString());
	btn_label->setSystemFontSize(40);

	auto start_menu = MenuItemLabel::create(btn_label,CC_CALLBACK_1(GameOver::backToStartScene,this));

	auto menu = Menu::create(start_menu, NULL);
	menu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(menu);

    return true;
}
void GameOver::backToStartScene(Ref * ref) {
	Director::getInstance()->replaceScene(TransitionFadeTR::create(0.5, StartGame::createScene()));
}


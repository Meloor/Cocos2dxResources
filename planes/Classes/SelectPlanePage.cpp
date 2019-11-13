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

#include "SelectPlanePage.h"
#include "MainGame.h"
USING_NS_CC;
SelectPlanePage* SelectPlanePage::create(int page)
{
	SelectPlanePage* pRet = new SelectPlanePage();
	if (pRet && pRet->initLevelPage(page)) {
		pRet->autorelease();
		return pRet;
	}
	else {
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool SelectPlanePage::initLevelPage(int page) {
	if (!Node::init()) {
		return false;
	}
	page_ = page;
	auto size = Director::getInstance()->getWinSize();
	//背景
	auto sprite = Sprite::create("ui/bg_select.png");
	sprite->setPosition(Vec2(size.width / 2, size.height / 2));
	addChild(sprite);
	sprite->setVisible(false);
	//添加帧动画
	auto animation = Animation::create();
	for (int i = 1; i <= 2; i++) {
		auto spr_name = String::createWithFormat("plane/heros%d_%d.png", page, i);
		animation->addSpriteFrameWithFile(spr_name->getCString());
	}
	animation->setDelayPerUnit(0.2f);
	animation->setLoops(-1);

	auto spr_name = String::createWithFormat("plane/heros%d_1.png", page);
	auto plane_sprite = Sprite::create(spr_name->getCString());
	plane_sprite->setPosition(size.width / 2, size.height / 2);
	plane_sprite->setScale(2);
	this->addChild(plane_sprite);
	//动作
	auto animate = Animate::create(animation);
	plane_sprite->runAction(animate);
	//添加menu
	auto dictionary = Dictionary::createWithContentsOfFile("fonts/text.xml");
	auto btn_label = Label::create();
	btn_label->setString(((String*)(dictionary->objectForKey("select")))->getCString());
	btn_label->setSystemFontSize(40);
	btn_label->setColor(ccc3(36, 106, 32));
	auto start_menu = MenuItemLabel::create(btn_label,CC_CALLBACK_1(SelectPlanePage::menuStartCallback,this));
	auto menu = Menu::create(start_menu, NULL);
	menu->setPosition(Vec2(size.width/2, size.height*0.3));
	this->addChild(menu);
}
void SelectPlanePage::menuStartCallback(Ref * pSender)
{
	//auto scene = Scene::create();
	//auto main_layer = MainGame::create();
	////main_layer->init_hero_plane(page_);//不能这样用，会中断,它是在在init函数之后完成。
	////main_layer->setTag(page_);//这方法为什么不行
	//scene->addChild(main_layer);
	//Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0, scene));
	UserDefault::getInstance()->setIntegerForKey("plane_type", page_);
	Director::getInstance()->replaceScene(TransitionFadeTR::create(0.5, MainGame::createScene()));
}
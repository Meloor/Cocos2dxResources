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

#include "Scene2.h"
#include "SimpleAudioEngine.h"
#define TAG 100
USING_NS_CC;

Scene* Scene2::createScene()
{
	//auto scene = Scene::create();
	auto scene = Scene::createWithPhysics();
	auto layer = Scene2::create();
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
bool Scene2::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//中文标题标签
	auto dic = Dictionary::createWithContentsOfFile("fonts/test.xml");
	auto str_en = String::createWithFormat("ch%d", 2);
	auto str_ch = (String*)(dic->objectForKey(str_en->getCString()));
	auto label = Label::create();
	label->setString(str_ch->getCString());
	label->setSystemFontSize(40);
	label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 100));
	this->addChild(label);

	//返回菜单
	MenuItemFont::setFontName("Arial");
	MenuItemFont::setFontSize(40);
	auto backItem = MenuItemFont::create("Back", CC_CALLBACK_1(Scene2::backMenuCallback, this));
	auto mn = Menu::create(backItem, NULL);
	mn->alignItemsVertically();
	mn->setPosition(Vec2(70, visibleSize.height - 50));//左上角
	this->addChild(mn, 100);

	//go菜单
	auto goItem = MenuItemImage::create(
		"go-down.png", "go-up.png", CC_CALLBACK_1(Scene2::goCallback, this));
	auto mn2 = Menu::create(goItem, NULL);
	mn2->alignItemsVertically();
	mn2->setPosition(Vec2(visibleSize.width - 200, 100));
	this->addChild(mn2, 100);

	list = Vector<Sprite*>(MAX_COUNT);//不需要管理内存
	for (int i = 0; i < MAX_COUNT; i++) {
		auto sp = Sprite::create("Ball.png");
		list.pushBack(sp);
	}

	return true;
}



void Scene2::goCallback(Ref* pSender){
	Size vSize = Director::getInstance()->getVisibleSize();
	//在init函数中不对list使用retain,会发现list的引用计数是一个随机数
	//当存储单元被释放时会出现这种情况，就是list变成了野指针。
	log("list->count():%d", list.size());
	//init函数中添加了100个精灵到list中
	for(const auto& sp:list){
		int x = CCRANDOM_0_1()*vSize.width;
		int y = CCRANDOM_0_1()*vSize.height;
		sp->setPosition(Vec2(x, y));
		//移除后重新添加，也可以用两个遍历，先全部移除再全部一起添加
		this->removeChild(sp);
		this->addChild(sp);
	}
}

void Scene2::backMenuCallback(Ref * pSender)
{
	Director::getInstance()->popScene();
}





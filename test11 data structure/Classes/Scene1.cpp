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

#include "Scene1.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* Scene1::createScene()
{
	auto scene = Scene::create();
	auto layer = Scene1::create();
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
bool Scene1::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//标题标签
	auto dic = Dictionary::createWithContentsOfFile("fonts/test.xml");
	auto str_en = String::createWithFormat("ch%d", 1);
	auto str_ch = (String*)(dic->objectForKey(str_en->getCString()));
	auto label = Label::create();
	label->setString(str_ch->getCString());
	label->setSystemFontSize(40);
	label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 100));
	this->addChild(label,200);
	
	//返回菜单
	MenuItemFont::setFontName("Arial");
	MenuItemFont::setFontSize(40);
	auto backItem = MenuItemFont::create("Back", CC_CALLBACK_1(Scene1::backMenuCallback, this));
	auto mn = Menu::create(backItem, NULL);
	mn->alignItemsVertically();
	mn->setPosition(Vec2(70, visibleSize.height - 50));//左上角
	this->addChild(mn, 200);

	//go菜单
	auto goItem = MenuItemImage::create(
		"go-down.png", "go-up.png", CC_CALLBACK_1(Scene1::goCallback, this));
	auto mn2 = Menu::create(goItem, NULL);
	mn2->alignItemsVertically();
	mn2->setPosition(Vec2(visibleSize.width - 200, 100));
	this->addChild(mn2, 200);

	//使用create创建对象时会同时对其调用autoRelease,在消息循环结束时（这里是init函数结束时）释放。
	list = Array::createWithCapacity(MAX_COUNT);
	list->retain();//retain引用计数+1,对于ref,引用计数为0的时候会被释放，此时不希望释放
	//Array不是Node类型，因此不能使用this->addChild()方法将其添加到层中，只能手动retain。
	//放到list中了，并没有放到层里，所以在场景中还看不到
	for (int i = 0; i < MAX_COUNT; i++) {
		auto sp = Sprite::create("Ball.png");
		list->addObject(sp);
	}
	return true;
}
void Scene1::goCallback(Ref* pSender) {
	Size vSize = Director::getInstance()->getVisibleSize();
	//在init函数中不对list使用retain,会发现list的引用计数是一个随机数
	//当存储单元被释放时会出现这种情况，就是list变成了野指针。
	log("list->count():%d", this->list->count());
	Ref* obj = nullptr;
	//init函数中添加了100个精灵到list中
	CCARRAY_FOREACH(this->list, obj) {
		auto sp = (Sprite*)obj;
		int x = CCRANDOM_0_1()*vSize.width;
		int y = CCRANDOM_0_1()*vSize.height;
		sp->setPosition(Vec2(x, y));
		//移除后重新添加，也可以用两个遍历，先全部移除再全部一起添加
		this->removeChild(sp);
		this->addChild(sp);
	}
}

void Scene1::backMenuCallback(Ref * pSender)
{
	Director::getInstance()->popScene();
}

Scene1::~Scene1()
{
	this->list->removeAllObjects();
	//释放内存并将指针赋空，没有释放会造成内存泄漏，没有赋空会产生野指针。
	CC_SAFE_RELEASE_NULL(this->list);
}




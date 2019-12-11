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

#include "Scene6.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* Scene6::createScene()
{
	//auto scene = Scene::create();
	auto scene = Scene::createWithPhysics();
	auto layer = Scene6::create();
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
bool Scene6::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin =  Director::getInstance()->getVisibleOrigin();

	setTouchEnabled(true);//开启层触摸事件
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);//单点触摸

	//auto body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 0.5);
	//auto edgeNode = Node::create();
	//edgeNode->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	//edgeNode->setPhysicsBody(body);
	//this->addChild(edgeNode);

	//返回菜单
	MenuItemFont::setFontName("Arial");
	MenuItemFont::setFontSize(40);
	auto backItem = MenuItemFont::create("Back",CC_CALLBACK_1(Scene6::backMenuCallback,this));
	auto mn = Menu::create(backItem, NULL);
	mn->alignItemsVertically();
	mn->setPosition(Vec2(visibleSize.width - 70, 40));
	this->addChild(mn);

	return true;
}

bool Scene6::onTouchBegan(Touch * touch, Event * event)
{
	return false;
}

void Scene6::addNewSpriteAtPos(Vec2 pos)
{
}

void Scene6::nextMenuCallback(Ref* pSender){
	
}

void Scene6::backMenuCallback(Ref * pSender)
{
	Director::getInstance()->popScene();
}





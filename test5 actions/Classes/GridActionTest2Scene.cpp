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

#include "GridActionTestScene.h"
#include "GridActionTest2Scene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* GridActionTest2::createScene()
{
    return GridActionTest2::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GridActionTest2Scene.cpp\n");
}

// on "init" you need to initialize your instance
bool GridActionTest2::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Vec2 center = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	
	//场景中加入背景
	gridNodeTarget = NodeGrid::create();
	this->addChild(gridNodeTarget);

	//背景
	auto bg = Sprite::create("Background (2).png");
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	gridNodeTarget->addChild(bg);//不能用this去addchild,否则看不到物体
	//返回菜单
	MenuItemImage * backMenuItem = MenuItemImage::create(
		"Back-up (2).png",
		"Back-down (2).png",
		CC_CALLBACK_1(GridActionTest2::goBackCallback, this));
	auto backMenu = Menu::create(backMenuItem, NULL);
	backMenu->setAnchorPoint(Vec2(0.5f, 0.5f));
	backMenu->setPosition(Vec2(100, visibleSize.height - 50));
	this->addChild(backMenu);
	/******************************************************************/
	//角色
	sprite = Sprite::create("hero.png");
	sprite->setPosition(center);
	gridNodeTarget->addChild(sprite);//不能用this去addchild,否则看不到物体
	//go
	MenuItemImage * goMenuItem = MenuItemImage::create(
		"Go-up (2).png",
		"Go-down (2).png",
		CC_CALLBACK_1(GridActionTest2::goCallback, this));
	auto goMenu = Menu::create(goMenuItem, NULL);
	goMenu->setAnchorPoint(Vec2(0.5f, 0.5f));
	goMenu->setPosition(Vec2(visibleSize.width - 100, 50));
	this->addChild(goMenu);

	return true;
}



void GridActionTest2::goBackCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
}
void GridActionTest2::goCallback(Ref* pSender)
{
	log("tag = %i", this->getTag());
	auto visibleSize = Director::getInstance()->getVisibleSize();

	switch (this->getTag())
	{
	case kFlipX3D:
		gridNodeTarget->runAction(FlipX3D::create(3.0f)); break;
	case kPageTurn3D:
		gridNodeTarget->runAction(PageTurn3D::create(3.0f,Size(15,10))); break;
	case kLens3D:
		gridNodeTarget->runAction(Lens3D::create(3.0f,Size(15,10),
			Vec2(visibleSize.width/2,visibleSize.height/2),240)); break;
	case kShaky3D:
		gridNodeTarget->runAction(Shaky3D::create(3.0f,Size(15,10),5,false)); break;
	case kWaves3D:
		gridNodeTarget->runAction(Waves3D::create(3.0f, Size(15, 10),5,40)); break;
	case kJumpTitles3D:
		gridNodeTarget->runAction(JumpTiles3D::create(3.0f, Size(15, 10),2,30)); break;
	case kShakyTitles3D:
		gridNodeTarget->runAction(ShakyTiles3D::create(3.0f, Size(16, 12),5,false)); break;
	case kWavesTitles3D:
		gridNodeTarget->runAction(CCWavesTiles3D::create(3.0f, Size(15, 10),4,120)); break;
	default:
		break;
	}
}
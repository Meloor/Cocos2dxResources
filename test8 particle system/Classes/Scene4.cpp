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

#include "Scene4.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* Scene4::createScene()
{
    return Scene4::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in Scene4Scene.cpp\n");
}

// on "init" you need to initialize your instance
bool Scene4::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//返回菜单
	MenuItemFont::setFontName("Arial");
	MenuItemFont::setFontSize(40);
	MenuItemFont *item1 = MenuItemFont::create("back",
		CC_CALLBACK_1(Scene4::menuItem1Callback, this));
	auto menu = Menu::create(item1, NULL);
	menu->setPosition(Vec2(visibleSize.width - 50, 50));
	this->addChild(menu);

	//
	auto bg = Sprite::create("background-1.png");
	bg->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(bg);

	//
	auto p = ParticleSystemQuad::createWithTotalParticles(200);
	p->setTexture(Director::getInstance()->getTextureCache()->addImage("snow.png"));

	//粒子设置
	p->setDuration(-1);//设置发射粒子的持续时间-1表示永远持续
	p->setGravity(Point(0, -240));//设 置粒子的重力方向系 
	p->setAngle(90);//设置角度以及偏差
	p->setAngleVar(360);
	p->setRadialAccel(50);//设置径向加速度以及偏差
	p->setRadialAccelVar(0);
	p->setTangentialAccel(30);//设置粒子的切向加速度以及偏差
	p->setTangentialAccelVar (0) ;
	p->setPosVar(Point(400, 0));// 设置粒子初始化位置偏差
	p->setLife (4) ;//设置粒子生命期以及偏差
	p->setLifeVar (2);
	p->setStartSpin(30);//设置粒子开始时候旋转角度以及偏差
	p->setStartSpinVar (60) ;
	p->setEndSpin(60);//设置结束时候的旋转角度以及偏差
	p->setEndSpinVar(60) ;
	p->setStartColor(Color4F(1, 1, 1, 1));//设置开始时 候的颜色以及偏差
	p->setEndColor(Color4F(1, 1, 1, 1));//设置结 束时候的颜色以及偏差	
	p->setStartSize (30) ;//设置开始时候粒子大小以及偏差
	p->setStartSizeVar(0) ;
	p->setEndSize(20.0f);//设置粒子结束时候大小以及偏差
	p->setEndSizeVar(0);
	p->setEmissionRate(100);//设置每秒钟产生粒子的数量

	p->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(p);
	return true;
}
void Scene4::menuItem1Callback(Ref* pSender) {
	Director::getInstance()->popScene();
}


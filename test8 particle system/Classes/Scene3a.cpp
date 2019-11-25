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

#include "Scene3a.h"
#include "Scene3.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* Scene3a::createScene()
{
    return Scene3a::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in Scene3aScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Scene3a::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//·µ»Ø²Ëµ¥
	MenuItemFont::setFontName("Arial");
	MenuItemFont::setFontSize(40);
	MenuItemFont *item1 = MenuItemFont::create("back",
		CC_CALLBACK_1(Scene3a::menuItem1Callback, this));
	auto menu = Menu::create(item1, NULL);
	menu->setPosition(Vec2(visibleSize.width - 50, 50));
	this->addChild(menu);
	

	
	pb = Label::createWithBMFont("fonts/fnt8.fnt", "");
	pb->setPosition(Point(visibleSize.width / 2, visibleSize.height - 50));
	this->addChild(pb, 3);

	return true;
}
void Scene3a::onEnterTransitionDidFinish()
{
	Scene::onEnterTransitionDidFinish();
	ParticleSystem* system = NULL;
	switch (this->getTag())
	{
	case kExplosion:
		system = ParticleExplosion::create();
		pb->setString("Explosion");
		break;
	case kFire:
		system = ParticleFire::create();
		pb->setString("Fire");
		break;
	case kFireworks:
		system = ParticleFireworks::create();
		pb->setString("FireWorks");
		break;
	case kFlower:
		system = ParticleFlower::create();
		pb->setString("Flower");
		break;
	case kGalaxy:
		system = ParticleGalaxy::create();
		pb->setString("Galaxy");
		break;
	case kMeteor:
		system = ParticleMeteor::create();
		pb->setString("Meteor");
		break;
	case kRain:
		system = ParticleRain::create();
		pb->setString("Rain");
		break;
	case kSmoke:
		system = ParticleExplosion::create();
		pb->setString("Smoke");
		break;
	case kSnow:
		system = ParticleSnow::create();
		pb->setString("Snow");
		break;
	case kSpiral:
		system = ParticleSpiral::create();
		pb->setString("Spiral");
		break;
	case kSun:
		system = ParticleSun::create();
		pb->setString("Sun");
		break;
	default:
		break;
	}

	Size vsize = Director::getInstance()->getVisibleSize();
	system->setPosition(Vec2(vsize.width / 2, vsize.height / 2));

	this->addChild(system);
}
void Scene3a::menuItem1Callback(Ref* pSender) {
	Director::getInstance()->popScene();
}


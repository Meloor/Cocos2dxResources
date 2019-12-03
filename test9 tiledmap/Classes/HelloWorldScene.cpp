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

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;

Scene* HelloWorld::createScene()
{
	auto scene = Scene::create();
    auto layer =  HelloWorld::create();
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
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin =  Director::getInstance()->getVisibleOrigin();

	//读取瓦片地图
	myMap = TMXTiledMap::create("map/mymap.tmx");
	
	//获取对象
	TMXObjectGroup* objects = myMap->getObjectGroup("object");//通过对象层名获得对象层对象集合
	ValueMap player = objects->getObject("player");//通过对象名获得对象
	ValueMap originPoint = objects->getObject("originPoint");//通过对象名获得对象

	//设置地图偏移
	ox = originPoint["x"].asFloat();//获得对象的x轴
	oy = originPoint["y"].asFloat();//获得对象的y轴坐标，已经转换成了opengl坐标，即该对象的左下角在map中的opengl坐标
	log("originPoint(%f,%f)", ox, oy);//256,1632
	myMap->setPosition(Vec2(-ox, -oy));
	//this->setPosition(ox, oy);//移动视点（默认是原点（0,0））
	//this->setViewPointCenter(Vec2(-ox, -oy));
	this->addChild(myMap);

	//根据player对象位置设置精灵位置
	float x = player["x"].asFloat();//获得对象的x轴
	float y = player["y"].asFloat();//获得对象的y轴
	log("player(x=%f,y=%f)\n", x, y);
	playerSprite = Sprite::create("player.png");//场景中放置精灵
	playerSprite->setPosition(Vec2(x-ox, y-oy));//精灵的位置放到对象的位置
	playerSprite->setAnchorPoint(Vec2(0, 0));//对象的位置是其左下角，所以精灵的锚点也应该设置成左下角
	playerSprite->setAnchorPoint(Vec2(0, 1));//为什么是左上角呢
	this->addChild(playerSprite);

	//获取障碍层
	coLayer = myMap->getLayer("collider");

	this->setTouchEnabled(true);//开启层触摸监听
	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	return true;
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* envent) {
	return true;
}
void   HelloWorld::onTouchMoved(Touch* touch, Event* envent) {
	//log("touch moved");
}
void   HelloWorld::onTouchEnded(Touch* touch, Event* envent) {
	Vec2 touchp = touch->getLocation();//获取触摸点的opengl坐标
	Vec2 playerp = playerSprite->getPosition();//精灵在屏幕上的opengl坐标
	Vec2 diff = touchp - playerp;//触点与角色之间的距离差
	if (abs(diff.x) > abs(diff.y)) {
		if (diff.x > 0) {
			playerp.x += myMap->getTileSize().width;//每次只移动一格
			playerSprite->runAction(FlipX::create(FALSE));
		}
		else {
			playerp.x -= myMap->getTileSize().width;
			playerSprite->runAction(FlipX::create(TRUE));
		}
	}
	else {
		if (diff.y > 0)
			playerp.y += myMap->getTileSize().height;
		else playerp.y -= myMap->getTileSize().height;
	}
	//playerSprite->setPosition(playerp.x, playerp.y);
	this->setPlayerPos(playerp);//触摸结束后设置精灵位置
}

Vec2 HelloWorld::tileCoordFromPosition(Vec2 pos)//pos为触摸点的opengl坐标
{
	//地图y轴瓦片总数乘以每个瓦片的高度得到地图的y轴总高度
	int mpy = myMap->getMapSize().height * myMap->getTileSize().height;
	int mpx = myMap->getMapSize().width * myMap->getTileSize().width;

	//转换成在地图的opengl像素坐标，因为地图的原点不是屏幕原点
	Vec2 posInMap = Vec2(pos.x + ox, pos.y + oy);
	//转换成在地图的UI像素坐标（原点在左上角）
	Vec2 posInMapUI = Vec2(pos.x + ox, mpy- (pos.y + oy));
	
	//转换成瓦片坐标
	int x = posInMapUI.x / myMap->getTileSize().width;
	int y = posInMapUI.y / myMap->getTileSize().height;
	return Vec2(x,y);
}

void HelloWorld::setPlayerPos(Vec2 pos)//pos为精灵在屏幕上的opengl坐标
{
	Vec2 tilePos = this->tileCoordFromPosition(pos);//转换成瓦片坐标以方便判断
	int tileGid = coLayer->getTileGIDAt(tilePos);
	if (tileGid > 0) {
		Value prop = myMap->getPropertiesForGID(tileGid);//获得gid的属性
		ValueMap propMap = prop.asValueMap();//强制类型转换
		if (propMap["Collidable"].asBool()) {
			SimpleAudioEngine::getInstance()->playEffect("empty.wav");
			return;
		}
	}
	playerSprite->setPosition(pos);
	this->setViewPointCenter(playerSprite->getPosition());
}

void HelloWorld::setViewPointCenter(Vec2 pos)//这个点是目标点
{
	//地图y轴瓦片总数乘以每个瓦片的高度得到地图的y轴总高度
	int mpy = myMap->getMapSize().height * myMap->getTileSize().height;
	int mpx = myMap->getMapSize().width * myMap->getTileSize().width;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	//x坐标不能小于屏幕坐标的一半
	int x = MAX(pos.x, visibleSize.width / 2);
	int y = MAX(pos.y, visibleSize.height / 2);
	x = MIN(x,mpx - visibleSize.width / 2);
	y = MIN(x, mpy - visibleSize.height / 2);

	Vec2 pointA = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	Vec2 pointB = Vec2(x, y);
	Vec2 offset = pointA - pointB;//相当于AB向量
	this->setPosition(offset);//设置的是Layer的位置,移动层就相当于移动地图
}


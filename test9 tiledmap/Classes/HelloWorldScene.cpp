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
	//获得对象在地图上的opengl坐标
	//即该对象的左下角在map中的opengl坐标
	float ox = originPoint["x"].asFloat();
	float oy = originPoint["y"].asFloat();
	//log("originPoint(%f,%f)", ox, oy);
	//移动层，而场景是没有变的，层上的地图和精灵会跟着移动
	this->setPosition(-ox, -oy);
	this->addChild(myMap);

	//根据player对象位置设置精灵位置
	float x = player["x"].asFloat();//获得对象的x轴坐标
	float y = player["y"].asFloat();//获得对象的y轴坐标
	//log("player(x=%f,y=%f)\n", x, y);
	playerSprite = Sprite::create("player.png");//场景中放置精灵
	playerSprite->setPosition(Vec2(x, y));//精灵的位置放到对象的位置
	//对象的位置是其左下角，所以精灵的锚点也应该设置成左下角
	playerSprite->setAnchorPoint(Vec2(0, 0));
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
	Vec2 touchp = touch->getLocation();//获取触摸点的opengl屏幕坐标
	Vec2 touchInLayer = touchp - this->getPosition();//触摸点在层上的opengl坐标
	//log("touch pos(%f,%f)", touchp.x, touchp.y);
	Vec2 playerp = playerSprite->getPosition();//精灵在层上的opengl坐标
	//log("player pos(%f,%f)", playerp.x, playerp.y);
	Vec2 diff = touchInLayer - playerp;//触点与角色之间的距离差
	offset = Vec2(0, 0);//每次移动的偏移值，如果没有移动就是0
	if (abs(diff.x) > abs(diff.y)) {
		if (diff.x > 0) {
			log("go right");
			offset.x = myMap->getTileSize().width;//每次只移动一格
			playerSprite->runAction(FlipX::create(FALSE));
		}
		else {
			log("go left");
			offset.x = -myMap->getTileSize().width;
			playerSprite->runAction(FlipX::create(TRUE));
		}
	}
	else {
		if (diff.y > 0) {
			offset.y = myMap->getTileSize().height;
			log("go up");
		}
		else {
			offset.y = -myMap->getTileSize().height;
			log("go down");
		}
	}
	//触摸结束后设置精灵在层中的位置（带碰撞检测）
	this->setPlayerPos(playerp+offset);
}
//触摸点在层上的opengl坐标坐标转换成瓦片坐标
//pos为触摸点在层上的opengl坐标，其原点为层的原点
Vec2 HelloWorld::tileCoordFromPosition(Vec2 pos)
{
	//地图y轴瓦片总数乘以每个瓦片的高度得到地图的y轴总高度
	int mpy = myMap->getMapSize().height * myMap->getTileSize().height;

	//转换成在地图的opengl像素坐标。现在层的原点也是地图的opengl原点。
	Vec2 posInMap = Vec2(pos.x, pos.y);
	//转换成在地图的UI像素坐标（原点在左上角）
	Vec2 posInMapUI = Vec2(pos.x, mpy-pos.y );
	
	//转换成瓦片坐标
	int x = posInMapUI.x / myMap->getTileSize().width;
	int y = posInMapUI.y / myMap->getTileSize().height;
	return Vec2(x,y);
}

//碰撞检测
void HelloWorld::setPlayerPos(Vec2 pos)//pos为精灵在层上的opengl坐标,
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
	this->setViewPointCenter(pos);//精灵真正移动后才会移动层
}
//移动Layer保证player尽量位于屏幕中心
void HelloWorld::setViewPointCenter(Vec2 pos)//pos是精灵在层上的opengl坐标
{
	//地图y轴瓦片总数乘以每个瓦片的高度得到地图的y轴总高度
	int mpy = myMap->getMapSize().height * myMap->getTileSize().height;
	int mpx = myMap->getMapSize().width * myMap->getTileSize().width;

	Size visibleSize = Director::getInstance()->getVisibleSize();

	Vec2 layerNextPos = this->getPosition() - offset;//层的移动方向和精灵的移动方向相反
	
	//防止出现黑边
	if (layerNextPos.x > 0)//层往右偏移，那么左边就会有黑边
		layerNextPos.x =0;
	if (layerNextPos.x < -mpx + visibleSize.width)//层往左偏移，要留下一倍的屏幕宽度
		layerNextPos.x = -mpx + visibleSize.width;
	if (layerNextPos.y > 0)//层往上偏移，那么下面就会有黑边
		layerNextPos.y = 0;
	if (layerNextPos.y < -mpy + visibleSize.height)//层往下偏移，要留下一倍的屏幕高度
		layerNextPos.y = -mpy + visibleSize.height;

	//到达边界后要先移动1/2屏幕的距离再滚动屏幕
	float px = playerSprite->getPositionX();
	float py = playerSprite->getPositionY();
	if (px <= visibleSize.width / 2)
		layerNextPos.x = 0;
	if (px >= mpx - visibleSize.width / 2)
		layerNextPos.x = -mpx + visibleSize.width;
	if (py <= visibleSize.height / 2)
		layerNextPos.y = 0;
	if (py >= mpy - visibleSize.height / 2)
		layerNextPos.y = -mpy + visibleSize.height;

	this->setPosition(layerNextPos);//设置的是Layer的位置,移动层就相当于移动地图
}


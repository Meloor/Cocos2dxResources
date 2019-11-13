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

#include "SelectPlaneLayer.h"
#include "SimpleAudioEngine.h"
#define SHORTEST_SLIDE_LENGTH 50
USING_NS_CC;

Scene* SelectPlaneLayer::createScene()
{
	auto sc = Scene::create();
	auto layer = SelectPlaneLayer::create();
	sc->addChild(layer);
    return sc;
}


// on "init" you need to initialize your instance
bool SelectPlaneLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	//添加触摸绑定事件
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(SelectPlaneLayer::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(SelectPlaneLayer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(SelectPlaneLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	size_x = Director::getInstance()->getWinSize().width;
	size_y = Director::getInstance()->getWinSize().height;
    return true;
}

void SelectPlaneLayer::goToCurrNode() {
	//滑动效果
	this->runAction(MoveTo::create(0.4f,Point(-cur_page_node_*size_x, 0)));
}

void SelectPlaneLayer::addNode(Node *level) {
	if (level) {
		level->setContentSize(Size(size_x, size_y));
		level->setPosition(Point(size_x*page_node_, 0));
		this->addChild(level);
		//记录添加几个飞机界面
		page_node_++;
	}
}

bool SelectPlaneLayer::onTouchBegan(Touch * touch, Event * unused_event)
{
	touch_down_point_ = touch->getLocation();
	touch_cur_point_ = touch_down_point_;
	return true;
}

void SelectPlaneLayer::onTouchMoved(Touch * touch, Event * unused_event)
{
	Point touchPoint = touch->getLocation();
	auto currX = this->getPositionX() + touchPoint.x - touch_cur_point_.x;
	Point pos_point = Point(currX, getPositionY());
	touch_cur_point_ = touchPoint;
	
}

void SelectPlaneLayer::onTouchEnded(Touch * touch, Event * unused_event)
{
	//坐标差
	touch_up_point_ = touch_cur_point_;
	auto dis = touch_up_point_.getDistance(touch_down_point_);
	if (dis >= SHORTEST_SLIDE_LENGTH)
	{
		if (touch_down_point_.x > touch_up_point_.x) {
			++cur_page_node_;
			if (page_node_ - 1 < cur_page_node_)
				cur_page_node_ = page_node_ - 1;
		}
		else if (touch_down_point_.x < touch_up_point_.x) {
			--cur_page_node_;
			if (cur_page_node_ < 0) {
				cur_page_node_ = 0;
			}
		}
		//log("touch_down_point_.x:%lf touch_up_point_:%lf\n", touch_down_point_.x, touch_up_point_.x);
		//log("cur_page_node_%d",cur_page_node_);
		goToCurrNode();
	}
}


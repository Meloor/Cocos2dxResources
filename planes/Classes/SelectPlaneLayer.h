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

#ifndef __SELECT_PLANE_LAYER_H__
#define __SELECT_PLANE_LAYER_H__

#include "cocos2d.h"
using namespace cocos2d;
class SelectPlaneLayer : public cocos2d::Layer
{
private:
	int page_node_;//几个飞机
	int cur_page_node_;//当前页面
	Point touch_down_point_;//点击时为止
	Point touch_up_point_;//拾起时为止
	Point touch_cur_point_;
	float size_x, size_y;
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
	void goToCurrNode();
	void addNode(Node *level);

	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchMoved(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);

	
    // implement the "static create()" method manually
    CREATE_FUNC(SelectPlaneLayer);
};

#endif // __HELLOWORLD_SCENE_H__

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

#ifndef __SECOND_SCENE_H__
#define __SECOND_SCENE_H__
	
#include "cocos2d.h"
USING_NS_CC;
class Second : public cocos2d::Layer
{
private:
	EventListenerTouchOneByOne* listener;
	Sprite* boxA;
	Sprite* boxB;
	Sprite* boxC;
	Sprite* touchedObject;//当前触摸的子对象
	Sprite* ball;
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	virtual void onEnter();
	virtual void onExit();
    // a selector callback
	//触摸事件回调函数，与父类中的不一样，名称不是自己命名的
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);

	virtual void onAcceleration(Acceleration*acc, Event* event);
	Sprite* setTouchedObject(Touch* touch);//设置层中当前被触摸的子对象。
	void goCallback(Ref* pSender);//返回到前一个场景
    CREATE_FUNC(Second);
};

#endif // __Second_SCENE_H__

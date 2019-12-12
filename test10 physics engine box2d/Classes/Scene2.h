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

#ifndef __Scene2_H__
#define __Scene2_H__

#include "cocos2d.h"
#include "ContactListener.h"
#include "Box2D\Box2D.h"
#define PTM_RATIO 32//像素与米的比例
USING_NS_CC;
class Scene2 : public cocos2d::Layer
{
private:
	b2World* world;
	ContactListener* lis;
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	virtual void update(float dt);
	void initPhysics();//写一个初始化物理引擎的函数

	virtual bool onTouchBegan(Touch* touch, Event*event);
	void addNewSpriteAtPos(Vec2 pos);//在触点生成一个小精灵
    // implement the "static create()" method manually
	void nextMenuCallback(Ref* pSender);
	void backMenuCallback(Ref* pSender);
    CREATE_FUNC(Scene2);
	~Scene2();
};

#endif // __Scene2_SCENE_H__

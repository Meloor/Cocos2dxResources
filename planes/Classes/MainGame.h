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

#ifndef __MainGame_H__
#define __MainGame_H__

#include "cocos2d.h"
USING_NS_CC;
class MainGame : public cocos2d::Layer
{
public:
	Sprite * spr_bg1_;
	Sprite * spr_bg2_;
	Sprite * hero_player_;
public:
    static Scene* createScene();

    virtual bool init();
	void onEnterTransitionDidFinish();
	void onExit();

	void update(float delta);
    
	//单点触摸方法
	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchMoved(Touch *touch, Event * unused_event);
	//初始化玩家飞机
	void init_hero_plane(int index);
	
	void hero_death();
	void hero_player_action_end();
	//添加敌机
	void add_enemy(float delta);
	//添加子弹
	void add_bullet(float tm);
	//碰撞检测
	void is_crash(float tm);
    // implement the "static create()" method manually
    CREATE_FUNC(MainGame);
};

#endif // __MainGame_SCENE_H__

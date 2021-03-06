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

#ifndef __EnemyBase_H__
#define __EnemyBase_H__

#include "cocos2d.h"

class EnemyBase : public cocos2d::Sprite
{
private:
	int enemy_index_;
	int enemy_hp_;
	//�Ƿ�ը
	bool is_death_;
public:

    virtual bool init();
	virtual void onEnterTrnasitionDidFinish();
	virtual void onExit();

	virtual void update(float delta);
	
	void initEnemy(int index = 1);
	void enemy_death();
	void enemy_death_action_end();
	void remove_enemy();
	int get_hp();
	void set_hp(int hp);

    // implement the "static create()" method manually
    CREATE_FUNC(EnemyBase);
};

#endif // __EnemyBase_SCENE_H__

#pragma once
#ifndef __MANAGEBASE_H__
#define __MANAGEBASE_H__

#include "cocos2d.h"
#include "Bullet.h"
#include "EnemyBase.h"
USING_NS_CC;
class ManagerBase
{
private:
	static ManagerBase* manager_;
public:
	Vector<EnemyBase*> enemy_list_;//存的是Enemy对象的指针
	Vector<Bullet*> bullet_list_;
public:
	static ManagerBase* getInstance();
	static void deleteInstance();
public:
	//他们本身就是Vector对象，这可能很大，所以要传递它的地址。
	Vector<EnemyBase*> &getEnemyList() { return enemy_list_; }
	Vector<Bullet*> &getBulletList() { return  bullet_list_; }
	//添加敌机
	void set_enemy_list(EnemyBase* enemy);
	void set_bullet_list(Bullet* bullet);
	void remove_enemy_list(EnemyBase* enemy);
	void remove_bullet_list(Bullet* bullet);
public:
	ManagerBase();
	~ManagerBase();
};
#endif // __StartGame_SCENE_H__



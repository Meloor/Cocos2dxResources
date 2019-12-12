#pragma once
#include "cocos2d.h"
#include "Box2D/Box2D.h"
USING_NS_CC;
class ContactListener :public b2ContactListener {
private:
	virtual void BeginContact(b2Contact* contact);//两物体接触时响应
	virtual void EndContact(b2Contact* contact);//两物体分离时响应
	virtual void PreSolve(b2Contact* contact,const b2Manifold* oldManiFold);//持续接触时响应，它会被多次调用
	virtual void PostSolve(b2Contact* contact,const b2ContactImpulse* impulse);//持续接触时响应，在presolve之后调用
};
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

#include "Bullet.h"
#include "ManagerBase.h"

USING_NS_CC;



bool Bullet::init()
{
	return true;
}
void Bullet::onEnterTransitionDidFinish() {
	Sprite::onEnterTransitionDidFinish();
	scheduleUpdate();
}
void Bullet::onExit() {
	Sprite::onExit();
}
void Bullet::update(float delta) {
	//×Óµ¯ÔË¶¯
	this->setPositionY(this->getPositionY() + 5);
	//ÅÐ¶Ï×Óµ¯ÊÇ·ñÒÆ³ýÆÁÄ»
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (this->getPositionY() > visibleSize.height) {
		this->removeFromParentAndCleanup(true);
		ManagerBase::getInstance()->remove_bullet_list(this);	
	}
}
void Bullet::initBullet(char* bullet_name) {
	auto spr_name = String::createWithFormat("plane/%s", bullet_name);
	this->setTexture(spr_name->getCString());
}



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

#include "MainGame.h"
#include "StartGame.h"
#include "SimpleAudioEngine.h"
#include "EnemyBase.h"
#include "Bullet.h"
#include "ManagerBase.h"
#include "PlaneSupport.h"
#include "SuspandLayer.h"
USING_NS_CC;

Scene* MainGame::createScene()
{
    //return MainGame::create();
	auto scene = Scene::create();
	auto layer = MainGame::create();
	scene->addChild(layer);
	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MainGameScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainGame::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	plane_support_ = NULL;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//背景1
	spr_bg1_ = Sprite::create("ui/bgs.png");
	spr_bg1_->setAnchorPoint(Vec2(0, 0));
	spr_bg1_->setPosition(Vec2(0, 0));
	this->addChild(spr_bg1_);

	//背景2
	spr_bg2_ = Sprite::create("ui/bgs.png");
	spr_bg2_->setAnchorPoint(Vec2(0, 0));
	spr_bg2_->setPosition(Vec2(0, spr_bg1_->getContentSize().height));
	this->addChild(spr_bg2_);

	scheduleUpdate();
	//初始化飞机
	init_hero_plane(1);

	//添加暂停*********************************************************************/
	//添加menu
	auto dictionnary = Dictionary::createWithContentsOfFile("fonts/text.xml");
	auto btn_label = Label::create();
	btn_label->setString(((String*)(dictionnary->objectForKey("suspend")))->getCString());
	btn_label->setSystemFontSize(30);
	auto start_menu = MenuItemLabel::create(btn_label, CC_CALLBACK_1(MainGame::suspend, this));

	auto menu = Menu::create(start_menu, NULL);
	menu->setPosition(Vec2(visibleSize.width - btn_label->getContentSize().width / 2-5,
		visibleSize.height - btn_label->getContentSize().height / 2-5));
	this->addChild(menu);

	//添加暂停*********************************************************************/
	//单点触摸监听器
	auto m_touchListener = EventListenerTouchOneByOne::create();
	m_touchListener->onTouchBegan = CC_CALLBACK_2(MainGame::onTouchBegan, this);
	m_touchListener->onTouchMoved = CC_CALLBACK_2(MainGame::onTouchMoved, this);
	//设置吞噬
	m_touchListener->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()
		->addEventListenerWithSceneGraphPriority(m_touchListener, hero_player_);
    return true;
}
void MainGame::onEnterTransitionDidFinish(){
	Layer::onEnterTransitionDidFinish();
	scheduleUpdate();

	//敌机
	this->schedule(SEL_SCHEDULE(&MainGame::add_enemy), 0.3f);
	//子弹
	this->schedule(SEL_SCHEDULE(&MainGame::add_bullet), 0.09f);
	//碰撞检测
	this->schedule(SEL_SCHEDULE(&MainGame::is_crash));
	//物资
	this->schedule(SEL_SCHEDULE(&MainGame::add_support),9.0f);
}
void MainGame::hero_death()
{
	hero_player_->stopAllActions();
	this->unschedule(SEL_SCHEDULE(&MainGame::add_bullet));
	this->unschedule(SEL_SCHEDULE(&MainGame::is_crash));
	this->unschedule(SEL_SCHEDULE(&MainGame::add_support_bullet));

	auto animation = Animation::create();
	for (int i = 1; i <= 4; i++) {
		auto str_name = String::createWithFormat("plane/b%d.png", i);
		animation->addSpriteFrameWithFile(str_name->getCString());
	}
	animation->setDelayPerUnit(0.2f);
	animation->setLoops(1);

	//hero_player_->runAction(Animate::create(animation));
	hero_player_->runAction(Sequence::create(Animate::create(animation),
		CallFunc::create(CC_CALLBACK_0(MainGame::hero_player_action_end, this)),NULL));
}
void MainGame::hero_player_action_end()
{
	this->unschedule(SEL_SCHEDULE(&MainGame::add_enemy));
	hero_player_->removeFromParentAndCleanup(true);//从场景中移除，没有父对象它就会被加入到对象回收池删除
	//回到主题界面
	Director::getInstance()->replaceScene(TransitionFadeTR::create(0.5, StartGame::createScene()));
}
void MainGame::onExit() {
	unscheduleUpdate();
	Layer::onExit();
}
void MainGame::update(float delta) {
	//实现背景滚动,两个背景图交替出现
	float y1 = spr_bg1_->getPositionY() - 3.0f;//向下移动
	float y2 = spr_bg2_->getPositionY() - 3.0f;

	spr_bg1_->setPositionY(y1);
	spr_bg2_->setPositionY(y2);

	//判断背景图片是否超出边界
	if (y1 < -spr_bg1_->getContentSize().height) {
		spr_bg1_->setPositionY(spr_bg2_->getPositionY() + spr_bg2_->getContentSize().height -2);
	}else if(y2 < -spr_bg2_->getContentSize().height) {
		spr_bg2_->setPositionY(spr_bg1_->getPositionY() + spr_bg1_->getContentSize().height -2);
	}

}

void MainGame::init_hero_plane(int index) {
	//添加动画
	auto animation = Animation::create();
	for (int i = 0; i < 2; i++) {
		auto str_name = String::createWithFormat("plane/heros%d_%d.png", index, i + 1);
		animation->addSpriteFrameWithFile(str_name->getCString());
	}
	animation->setDelayPerUnit(0.5);
	animation->setLoops(-1);
	//创建飞机精灵
	hero_player_ = Sprite::create(String::createWithFormat("plane/heros%d_1.png", index)->getCString());
	auto visibleSize = Director::getInstance()->getVisibleSize();
	hero_player_->setPosition(Vec2(visibleSize.width / 2, hero_player_->getContentSize().height/2));
	this->addChild(hero_player_);
	hero_player_->runAction(Animate::create(animation));
}

bool MainGame::onTouchBegan(Touch *touch, Event *unused_event) {
	log("onTouchBegan");
	//判断点击的区域是否在飞机上
	auto point = touch->getLocation();
	auto rect = hero_player_->getBoundingBox();
	if (rect.containsPoint(point)) {
		return true;
	}
	return false;
}
void MainGame::onTouchMoved(Touch *touch, Event *unused_event) {
	log("onTouchMoved");
	//获取飞机移动的距离
	auto add_point = touch->getLocation() - touch->getPreviousLocation();
	hero_player_->setPosition(hero_player_->getPosition() + add_point);
	//新的获取移动距离的方法,用这个怎么移动不了
	//auto add_point = touch->getDelta();
	//判断飞机一定的距离不要超出边界
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto hero_size = hero_player_->getContentSize();

	//x方向
	if (hero_player_->getPositionX() < hero_size.width / 2) {
		hero_player_->setPositionX(hero_size.width / 2);
	}
	else if (hero_player_->getPositionX() > visibleSize.width -  hero_size.width / 2) {
		hero_player_->setPositionX(visibleSize.width - hero_size.width / 2);
	}
	//y方向
	if (hero_player_->getPositionY() < hero_size.height / 2) {
		hero_player_->setPositionY(hero_size.height / 2);
	}
	else if (hero_player_->getPositionY() > visibleSize.height - hero_size.height / 2) {
		hero_player_->setPositionY(visibleSize.height - hero_size.height / 2);
	}
}

void MainGame::suspend(Ref * ref)
{
	unscheduleUpdate();
	//先把之前不用的纹理删除
	CCTextureCache::getInstance()->removeUnusedTextures();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto texture = RenderTexture::create(visibleSize.width, visibleSize.height);
	//截屏---------------------
	texture->begin();
	//渲染
	Director::getInstance()->getRunningScene()->visit();
	texture->end();
	texture->saveToFile("suspand.png", Image::Format::PNG);
	//-------------------------
	//使用schedule在下一帧调用callback函数
	//截屏时的下一帧
	auto back = [](float dt) {
		//切换到暂停界面
		auto scene = Scene::create();
		auto layer = SuspandLayer::create();
		scene->addChild(layer);
		Director::getInstance()->pushScene(scene);
	};
	//这里创建layer是因为移植android时不能调用主线程中界面的下一帧
	auto layer = Layer::create();
	this->addChild(layer);
	auto schedules = layer->getScheduler();
	schedules->schedule(back,layer, 0.0f, 0, 0.0f, false, "screenshot");
}

void MainGame::add_enemy(float delta) {
	//添加敌机
	int enemy_x = CCRANDOM_0_1() * 9 + 1;//1~10
	if (enemy_x > 6) {//7~10,40%
		enemy_x = 2;
	}else {//1~6
		enemy_x = 1;
	}
	auto enemy = EnemyBase::create(); 
	enemy->initEnemy(enemy_x);
	this->addChild(enemy);
	//将敌机放入管理器
	ManagerBase::getInstance()->set_enemy_list(enemy);
	log("add_enemy");//这条会输出但是没有敌机出现
}
void  MainGame::add_bullet(float tm) {
	auto bullet = Bullet::create();
	bullet->initBullet("bullet1.png");

	auto point = Vec2(hero_player_->getPositionX(),
		hero_player_->getPositionY()+hero_player_->getContentSize().height/2 +10);
	bullet->setPosition(point);

	this->addChild(bullet);
	//将子弹放入管理器
	ManagerBase::getInstance()->set_bullet_list(bullet);
	//log("将子弹放入管理器。");
	log("add bullet");
}

void MainGame::add_support(float tm)
{
	//初始化物资
	plane_support_ = PlaneSupport::create();
	//随机出支援物资的类型
	int index = CCRANDOM_0_1() * 2 + 1;
	support_index_ = index;
	plane_support_->init_support(index);
	this->addChild(plane_support_);
	plane_support_->setTag(index);
}

void MainGame::add_support_bullet(float tm)
{
	//吃到物资后的子弹
	auto bullet = Bullet::create();
	if (support_index_ == 2)
		bullet->initBullet("bullet_suspand2.png");
	else bullet->initBullet("bullet_suspand1.png");

	//加了支援物资的玩家飞机死亡后，会中断，因为玩家飞机死亡后没有关闭add_support_bullet
	auto point = Vec2(hero_player_->getPositionX(),
		hero_player_->getPositionY() + hero_player_->getContentSize().height);
	bullet->setPosition(point);
	this->addChild(bullet);
	ManagerBase::getInstance()->set_bullet_list(bullet);
}

void MainGame::is_crash(float tm)
{
	auto & enemy_list = ManagerBase::getInstance()->getEnemyList();
	auto & bullet_list = ManagerBase::getInstance()->getBulletList();

	//玩家飞机子弹和敌机的碰撞检测
	//倒序遍历,先生成的敌机和子弹会最先碰撞
	for (int i = enemy_list.size() - 1; i >= 0; --i) {
		auto enemy = enemy_list.at(i);
		//它的生命值都为0了怎么还会出现再list中，因为下面它生命值为0时并没有被移除
		if (enemy->get_hp() <= 0) {
			continue;
		}
		auto enemy_size = enemy->boundingBox();
		//子弹遍历
		for (int i = bullet_list.size() - 1; i >= 0; --i) {
			auto bullet = bullet_list.at(i);
			if (enemy_size.containsPoint(bullet->getPosition())) {
				enemy->set_hp(enemy->get_hp() - 1);
				//移除子弹
				bullet->removeFromParentAndCleanup(true);//从MainGame场景中移除
				ManagerBase::getInstance()->remove_bullet_list(bullet);//从list中移除，下次就不会被检测了

				//如果敌机血量为0播放爆炸，为什么不从list中移除
				if (enemy->get_hp() <= 0) {
					enemy->enemy_death();
				}
			}
		}
	}

	//玩家飞机和敌机的碰撞检测
	for (auto i = enemy_list.size() - 1; i >= 0; --i) {
		auto enemy = enemy_list.at(i);
		if (enemy->get_hp() <= 0) {
			continue;
		}
		auto rect = this->hero_player_->getBoundingBox();
		auto point = enemy->getPosition();
		if (rect.containsPoint(point)) {
			hero_death();
		}
	}

	//物资与玩家飞机的碰撞
	if (plane_support_ != NULL) {
		auto rect = hero_player_->getBoundingBox();
		auto point = plane_support_->getPosition();//支援物资走出屏幕后这里会出错
		if (rect.containsPoint(point)) {
			//添加支援物资的子弹
			this->schedule(SEL_SCHEDULE(&MainGame::add_support_bullet), 0.1f,50,0);//50这个参数是设置这个方法调用几次
			//停止普通子弹
			this->unschedule(SEL_SCHEDULE(&MainGame::add_bullet));
			//设置延迟执行添加普通子弹时间
			this->schedule(SEL_SCHEDULE(&MainGame::add_bullet),0.1f,-1,5.0f);//5.0f这个参数是设置这个方法牙齿多久后被调用
			plane_support_->setVisible(false);
			plane_support_ = NULL;
		}
		//这里如果忘了除以2那么当子弹移除屏幕时，它还有一小段时间是没有移除的，如果再调用其getPosition方法就会出错
		if (plane_support_ != NULL && point.y < -plane_support_->getContentSize().height/2) {
			plane_support_->removeFromParent();
			plane_support_ = NULL;
		}
	}
	
}



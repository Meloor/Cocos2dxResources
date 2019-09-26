#include "HelloWorldScene.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//1从大图中直接裁剪
	//auto tree1 = Sprite::create("tree1.png", Rect(604, 38, 302, 295));
	//tree1->setPosition(Vec2(500, 200));
	//this->addChild(tree1, 1);
	//2从纹理缓存中裁剪
	//一个精灵做一个图片会耗费比较多的IO时间，所以一般是若干精灵做成一个大图，一次性
	//读入内存（创建纹理缓存)，然后裁剪出来,这种方法内存会耗费多一些。
	//把大图读入计算机内存中，然后利用纹理缓存反复使用，读入需要的部分
	//存入大图的时候，一般有一个loading的过程。这个时候可以用logo来分散注意力
	//在此过程中会启动一个子线程，进行加载和预处理，后面就比较流畅

	//创建精灵帧缓存
	//auto cache = Director::getInstance()->getTextureCache()->addImage("tree1.png");
	////指定纹理和裁剪矩形区域来创建精灵
	//auto tree2 = Sprite::create();
	//tree2->setTexture(cache);
	//tree2->setTextureRect(Rect(73, 72, 182, 270));
	////创建时直接用纹理缓存来初始化，第三个参数是是否旋转纹理，默认false不旋转
	////auto tree2 = Sprite::createWithTexture(cache,Rect(73, 72, 182, 270),false);
	//tree2->setPosition(Vec2(500, 200));
	//this->addChild(tree2,1);

	//使用精灵帧缓存
	//背景精灵
	auto bg = Sprite::create("background.png");
	//bg->setAnchorPoint(Vec2::ZERO);
	bg->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
	this->addChild(bg, 0);
	//创建精灵帧缓存
	SpriteFrameCache *frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("sprites.plist");
	//通过名字去访问精灵帧缓存中的精灵帧
	auto mountain1 = Sprite::createWithSpriteFrameName("mountain1.png");
	mountain1->setAnchorPoint(Vec2::ZERO);
	mountain1->setPosition(Vec2(-200,80));
	this->addChild(mountain1);
	//先获取精灵帧缓存中的精灵帧，再由精灵帧来创建精灵
	SpriteFrame* heroSF = frameCache->getSpriteFrameByName("hero1.png");
	auto hero = Sprite::createWithSpriteFrame(heroSF);
	hero->setPosition(Vec2(800,200));
	this->addChild(hero);


    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

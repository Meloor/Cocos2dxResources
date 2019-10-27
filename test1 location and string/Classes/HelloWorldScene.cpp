#include "HelloWorldScene.h"
#include "MyUtility.h"
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

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
 //   auto closeItem = MenuItemImage::create(
 //                                          "CloseNormal.png",
 //                                          "CloseSelected.png",
 //                                          CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
 //   
	//closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
 //                               origin.y + closeItem->getContentSize().height/2));

 //   // create menu, it's an autorelease object
 //   auto menu = Menu::create(closeItem, NULL);
 //   menu->setPosition(Vec2::ZERO);
 //   this->addChild(menu, 1);

 //   /////////////////////////////
 //   // 3. add your codes below...

 //   // add a label shows "Hello World"
 //   // create and initialize a label
 //   
 //   auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
 //   
 //   // position the label on the center of the screen
 //   label->setPosition(Vec2(origin.x + visibleSize.width/2,
 //                           origin.y + visibleSize.height - label->getContentSize().height));

 //   // add the label as a child to this layer
 //   this->addChild(label, 1);

 //   // add "HelloWorld" splash screen"
 //   auto sprite = Sprite::create("HelloWorld.png");

 //   // position the sprite on the center of the screen
 //   sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

 //   // add the sprite as a child to this layer
    //this->addChild(sprite, 0);

/*例4.4世界坐标转换为本地坐标******************************************************************/
	//auto  node1 = Sprite::create("Node1.jpg");
	//node1->setAnchorPoint(Vec2(1.0f,1.0f));
	//node1->setPosition(Vec2(400.0f,500.0f));
	//this->addChild(node1,1);

	//auto node2  = Sprite::create("Node1.jpg");
	//node2->setColor(Color3B::RED);
	//node2->setAnchorPoint(Vec2(0.5f,0.5f));
	//node2->setPosition(Vec2(200.0f,300.0f));
	//this->addChild(node2,2);

	//auto node2position = node2->getPosition();
	//auto point3 = node1->convertToNodeSpace(node2position);
	//auto point4 = node1->convertToNodeSpaceAR(node2position);
	//log("point3(%lf,%lf)",point3.x,point3.y);
	//log("point4(%lf,%lf)",point4.x,point4.y);
/*例4.5本地坐标转换为世界坐标******************************************************************/
	//auto  node1 = Sprite::create("Node1.jpg");
	//node1->setAnchorPoint(Vec2(0.0,0.0));
	//node1->setPosition(Vec2(400.0f,500.0f));
	//this->addChild(node1,1);

	//auto node2  = Sprite::create("Node2.jpg");
	//node2->setAnchorPoint(Vec2(0.0,0.0));
	//node2->setPosition(Vec2(0.0f,0.0f));
	//node1->addChild(node2,2);

	//auto node2position = node2->getPosition();
	//log("node2position(%lf,%lf)",node2position.x,node2position.y);
	//auto point1 = node1->convertToWorldSpace(node2position);
	//auto point2 = node1->convertToWorldSpaceAR(node2position);
	//log("point1(%lf,%lf)",point1.x,point1.y);
	//log("point2(%lf,%lf)",point2.x,point2.y);


/*例4.5本地坐标转换为世界坐标2******************************************************************/
	//auto node0 = Sprite::create("Node0.jpg");
	//node0->setAnchorPoint(Vec2(0.0f,0.0f));
	//node0->setPosition(Vec2(100.0f,100.0f));
	//this->addChild(node0,1);

	//auto  node1 = Sprite::create("Node1.jpg");
	//node1->setAnchorPoint(Vec2(0.5,0.5));
	//node1->setPosition(Vec2(400.0f,500.0f));
	//node0->addChild(node1,1);

	//auto node2  = Sprite::create("Node2.jpg");
	//node2->setAnchorPoint(Vec2(0.0,0.0));
	////node2->setAnchorPoint(Vec2(1.0,1.0));
	////node2->setAnchorPoint(Vec2(0.5,0.5));
	//node2->setPosition(Vec2(50.0f,50.0f));
	//node1->addChild(node2,2);

	//auto node1position = node1->getPosition();
	//auto node2position = node2->getPosition();
	//log("node2position(%lf,%lf)",node2position.x,node2position.y);
	//auto point1 = node1->convertToWorldSpace(node2position);
	////将局部Vec2转换为世界空间坐标。
	////The result is in Points. treating the returned/received node point as anchor relative
	////结果是以点为单位的。将返回/接收的节点视为相对锚点。
	//auto point2 = node1->convertToWorldSpaceAR(node2position);//返回其父对象的锚点的世界坐标
	////将Vec2转换为世界空间坐标。
	//auto point3 = node1->convertToNodeSpace(node2position);
	//auto point4 = node1->convertToNodeSpaceAR(node2position);

	//auto point5 = node0->convertToWorldSpace(node1position);
	//auto point6 = node0->convertToWorldSpaceAR(node1position);
	//log("point1(%lf,%lf)",point1.x,point1.y);
	//log("point2(%lf,%lf)",point2.x,point2.y);
	////log("point3(%lf,%lf)",point3.x,point3.y);
	////log("point4(%lf,%lf)",point4.x,point4.y);
	//log("point5(%lf,%lf)",point5.x,point5.y);
	//log("point6(%lf,%lf)",point6.x,point6.y);
/*实例4.1.3字符串*******************************************************************************************/    
	//std::string  name  = "tony";
	////std::string name  = std::string("tony");
	//log("name = %s", name);
	//log("name = %s",name.c_str());//将string类型的字符串转换为const char *类型

	////使用指针的用法
	//std::string * name2 = new std::string("tony");
	//log("name = %s",name2->c_str());

	////使用__String
	////cocos2d::__String转换为const char*类型
	//__String* name3 = __String::create("Hi,Tony");
	//const char *cstring = name3->getCString();

	////const char*转换为cocos2d::__String类型，示例代码如下：
	//const char* cstring2 = "Hi,Tony";
	//__String* ns=__String::createWithFormat("%s",cstring2);

	////std::string转换为cocos2d::__String类型，示例代码如下：
	//std::string string = "Hi,Tony";
	//__String* ns2=__String::createWithFormat("%s",string.c_str());

	////cocos2d::__String 转换为int类型：
	//int num=123;
	//__String* ns3=__String::createWithFormat("%d",num);
	//int num2=ns3->intValue();

	////createWithFormat不但可以转换字符串，还可以将一个整数转换成字符串
	//int num3 = 123;
	//__String *name4 = __String::createWithFormat("%d",num3);
	//log("%s",name4->getCString());
/*win32平台下乱码问题*****************************************************************/
	std::string string = "大家好啊";
	log("%s",string.c_str());
	//解决方法一 文末加句号
	std::string s2 = "大家好 ";
	log("%s",s2.c_str());
	//方法2 使用MyUtility类中的转码方法
	__String* ns = __String::create("大家好");
	const char* cns;
	#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		 std::string sns = MyUtility::gbk_2_utf8(ns->getCString());
		 cns = sns.c_str();
	#else
		cns = ns->getCString();
	#endif
	log("%s",cns);
	auto label = LabelTTF::create(cns,"Arial",24);

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

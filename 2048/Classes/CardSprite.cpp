#include "CardSprite.h"
void CardSprite::cardInit(int numbers, int width, int height) {
	//初始化数字
	number = numbers;
	//加入游戏卡片的背景颜色块，留了15像素的空余位置，四个方向各7.5。
	layerColorBG = LayerColor::create(Color4B(200, 190, 180, 255), width - 15, height - 15);
	/*layerColorBG应该在sprite的正中间，而由于无论怎么设置anchorPoint显示时都相当于是（0,0）
	所以x,y轴在原点的基础上偏移间隔的一般。*/
	layerColorBG->setPosition(Point(7.5, 7.5));
	//加入字体
	const char* label_str = "";
	if (number > 0)//判断如果不等于0就显示，否则为空 
		label_str = String::createWithFormat("%i", number)->getCString();		
	labelCardNumber = Label::createWithSystemFont(
			label_str, "HirakakuProN-W6", 100);	
	labelCardNumber->setPosition(Point(layerColorBG->getContentSize().width / 2,
		layerColorBG->getContentSize().height / 2));
	layerColorBG->addChild(labelCardNumber);
	this->addChild(layerColorBG);
}
//该函数和常见的 类名::create() 函数很类似，都是静态的创建实例的方法
CardSprite* CardSprite::createCardSprite(int numbers, int width, int height) {
	CardSprite * card = new CardSprite();
	if (card&&card->init()) {//调用父类的init函数
		card->autorelease();//添加到自动释放池
		card->cardInit(numbers, width, height);
		return card;
	}
	else {
		CC_SAFE_DELETE(card);//初始化失败就删除
		return NULL;
	}
}
bool CardSprite::init() {
	if (!Sprite::init()) {
		return false;
	}
	return true;
}
int CardSprite::getNumber() {
	return number;
}
void CardSprite::setNumber(int num) {
	number = num;

	//根据数字的大小来调整字体的大小
	if (number >= 0)
		labelCardNumber->setSystemFontSize(90);
	if(number>= 10)
		labelCardNumber->setSystemFontSize(70);
	if(number>=100)
		labelCardNumber->setSystemFontSize(50);
	if(number>=1000)
		labelCardNumber->setSystemFontSize(30);

	//根据数字大小来调整颜色
	switch (number)
	{
	case 0:layerColorBG->setColor(Color3B(200, 190, 180)); break;
	case 2:layerColorBG->setColor(Color3B(240, 230, 220)); break;
	case 4:layerColorBG->setColor(Color3B(240, 220, 200)); break;
	case 8:layerColorBG->setColor(Color3B(240, 180, 120)); break;
	case 16:layerColorBG->setColor(Color3B(240, 140, 90)); break;
	case 32:layerColorBG->setColor(Color3B(240, 120, 90)); break;
	case 64:layerColorBG->setColor(Color3B(240, 90, 60)); break;
	case 128:layerColorBG->setColor(Color3B(240, 90, 60)); break;
	case 256:layerColorBG->setColor(Color3B(240, 200, 70)); break;
	case 512:layerColorBG->setColor(Color3B(240, 200, 70)); break;
	case 1024:layerColorBG->setColor(Color3B(0, 130, 0)); break;
	case 2048:layerColorBG->setColor(Color3B(0, 130, 0)); break;
	default:
		break;
	}

	//更新显示的数字
	if (number > 0) {
		labelCardNumber->setString(String::createWithFormat("%i", number)->getCString());
	}
	else {
		labelCardNumber->setString("");
	}
}

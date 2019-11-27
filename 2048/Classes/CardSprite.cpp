#include "CardSprite.h"
void CardSprite::enemyInit(int numbers, int width, int height) {
	//初始化数字
	number = numbers;
	//加入游戏卡片的背景颜色块，留了15像素的空余位置，四个方向各7.5。
	layerColorBG = LayerColor::create(Color4B(200, 190, 180, 255), width - 15, height - 15);
	/*layerColorBG应该在sprite的正中间，而由于无论怎么设置anchorPoint显示时都相当于是（0,0）
	所以x,y轴在原点的基础上偏移间隔的一般。*/
	layerColorBG->setPosition(Point(7.5, 7.5));

	////加入字体
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
CardSprite* CardSprite::createCardSprite(int numbers, int width, int height) {
	CardSprite * enemy = new CardSprite();
	if (enemy&&enemy->init()) {
		enemy->autorelease();//这里是干什么的
		enemy->enemyInit(numbers, width, height);
		return enemy;
	}
	CC_SAFE_DELETE(enemy);//初始化失败就删除
	return NULL;
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

	//更新显示的数字
	if (number > 0) {
		labelCardNumber->setString(String::createWithFormat("%i", number)->getCString());
	}
	else {
		labelCardNumber->setString("");
	}
}
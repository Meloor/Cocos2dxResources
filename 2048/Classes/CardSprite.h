
#ifndef __CardSprite_H__
#define __CardSprite_H__

#include "cocos2d.h"
USING_NS_CC;
class CardSprite : public cocos2d::Sprite
{
private:
	int number;//显示在界面中的数字
	Label* labelCardNumber;//数字标签
	LayerColor* layerColorBG;//颜色块
private:
	void cardInit(int numbers, int width, int height);
public:
	//静态函数，用于创建卡片精灵
	static CardSprite* createCardSprite(int numbers,int width,int height);
	virtual bool init();
	CREATE_FUNC(CardSprite);
	int getNumber();
	void setNumber(int num);
};

#endif // __CardSprite_H__

#pragma once
// 左
void isLeft() {
	/**
	* 这里的逻辑有三种情况 
	1.左边为空，直接左滑到最后一格 
	2.左边碰到的第一个数是相等的，就相加 
	3.左边碰到的第一个数是不相等的，靠在旁边

	先移动，再合并，
	2024->0224->0008

	*/
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			// 往左滑是一行一行去遍历的
			for (int j2 = j + 1; j2 < 4; j2++) {
				// 如果说遍历到值
				if (cards[j2][i].getNum() > 0) {
					// 如果当前位置上为0,就放在这个位置上去
					if (cards[j][i].getNum() <= 0) {
						cards[j][i].setNum(cards[j2][i].getNum());
						// 把原来位置上的数字清除
						cards[j2][i].setNum(0);
						// 让图形继续遍历
						j--;

						// 有值，并且还相同
					}
					else if (cards[j][i].equals(cards[j2][i])) {
						// 合并,这里做了一个很巧妙的写法，我们相加，其实2048方块上的数字都是双倍的，
						//所以我们只要原数据*2就可以了
						cards[j][i].setNum(cards[j][i].getNum() * 2);
						// 把原来位置上的数字清除
						cards[j2][i].setNum(0);

					}
					break;
				}
			}
		}
	}
}
/******************************************************************/
bool  HelloWorld::doLeft() {
	log("go left");
	/*
	理一下游戏的逻辑，往左划时
	step1:所有的card都会往左移（跳过值为0的card),在左边互相紧靠。
	step2:肯定是左边的先合并，如果有相同的就合并，合并后又会有空card,空card后面的card要填补空card的位置。
	*/
	bool isdo = false;
	for (int y = 0; y < 4; y++) {
		//bool flag = true;
		//while (flag) {
		//	int x_num = 4;
		//	for (int x = 0; x < x_num; x++) {
		//		//如果这个格子为空，后面的都往前移
		//		if (cardArr[x][y]->getNumber() == 0) {
		//			for (int x1 = x + 1; x1 < x_num; x1++) 
		//				cardArr[x1 - 1][y]->setNumber(cardArr[x1][y]->getNumber());		
		//			cardArr[3][y]->setNumber(0);
		//			x_num--;//移动后，最后一个是空，后面无需再判断了
		//		}
		//		//如果格子非空，那么判断合并，用if而不用else是因为移动后可能非空
		//		if(cardArr[x][y]->getNumber() != 0){
		//			for (int x1 = x + 1; x1 < x_num; x1++) {
		//				if (cardArr[x][y]->getNumber() == cardArr[x1][y]->getNumber()) {
		//					cardArr[x][y]->setNumber(cardArr[x][y]->getNumber() * 2);
		//					cardArr[x1][y]->setNumber(0);
		//				}
		//				else break;//不相等就啥也不做
		//			}
		//		}
		//	}
		//}


		for (int x = 0; x < 4; x++) {//合并到x
									 //遍历到x,card从右往前移，与x最近的(x+1)先和x进行迭代判断
									 //判断到底是要进行迭代还是清空
			for (int x1 = x + 1; x1 < 4; x1++) {//x1是被合并的格子
				if (cardArr[x1][y]->getNumber()>0) {//x1非空
													//x为空，x1移动到x的位置，x1原位置置空
													//例子，x=0,x1=1,[0,2,2,2],向左滑动后[2,0,2,2],x1=2,[4,0,0,2],x1=3,[4,0,0,2]
													//x为空只会在里层for中出现一次，第一次过后就会被设置为非空。
					if (cardArr[x][y]->getNumber() <= 0) {
						cardArr[x][y]->setNumber(cardArr[x1][y]->getNumber());
						cardArr[x1][y]->setNumber(0);
						//x--;//然后下一个x1判断时会读取cardArr[-1][y]产生中断，如[0,2,4,8]

						//log("x=%d", x);		
						isdo = true;
					}//x非空，判断是否与x相同,相同则合并到x
					else if (cardArr[x][y]->getNumber() == cardArr[x1][y]->getNumber()) {
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber() * 2);
						//合并到x后，x1置为空，然后下一个x1与x进行判断，如果相同会继续合并
						//如[2,2,4,4]合并的最终结果为[8,0,0,4]
						cardArr[x1][y]->setNumber(0);
						isdo = true;
					}//x非空且和x1不同，什么都不做，x1停在原处
					break;
				}//x1为空什么都不做
			}
		}
	}
	return isdo;
}
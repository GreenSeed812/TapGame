#ifndef _ShopData_H_
#define _ShopData_H_
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include<cocos2d.h>
using namespace cocos2d;
using namespace  rapidjson;
struct ItemData
{
	bool isUsing;
	int itemNum;
	int ID;
	float leftTime;
};
class ShopData
{
public:
	static ShopData* getInstance();
	void useItemByID(int);
	void buyItemByID(int);
	int getShopGold(){ return m_shopGold; }
	void stopItemById(int i);
	void subShopGold(int gold);
	void addShopGold(int gold);
	bool getItemBeUsedById(int id);
	int getCount(int id);
	ItemData * getItemDataById(int id);
	void readUserData();
	void saveUserData(Document& document);
private:
	void init();
	ShopData();
	~ShopData();
	int m_shopGold;
	ItemData* m_items[13];
};


#endif


//海潮图腾
//闪电图腾
//火舌图腾
//风怒图腾
//地精银行押运事故
//坚持神力
//技能刷新
//进阶佣兵
//神器升星
//转生礼包
//死从天降
//藏宝海湾的宝箱
//幸运硬币
//狂乱攻击

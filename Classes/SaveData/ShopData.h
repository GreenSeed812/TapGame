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
	int getNum(int id){ return m_num[id]; };
	void setNum(int id);
	ItemData * getItemDataById(int id);
	void readUserData();
	void saveUserData(Document& document);
private:
	void init();
	ShopData();
	~ShopData();
	int m_shopGold;
	int m_num[13];
	ItemData* m_items[13];
};


#endif


#ifndef _ShopData_H_
#define _ShopData_H_
#include<cocos2d.h>
class ShopData
{
public:
	static ShopData* getInstance();
	int getShopGold(){ return m_shopGold; }
	void subShopGold(int gold){ m_shopGold -= gold; cocos2d::CCNotificationCenter::getInstance()->postNotification("arResetChange"); }
	void addShopGold(int gold){ m_shopGold += gold; cocos2d::CCNotificationCenter::getInstance()->postNotification("arResetChange"); }
private:
	ShopData();
	~ShopData();
	int m_shopGold;

};


#endif
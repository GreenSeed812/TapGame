#ifndef _ShopData_H_
#define _ShopData_H_
class ShopData
{
public:
	static ShopData* getInstance();
	int getShopGold(){ return m_shopGold; }
	void subShopGold(int gold){ m_shopGold -= gold; }
	void addShopGold(int gold){ m_shopGold += gold; }
private:
	ShopData();
	~ShopData();
	int m_shopGold;

};


#endif
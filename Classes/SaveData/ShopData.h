#ifndef _ShopData_H_
#define _ShopData_H_
#include<cocos2d.h>
class ShopData
{
public:
	static ShopData* getInstance();
	void useItemByID(int);
	void buyItemByID(int);
	int getShopGold(){ return m_shopGold; }
	void subShopGold(int gold){ m_shopGold -= gold; }
	void addShopGold(int gold){ m_shopGold += gold; }
	bool getItemBeUsedById(int id);
private:
	ShopData();
	~ShopData();
	bool m_haichaoS;
	bool m_shandianS;
	bool m_huosheS;
	bool m_fengnuS;
	bool m_bankS;
	bool m_keepGodPowerS;
	bool m_refreshS;
	bool m_whosyourdaddyS;
	bool m_luckyCoinS;
	bool m_kuangluanS;
	bool m_relifeS;
	int m_shopGold;
	int m_haiChao;
	int m_shandian;
	int m_huoshe;
	int m_fengnu;

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

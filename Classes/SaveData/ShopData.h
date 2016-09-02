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
	bool getHaichaoS(){ return m_haichaoS; }
	bool getShandianS(){ return m_shandianS; }
	bool getHuosheS(){ return m_huosheS; }
	bool getFengnuS(){ return m_fengnuS; }
	bool getjianchiS(){ return m_jianchiS; }
	bool getshuaxinS(){ return m_shuaxinS; }
	bool getmiaoshaS(){ return m_miaoshaS; }
	bool getcangbaohaiwanS(){ return m_cangbaohaiwanS; }
	bool getxingyunS(){ return m_xingyunS; }
	bool getkuangluanS(){ return m_kuangluanS; }
private:
	ShopData();
	~ShopData();
	bool m_haichaoS;
	bool m_shandianS;
	bool m_huosheS;
	bool m_fengnuS;
	bool m_bankS;
	bool m_jianchiS;
	bool m_shuaxinS;
	bool m_miaoshaS;
	bool m_cangbaohaiwanS;
	bool m_xingyunS;
	bool m_kuangluanS;
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

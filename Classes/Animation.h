#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <cocos2d.h>
using namespace cocos2d;

class MyAnimation : public cocos2d::Node
{
public:
	static MyAnimation * getInstance();
	void runHarmer(bool,Node *);
	void runAoshu(bool, Node*);
	void initXiangyunani();
	void initZhisiani();
	void initShizijun();
	void initKuaisusheji();
	void initBaofengxueani();
	void initshixie();
	void initshixiekuang();
	void inittouqie();
	void initkuangluan();
	void initbaodian();
	Animate* getAnimate_xy();
	Animate* getAnimate_zs();
	Animate* getAnimate_szj();
	Animate* getAnimate_kssj();
	Animate* getAnimate_bfx();
	Animate* getAnimate_sx();
	Animate* getAnimate_sxk();
	Animate* getAnimate_tq();
	Animate* getAnimate_kl();
	Animate* getAnimate_bd();
	void setPos();
	bool getKSSJplaying(){ return m_kssj; }
	bool getKLGJplaying(){ return m_klgj; }
	void setKSSJplaying(bool kssj){ m_kssj = kssj; }
	void setKLGJplaying(bool klgj){ m_klgj = klgj; }
private:
	MyAnimation();
	Animation* m_harmaer;
	Animation* m_aoshu;
	static MyAnimation * m_animation;
	Animation* m_xiangyunani;
	Animation* m_zhisiani;
	Animation* m_shizijunani;
	Animation* m_kuaisusheji;
	Animation* m_baofengxueani;
	Animation* m_shixieani;
	Animation* m_shixiekuangani;
	Animation* m_touqieani;
	Animation* m_kuangluanani;
	Animation* m_baodian;
	bool m_kssj;
	bool m_klgj;
};


#endif
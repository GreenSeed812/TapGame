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
	Animate* getAnimate_xy();
	Animate* getAnimate_zs();
	Animate* getAnimate_szj();
	Animate* getAnimate_kssj();
	Animate* getAnimate_bfx();
	Animate* getAnimate_sx();
	Animate* getAnimate_sxk();
	Animate* getAnimate_tq();
	void setPos();
	bool getKSSJplaying(){ return m_kssj; }
	void setKSSJplaying(bool kssj){ m_kssj = kssj; }
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
	bool m_kssj;
};


#endif
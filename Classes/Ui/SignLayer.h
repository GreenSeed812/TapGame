#ifndef _SignLayer_H_
#define _SignLayer_H_
#include <cocos2d.h>
USING_NS_CC;

class SignLayer :public cocos2d::Layer
{
public:
	virtual bool init();
	void initSignLayer();
	bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*){ return true; }
	CREATE_FUNC(SignLayer);

private:
	cocos2d::Node* rootNode;
	int m_day;
	tm * m_time;
	bool m_state;
	void signChange(Ref*);
	void stateChange();
	void dayChange();
	void reset();
	void btnChange();
	bool checkDay();
	LayerColor * m_bgLayer;
	cocos2d::ValueMap m_strings;
	int m_Rate;
};


#endif
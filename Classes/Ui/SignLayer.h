#ifndef _SignLayer_H_
#define _SignLayer_H_
#include <cocos2d.h>
using namespace cocos2d;
class SignLayer :public cocos2d::Layer
{
public:
	virtual bool init();
	void initSignLayer();
	bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*){ return true; }
	CREATE_FUNC(SignLayer);

private:
	cocos2d::Node* rootNode;
	bool m_receive1;
	bool m_receive2;
	bool m_receive3;
	bool m_receive4;
	bool m_receive5;
	bool m_receive6;
	bool m_receive7;
	int m_day;
	void signChange(Ref*);
	cocos2d::ValueMap m_strings;
};


#endif
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
	int m_day;
	void signChange(Ref*);
	cocos2d::ValueMap m_strings;
};


#endif
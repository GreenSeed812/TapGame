#ifndef _SignLayer_H_
#define _SignLayer_H_
#include <cocos2d.h>
class SignLayer :public cocos2d::Layer
{
public:
	virtual bool init();
	void initSignLayer();
	bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*){ return true; }
	CREATE_FUNC(SignLayer);

private:
	cocos2d::Node* rootNode;

};


#endif
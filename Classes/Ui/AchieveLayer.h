#ifndef _AchieveLayer_H_
#define _AchieveLayer_H_
#include <cocos2d.h>
class AchieveLayer :public cocos2d::Layer
{
public:
	virtual bool init();
	bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*){ return true; }
	CREATE_FUNC(AchieveLayer);

private:
	cocos2d::Node* rootNode;

};



#endif
#ifndef _SettingLayer_H_
#define _SettingLayer_H_
#include <cocos2d.h>
class settingLayer:public cocos2d::Layer
{
public:
	virtual bool init();
	bool onTouchBegan(cocos2d::Touch*,cocos2d::Event*){ return true; }
	CREATE_FUNC(settingLayer);

private:
	cocos2d::Node* rootNode;
};



#endif
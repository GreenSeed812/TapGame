#ifndef _SettingLayer_H_
#define _SettingLayer_H_
#include <cocos2d.h>
#include "BgMusic.h"
class settingLayer:public cocos2d::Layer
{
public:
	virtual bool init();
	bool onTouchBegan(cocos2d::Touch*,cocos2d::Event*){ return true; }
	static void setOff_On(bool bg, bool sound){ m_mus_off_on = bg; m_sou_off_on = sound; };
	CREATE_FUNC(settingLayer);

private:
	cocos2d::Node* rootNode;
	static bool m_mus_off_on;
	static bool m_sou_off_on;
};



#endif
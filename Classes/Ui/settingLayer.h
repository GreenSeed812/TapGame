#ifndef _SettingLayer_H_
#define _SettingLayer_H_
#include <cocos2d.h>
#include "BgMusic.h"
class settingLayer:public cocos2d::Layer
{
public:
	virtual bool init();
	bool onTouchBegan(cocos2d::Touch*,cocos2d::Event*){ return true; }
	static void setNode(Node * node){ g_node = node; };
	CREATE_FUNC(settingLayer);
private:
	cocos2d::Node* rootNode;
	static Node * g_node;
	bool m_mus_off_on;
	bool m_sou_off_on;
	LayerColor * m_bgLayer;
};



#endif
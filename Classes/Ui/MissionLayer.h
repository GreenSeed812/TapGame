#ifndef _MissionLayer_H_
#define _MissionLayer_H_
#include <cocos2d.h>
USING_NS_CC;
class MissionLayer :public cocos2d::Layer
{
public:
	virtual bool init();
	bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*){ return true; }
	CREATE_FUNC(MissionLayer);

private:
	cocos2d::Node* rootNode;
	void initMission();
	bool m_suc;
	LayerColor * m_bgLayer;

};


#endif
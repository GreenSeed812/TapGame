#ifndef _AchieveLayer_H_
#define _AchieveLayer_H_
#include <cocos2d.h>
using namespace cocos2d;
class AchieveLayer :public cocos2d::Layer
{
public:
	virtual bool init();
	void initAchieveLayer();
	bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*){ return true; }
	CREATE_FUNC(AchieveLayer);

private:
	Node* m_rootNode;
	Node * m_bg;
	LayerColor * m_bgLayer;
	void achieveChange(Ref*);
};



#endif
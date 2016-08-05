#ifndef _ClickLayer_H_
#define _ClickLayer_H_
#include<cocos2d.h>

using namespace cocos2d;
class ClickLayer :public Layer
{
public:
	virtual bool init();
	virtual bool onTouchBegan(Touch *touch, Event*);
	void onTouchMoved(Touch *touch, Event*);
	void onTouchEnded(Touch *touch, Event*);
	void onTouchCanceled(Touch *touch, Event*);
	void normalAtk();
	CREATE_FUNC(ClickLayer);
	EventListenerTouchOneByOne *touchListener;
	void setTouchEnabled(bool boolean){ touchListener->setEnabled(boolean); }
	void attackeffection();
private:
	int m_clickPerSecond;
	
	Animation* ani;
};


#endif
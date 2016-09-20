#ifndef _ClickLayer_H_
#define _ClickLayer_H_
#include<cocos2d.h>
#include<cocostudio/CocoStudio.h>
using namespace cocos2d;
using namespace cocostudio;
class ClickLayer :public Layer
{
public:
	virtual bool init();
	virtual bool onTouchBegan(Touch *touch, Event*);
	void onTouchEnded(Touch *touch, Event*);
	void onTouchCanceled(Touch *touch, Event*);
	void deleteArmature(Armature * armature, MovementEventType type, const std::string& action);
	CREATE_FUNC(ClickLayer);
	EventListenerTouchOneByOne *touchListener;
	void setTouchEnabled(bool boolean){ touchListener->setEnabled(boolean); }
	
private:
	int m_clickPerSecond;
	Armature* m_armature;
	
};


#endif
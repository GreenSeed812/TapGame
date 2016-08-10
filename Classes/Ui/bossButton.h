#ifndef _bossButton_H_
#define _bossButton_H_
#include <cocos2d.h>
using namespace cocos2d;
class bossButton :public Layer
{
public:
	bossButton();
	~bossButton();
	bool init();
	bool onTouchBegan(Touch *touch, Event*);
	void onTouchEnded(Touch *touch, Event*);
	CREATE_FUNC(bossButton);
private:
	EventListenerTouchOneByOne* touchListener;
	int i;
	Sprite * m_sprite;
};



#endif
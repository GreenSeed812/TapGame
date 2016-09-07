#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <cocos2d.h>
using namespace cocos2d;

class MyAnimation : public cocos2d::Node
{
public:
	static MyAnimation * getInstance();
	void runHarmer(bool,Node *);
	void runAoshu(bool, Node*);
	void setPos();
private:
	MyAnimation();
	Animation* m_harmaer;
	Animation* m_aoshu;
	static MyAnimation * m_animation;
};


#endif
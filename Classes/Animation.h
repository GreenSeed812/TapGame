#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <cocos2d.h>
using namespace cocos2d;

class MyAnimation : public cocos2d::Node
{
public:
	static MyAnimation * getInstance();
	void runHarmer(bool,Node *);
private:
	MyAnimation();
	Animation* m_harmaer;
	static MyAnimation * m_animation;
};


#endif
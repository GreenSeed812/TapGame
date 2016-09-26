#ifndef _ARSTAR_UP_H_
#define _ARSTAR_UP_H_

#include <cocos2d.h>
USING_NS_CC;

class ArStarUp : public Layer
{
public:
	bool init(int);
	static ArStarUp* getInstance();
	static ArStarUp * g_asu;
private:
	Node * m_node;
	
};

#endif
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
	void setNode(Node * node){ m_mainNode = node; }
private:
	Node * m_node;
	Node * m_mainNode;
	LayerColor * m_bgLayer;
	void arCallBack(Node *);
};

#endif
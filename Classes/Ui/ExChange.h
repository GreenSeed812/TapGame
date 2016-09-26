
#ifndef _EXCHANGE_H_
#define _EXCHANGE_H_

#include <cocos2d.h>
#include "Tool/MyNum.h"
using namespace cocos2d;

class ExChange : public cocos2d::Layer
{
public:
	bool init();
	void initExchange();
	void setNode(Node * node){ g_node = node; }
	void exChange(Ref*);
	void callback(Node * node);
	static void setCount(int count){ g_countNow = count; };
	CREATE_FUNC(ExChange);
private:
	Node * m_rootNode;
	static int g_countNow;
	int m_countMax;
	int m_money;
	MyNum m_gold;
	LayerColor * m_bgLayer;
	static Node * g_node;
};


#endif
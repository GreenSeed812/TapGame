
#ifndef _ACHIEVEITEM_H_
#define _ACHIEVEITEM_H_

#include <cocos2d.h>
#include "Tool/MyNum.h"
using namespace cocos2d;

class AchieveItem :public cocos2d::Layer
{
public:
	virtual bool init();
	void initAchieveItem(int id);
	static void setNode(Node * node){ g_node = node; }
	CREATE_FUNC(AchieveItem);
private:
	int m_id;
	int m_money;
	int m_starNum;
	bool m_starUp;
	bool m_starUped;
	bool m_click;
	MyNum m_countMax;
	static Node * g_node;
	Node * m_node;
};
#endif
#ifndef _ITEMLAYER_H_
#define _ITEMLAYER_H_
#include <cocos2d.h>
using namespace cocos2d;

class ItemLayer : public cocos2d::Layer
{
public:
	bool init();
	void initItemLayer(int id);
	void itemChange(Ref*);
	CREATE_FUNC(ItemLayer);
private:
	Node * m_rootNode;
	Node * m_layer;
	float m_time;
	int m_id;
	void timeCalculate();
	void btnChange();
};

#endif
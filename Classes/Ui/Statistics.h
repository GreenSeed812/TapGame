
#ifndef _STATISTICS_H_
#define _STATISTICS_H_

#include <cocos2d.h>
using namespace cocos2d;

class Statistics : public cocos2d::Layer
{
public:
	bool init();
	void initStatistics();
	void statisticsChange(Ref * ref);

	CREATE_FUNC(Statistics);

private:
	Node* m_rootNode;
	Node * m_layer;
	LayerColor * m_bgLayer;
};


#endif
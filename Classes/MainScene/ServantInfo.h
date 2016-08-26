
#ifndef _SERVANTINFO_H
#define _SERVANTINFO_H
#include "Tool/MyNum.h"
#include <cocos2d.h>
using namespace cocos2d;
class ServantInfo : public Layer
{
public:
	bool init();
	void initServantInfo(int id);
	CREATE_FUNC(ServantInfo);
private:
	Node * m_node;
	Layer* m_layer;
};


#endif
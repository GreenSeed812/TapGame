
#ifndef _RELIFE_H_
#define _RELIFE_H_
#include "Tool/MyNum.h"
#include <cocos2d.h>
using namespace cocos2d;

class Relife : public Layer
{
public:
	bool init();
	void initRelife();
	CREATE_FUNC(Relife);
private:
	Node * m_node;
	Layer* m_layer;
};


#endif
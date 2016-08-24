
#ifndef _ARRESET_H_
#define _ARRESET_H_

#include <cocos2d.h>
#include "Tool/MyNum.h"
using namespace cocos2d;

class ArReset : public Layer
{
public:
	bool init();
	void initArResetLayer(int id);
	CREATE_FUNC(ArReset);
private:
	Node * m_node;
	Layer* m_layer;
	int m_id;
};

#endif
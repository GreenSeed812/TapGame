
#ifndef _PLAYERINFO_H_
#define _PLAYERINFO_H_

#include <cocos2d.h>
#include "Tool/MyNum.h"
using namespace cocos2d;

class PlayerInfo : public Layer
{
public:
	bool init();
	void initPlayerInfo();
	CREATE_FUNC(PlayerInfo);
private:
	Node * m_node;
	Layer* m_layer;
	LayerColor * m_bgLayer;
};


#endif
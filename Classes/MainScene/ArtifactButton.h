#ifndef _ArtifactButton_H_
#define _ArtifactButton_H_

#include <cocos2d.h>
#include "Tool/MyNum.h"
using namespace cocos2d;

class ArtifactButton : public Layer
{
public:
	bool init();
	void initArtifactLayer(int);
	//void coinChange(Ref*);
	static void getListView(Node* lv){ g_lv = lv; }
	CREATE_FUNC(ArtifactButton);

private:
	Node* node;
	MyNum m_gold;
	MyNum m_baseDps;
	MyNum m_dps;
	Layer* m_layer;
	static Node* g_lv;
	int m_id;
};


#endif
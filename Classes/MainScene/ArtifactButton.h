#ifndef _ArtifactButton_H_
#define _ArtifactButton_H_

#include <cocos2d.h>
#include "Tool/MyNum.h"
using namespace cocos2d;

class ArtifactButton : public Layer
{
public:
	bool init();
	void initArtifactLayer();
	void coinChange(Ref*);
	static void getListView(Node* lv){ g_lv = lv; }
	static void getRootNode(Node * node){ g_node = node; };
	CREATE_FUNC(ArtifactButton);

private:
	Node* node;
	static Node * g_node;
	int m_lhs;
	MyNum m_baseDps;
	MyNum m_dps;
	Layer* m_layer;
	static Node* g_lv;
	int m_id;
	bool onTouchBegan(Touch *, Event*);
	void onTouchEnded(Touch *, Event *);

};


#endif
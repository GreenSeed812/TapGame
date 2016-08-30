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
	void arChange(Ref*);
	static void setListView(Node* lv){ g_lv = lv; }
	static void setRootNode(Node*node){ g_node = node;};
	static void setArButtonNode(Node * btn){ g_button = btn; }
	static void setWidget(Node * node){ g_widget = node; }
	CREATE_FUNC(ArtifactButton);

private:
	Node* m_node;
	int m_lhs;
	MyNum m_baseDps;
	MyNum m_dps;
	Layer* m_layer;
	static Node* g_lv;
	static Node * g_node;
	static Node * g_button;
	static Node * g_widget;
	int m_id;
	int m_level;
	int m_StoneNum;//已消费的灵魂石
	bool m_levelUp;
	bool onTouchBegan(Touch *, Event*);
	void onTouchEnded(Touch *, Event *);

};


#endif
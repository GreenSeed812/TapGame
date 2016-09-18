#ifndef _ArtifactButton_H_
#define _ArtifactButton_H_

#include <cocos2d.h>
#include "Tool/MyNum.h"
using namespace cocos2d;

class ArtifactButton : public Layer
{
public:
	bool init();
	void initArtifactLayer(int id,bool check);
	void arChange(Ref*);
	static void setListView(Node* lv){ g_lv = lv; }
	static void setRootNode(Node*node){ g_node = node;};
	void setWidget(Node * node){ m_widget = node; }
	CREATE_FUNC(ArtifactButton);

private:
	Node* m_node;
	int m_lhs;
	MyNum m_baseDps;
	MyNum m_dps;
	Layer* m_layer;
	static Node* g_lv;
	static Node * g_node;
	Node * m_widget;
	int m_id;
	int m_level;
	int m_StoneNum;//�����ѵ����ʯ
	bool m_levelUp;

};


#endif
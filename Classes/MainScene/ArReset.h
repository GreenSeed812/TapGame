
#ifndef _ARRESET_H_
#define _ARRESET_H_

#include <cocos2d.h>
#include "Tool/MyNum.h"
#include "ArtifactButton.h"
using namespace cocos2d;

class ArReset : public Layer
{
public:
	bool init();
	void initArResetLayer(int id);
	void setStoneNum(int num){ m_StoneNum = num; };
	static void getListView(Node* lv){ g_lv = lv; }
	void setNode(Node * node, int tag){ m_arBtn = node; g_tag = tag; }
	void arResetChange(Ref*);
	CREATE_FUNC(ArReset);
private:
	Node * m_node;
	Node * m_arBtn;
	static int g_tag;
	static Node* g_lv;
	Layer* m_layer;
	int m_StoneNum;
	int m_id;
};

#endif
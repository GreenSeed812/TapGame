
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
	void setWidget(Node * node){ m_widget = node; }
	void setListView(Node * node)
	{ 
		g_listview = node;
	}
	void setBtn(Node * node){ g_btn = node; }
	void arResetChange(Ref*);
	CREATE_FUNC(ArReset);
private:
	Node * m_node;
	Node * m_widget;
	static Node * g_listview;
	Node * g_btn;
	Layer* m_layer;
	int m_StoneNum;
	int m_id;
};

#endif
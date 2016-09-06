#ifndef _ServantButton_H_
#define _ServantButton_H_
#include <cocos2d.h>
#include "Tool/MyNum.h"
#include <vector>
using namespace cocos2d;
using namespace std;
class ServantButton :public Layer 
{
public:
	bool init();
	void initServantLayer(int);
	CREATE_FUNC(ServantButton);
	static void getListView(Node* lv){ g_lv = lv; }
	static void getRootNode(Node * node){ g_node = node; }
	void coinChange(Ref*);
private:
	Node* node;
	Layer* m_layer;
	int m_id;
	int m_skillcount;
	bool m_clickState;
	bool m_state;
	static Node* g_lv;
	static Node * g_node;
	bool onTouchBegan(Touch * touch, Event* event);
	void onTouchEnded(Touch * touch, Event * event);
	void oneUp();
	void upLevel();
	void lockState();
	void unLockSkill();
	void callbackSer(Node * node);
};


#endif

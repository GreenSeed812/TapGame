#ifndef _ServantButton_H_
#define _ServantButton_H_
#include <cocos2d.h>
#include "Tool/MyNum.h"
using namespace cocos2d;
class ServantButton :public Layer 
{
public:
	bool init();
	void initServantLayer(int);
	CREATE_FUNC(ServantButton);
	static void getListView(Node* lv){ g_lv = lv; }
	void coinChange(Ref*);
private:
	Node* node;
	MyNum m_gold;
	MyNum m_baseDps;
	MyNum m_dps;
	static Node* g_lv;
	std::vector<float> m_dpsMul;
	int m_id;
	Layer* m_layer;
	bool m_unlock;
	bool m_lock;
	bool m_locked;
	int m_lockCount;
	int m_skillCount;
};


#endif // !_ServantButton_H_

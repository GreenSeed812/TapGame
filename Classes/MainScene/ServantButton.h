#ifndef _ServantButton_H_
#define _ServantButton_H_
#include <cocos2d.h>
#include "Tool/MyNum.h"
#include <vector>
#include "SaveData/ServantSkill.h"
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
	MyNum m_gold;
	MyNum m_upGold10;
	MyNum m_upGold100;
	MyNum m_baseDps;
	MyNum m_dps;
	int m_skillcount;
	static Node* g_lv;
	static Node * g_node;
	vector <ServantSkill *> m_skills;
	std::vector<float> m_dpsMul;
	int m_id;
	Layer* m_layer;
	bool onTouchBegan(Touch * touch, Event* event);
	void onTouchEnded(Touch * touch, Event * event);
	void upLevel(bool off_on);
	void oneUp();
	void unLockSkill();
	void callbackSer(Node * node);
};


#endif

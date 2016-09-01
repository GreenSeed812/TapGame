#ifndef _PlayerButton_H_
#define _PlayerButton_H_
#include <cocos2d.h>
#include "Tool/MyNum.h"
using namespace cocos2d;
enum BUTTONTYPE
{
	PLAYER,
	SKILL1,
	SKILL2,
	SKILL3,
	SKILL4,
	SKILL5,
	SKILL6,
	RELIFE
};
class PlayerButton :public Layer
{
public:
	bool init();
	CREATE_FUNC(PlayerButton);
	void initPlayerButton(BUTTONTYPE);
	void coinChange(Ref*);
	static void getSkillLayer(Node * layer){ g_skillLayer = layer; }
	static void getRootNode(Node * node){ g_node = node; }
private:
	Node * playerLayer;
	BUTTONTYPE m_type;
	MyNum m_upGold;
	MyNum m_upGold10;
	MyNum m_upGold100;
	static Node * g_skillLayer;
	static Node * g_node;
	void upLevelCount();
	bool onTouchBegan(Touch * touch, Event* event);
	void onTouchEnded(Touch * touch, Event * event);
	void callback(Node * node);
};


#endif // !_PlayerButton_H_
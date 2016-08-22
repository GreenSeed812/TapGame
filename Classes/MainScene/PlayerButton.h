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
private:
	Node * playerLayer;
	BUTTONTYPE m_type;
	MyNum m_upGold;
};


#endif // !_PlayerButton_H_
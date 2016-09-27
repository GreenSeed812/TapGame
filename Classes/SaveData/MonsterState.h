#include "Tool/SqLite.h"
#ifndef _MonsterState_H_
#define _MonsterState_H_
enum MONSTER_TYPE
{
	BOSS,
	RARE,
	NORMAL
};
class MonsterState
{
public:
	static MonsterState * getInstance();
	void setMonsterState(MONSTER_TYPE type){ m_type = type; }
	MONSTER_TYPE getTypeNow(){ return m_type; }
	void saveBoss(MonsterData* monster);
	MonsterData * getBoss(){ return &m_boss; }
	bool getSaveBoss(){return m_saveMonster; }
	void setSaveBoss(bool boolean){ m_saveMonster = boolean; }
private:
	MonsterState();
	~MonsterState();
	MONSTER_TYPE m_type;
	MonsterData m_boss;
	bool m_saveMonster;
};


#endif
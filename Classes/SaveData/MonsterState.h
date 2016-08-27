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
private:
	MonsterState();
	~MonsterState();
	MONSTER_TYPE m_type;

};


#endif
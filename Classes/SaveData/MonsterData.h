#ifndef _MonsterData_H_
#define _MonsterData_H_
enum MONSTER_TYPE
{
	BOSS,
	RARE,
	NORMAL
};
class MonsterData
{
public:
	static MonsterData * getInstance();
	void setMonsterData(MONSTER_TYPE type){ m_type = type; }
	MONSTER_TYPE getTypeNow(){ return m_type; }
private:
	MonsterData();
	~MonsterData();
	MONSTER_TYPE m_type;

};


#endif
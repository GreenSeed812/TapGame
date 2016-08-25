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
	
private:
	MonsterData();
	~MonsterData();
	MONSTER_TYPE m_type;

};


#endif
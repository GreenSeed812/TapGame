#ifndef _PlayerData_H_
#define _PlayerData_H_
#include "Tool\Rule.h"
class PlayerData
{
public:
	
	static PlayerData * getInstance();
	int getLevel(){ return m_level; }
	int getMonsterNum(){ return m_monsterNum; }
	MyNum getDps(){ return m_basedps; }
	MyNum getHpNow(){ return m_hpNow; }
	void setLevel(int level){ m_level = level; }
	void subHp(){ m_hpNow = *Ruler::getInstance()->subNum(&m_hpNow,&m_basedps); }
	void setHpNow(MyNum hp){ m_hpNow = hp; }
private:
	int m_level;
	int m_monsterNum;
	int m_playerLevel;
	MyNum m_basedps;
	MyNum m_hpNow;
	PlayerData();
	~PlayerData();
};
#endif

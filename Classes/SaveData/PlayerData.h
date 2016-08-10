#ifndef _PlayerData_H_
#define _PlayerData_H_
#include "Tool\Rule.h"
#include <vector>
struct LatestData
{
	std::vector<MyNum> m_HpData;
	MyNum m_dropData;
	int randNpc[5];
};
class PlayerData
{
public:
	
	static PlayerData * getInstance();
	int getLevel(){ return m_level; }
	int getMonsterNum(){ return m_monsterNum; }
	MyNum getDps(){ return m_basedps; }
	MyNum getHpNow(){ return m_hpNow; }
	MyNum getMaxHp();
	void setLevel(int level){ m_level = level; }
	void subHp(){ m_hpNow = *Ruler::getInstance()->subNum(&m_hpNow,&m_basedps); }
	void setHpNow(MyNum hp){ m_hpNow = hp; }
	int getRandNpc(int r);
	MyNum *getHpByID(int id);
	void levelUp();
	void heroLevelUp();
	MyNum getHeroDps(){ return m_heroDpsAll; }
	int getPlayerLevel(){ return m_playerLevel; }
	void addGold(MyNum* gold){ m_gold = *Ruler::getInstance()->addNum(&m_gold, gold); }
	void subGold(MyNum* gold){ m_gold = *Ruler::getInstance()->subNum(&m_gold, gold); }
	int getWaveNow(){ return m_waveNow; }
	void waveUp(){ m_waveNow++; }
	void resetWave(){ m_waveNow = 1; }
private:
	int m_waveNow;
	int m_level;
	int m_monsterNum;
	int m_playerLevel;
	MyNum m_basedps;
	MyNum m_hpNow;
	MyNum m_gold;
	LatestData m_latest;
	PlayerData();
	~PlayerData();
	MyNum m_heroDpsAll;
};
#endif

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
	void addGold(MyNum* gold);
	void addServantNum(){ m_servantNum++; }
	void defeatMonsterGold();
	static PlayerData * getInstance();
	int getLevel(){ return m_level; }
	int getMonsterNum(){ return m_monsterNum; }
	MyNum getDps();
	float getDpsMul(){ return m_dpsMul; }
	MyNum getHeroDps();
	MyNum* getGold(){ return &m_gold; }
	MyNum getHpByID(int id);
	MyNum getHpNow(){ return m_hpNow; }
	MyNum getMaxHp();
	int getSkillLevel(int i){ return m_skillLevel[i];}	
	int getWaveNow(){ return m_waveNow; }
	int getPlayerLevel(){ return m_playerLevel; }
	int getRandNpc(int r);
	int getServantLevel(int i){ return m_servantLevel[i]; }
	int getServantNum(){ return m_servantNum; }
	void heroLevelUp();
	void levelUp();
	void resetWave(){ m_waveNow = 1; }
	void servantLevelUp(int i){ m_servantLevel[i]++;}
	void setHpNow(MyNum hp){ m_hpNow = hp; }
	void setLevel(int level){ m_level = level; }
	void setServantBaseDps(MyNum dps, int id){ m_servantBaseDps[id] = dps; }
	void setWave(int wave){ m_waveNow = wave; }
	void skillLevelUp(int i){ m_skillLevel[i-1]++; }
	void subGold(MyNum* gold);
	void subHp(){ m_hpNow = Ruler::getInstance()->subNum(&m_hpNow,&m_basedps); }
	void waveUp(){ m_waveNow++; }	
private:
	int m_waveNow;
	int m_level;
	int m_monsterNum;
	int m_playerLevel;
	float m_dpsMulBase;
	float m_dpsMul;
	float m_goldMulBase;
	float m_goldMulAdd;
	MyNum m_basedps;
	MyNum m_hpNow;
	MyNum m_gold;
	LatestData m_latest;
	PlayerData();
	~PlayerData();
	MyNum m_heroDpsAll;
	float m_bossTime;
	int m_skillLevel[6];
	int m_servantNum;
	int m_servantLevel[33];
	MyNum m_servantBaseDps[33];
	float m_servantMul[33];
	float m_servantAllMul;
};
#endif

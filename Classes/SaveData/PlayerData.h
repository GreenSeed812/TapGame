#ifndef _PlayerData_H_
#define _PlayerData_H_
#include "Tool/Rule.h"
#include "Tool/SqLite.h"
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
	void addexplorPer(int per){ m_explorePer += per; }
	void addexploreProb(int prob){ m_exploreProb += prob; }
	void addArNum();
	void addGold(MyNum* gold);
	void addServantNum(){ m_servantNum++; }
	int getArtiStone(){ return 1000; }
	void defeatMonsterGold();
	static PlayerData * getInstance();
	float getBanTime(int i){ return m_skillData.at(i-1)->baseBanTime; }
	MyNum getdefeatMonsterGold();
	float getKeepTime(int i){ return m_skillData.at(i-1)->baseTime; }
	int getLevel(){ return m_level; }
	int getMonsterNum(){ return m_monsterNum; }
	MyNum getDps();
	float getDpsMul(){ return m_dpsMul; }
	MyNum getHeroDps();
	MyNum* getGold(){ return &m_gold; }
	MyNum getHpByID(int id);
	MyNum getHpNow(){ return m_hpNow; }
	MyNum getMaxHp();
	int getServantAverLevel(); 
	float getSkillEFF(int i);
	int getSkillLevel(int i){ return m_skillLevel[i];}
	MyNum getTapDpsNoExp();
	int getWaveNow(){ return m_waveNow; }
	int getPlayerLevel(){ return m_playerLevel; }
	int getRandNpc(int r);
	int getRelifeStone();
	int getHeroRelifeStone();
	int getServantRelifeStone();
	int getLevelRelifeStone();
	MyNum getServantDps(int i);
	int getServantLevel(int i){ return m_servantLevel[i]; }
	MyNum getservantLevelUpGold(int id);
	int getServantNum(){ return m_servantNum; }
	bool getSkillopen(int i){ return m_skillOpen[i]; }
	MyNum getTapDps();
	int getMaxTime(){ return m_maxTime; }
	int getMaxWave(){ return m_maxWave; }
	void heroLevelUp();
	void levelUp();
	void randRareMonster();
	void relife();
	void resetMaxWave();
	void resetTime();
	void resetWave(){ m_waveNow = 1; }
	void servantLevelUp(int i);
	void setHpNow(MyNum hp){ m_hpNow = hp; }
	void setLevel(int level){ m_level = level; }
	void setServantBaseDps(MyNum dps, int id);
	void setSkillexploreProb(int prob){ m_skillexploreProb = prob; }
	void setSkillTap(float t){ m_skillTap = t; }
	void setWave(int wave){ m_waveNow = wave; }
	void skillLevelUp(int i){ m_skillLevel[i-1]++; }
	void subexplorPer(int per){ m_explorePer -= per; }
	void subexploreProb(int prob){ m_exploreProb -= prob; }
	void subGold(MyNum* gold);
	void subHp(MyNum dps){ m_hpNow = Ruler::getInstance()->subNum(m_hpNow,dps); }
	void waveUp(){ 	m_waveNow++;}
	void closeSkill(int i){ m_skillOpen[i] = false; }
	void openSkill(int i){ m_skillOpen[i] = true; }
	void subHp(){ m_hpNow = Ruler::getInstance()->subNum(m_hpNow,m_basedps); }
	void unlockSernantSkill(int servantid, int skillid);
	void saveUserData(float dt);
	bool init();
private:
	int m_waveNow;
	int m_level;
	int m_monsterNum;
	int m_playerLevel;
	int m_maxTime;
	int m_maxWave;
	float m_dpsMulBase;
	float m_dpsMul;
	float m_explorePer;
	int m_exploreProb;
	float m_goldMulBase;
	float m_goldMulBox;
	float m_goldMulServantAdd;
	MyNum m_basedps;
	MyNum m_hpNow;
	MyNum m_gold;
	LatestData m_latest;
	PlayerData();
	~PlayerData();
	MyNum m_heroDpsAll;
	float m_bossTime;
	int m_rareProb;
	int m_skillLevel[6];
	int m_servantNum;
	int m_servantLevel[33];
	MyNum m_servantBaseDps[33];
	float m_servantMul[33];
	float m_servantAllMul;
	float m_servantTapDps;
	bool m_skillOpen[6];
	float m_skillTap;
	std::vector<SkillData*> m_skillData;
	int m_skillexploreProb;
	float m_bossDpsMul;
	float m_TapDpsMul;
	float m_latestTapMul;
	int m_diamond;
	int m_artifactStar[29];
};
#endif

#ifndef _AchieveData_H_
#define _AchieveData_H_
#include "Tool/MyNum.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
using namespace  rapidjson;
class AchieveData
{
public:
	static AchieveData* getInstance();
	void saveUserDefault(Document& document);
	void readUserDefault();
public:
	void killMonster(){ m_monsterKill++; }
	void addCoin(MyNum add);
	void maxLevel(int level){ if(level > m_maxLevel) m_maxLevel = level; }
	void addArStone(int add){ m_ArStoneCollect += add; }
	void ArMaxNum(int num){ if (num > m_ArMax) m_ArMax = num; }
	void killBoss(){ m_bossKill++; }
	void tap();
	void relife(){ m_relifeNum++; }
	void maxPlayerLevel(int plevel){ if (plevel > m_maxPlayerLevelUp)m_maxPlayerLevelUp = plevel; }
	void killRareMonster(){ m_killraremonster++; }
	void addexploreNum(){ exploreNum++; }
	void skillUsed(int i);
	int getStarNumByID(int id){ return starNum[id-1]; }
	void setStarNumByID(int id, int num){ starNum[id-1] = num; }
	int getTotalReword(){ return m_totalrewords; }
	void addTotalReword(int add){ m_totalrewords += add; }
public:
	int getTapNum(){ return m_tapNum; }
	int getMonsterKill(){ return m_monsterKill; }
	int getRareKill(){ return m_killraremonster; }
	int getBossKill(){ return m_bossKill; }
	int getMaxxLevel(){ return m_maxLevel; }
	int getRelifeNum(){ return m_relifeNum; }
	MyNum getCoinCollect(){ return m_coinCollect; }
public:
	MyNum getMyNumByID(int id);
	int getNumByID(int id);
private:
	AchieveData();
	~AchieveData();
	int m_monsterKill;
	MyNum m_coinCollect;
	int m_maxLevel;
	int m_ArStoneCollect;
	int m_ArMax;
	MyNum m_maxDpsPer;
	int m_bossKill;
	int m_tapNum;
	int m_relifeNum;
	int m_maxPlayerLevelUp;
	int m_killraremonster;
	int m_skill1used;
	int m_skill2used;
	int m_skill3used;
	int m_skill4used;
	int m_skill5used;
	int m_skill6used;
	int exploreNum;
	int starNum[23];
	int m_totalrewords;
};


#endif
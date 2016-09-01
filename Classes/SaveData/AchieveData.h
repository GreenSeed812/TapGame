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
	void killMonster(){ m_monsterKill++; }
	void addCoin(MyNum add);
	void maxLevel(int level){ if(level > m_maxLevel) m_maxLevel = level; }
	void addArStone(){ m_ArStoneCollect++; }
	void ArMaxNum(int num){ if (num > m_ArMax) m_ArMax = num; }
	void killBoss(){ m_bossKill++; }
	void tap(){ m_tapNum++; }
	void relife(){ m_relifeNum++; }
	void maxPlayerLevel(int plevel){ if (plevel > m_maxPlayerLevelUp)m_maxPlayerLevelUp = plevel; }
	void killRareMonster(){ m_killraremonster++; }
	void skillUsed1(){ m_skill1used++; }
	void skillUsed2(){ m_skill2used++; }
	void skillUsed3(){ m_skill3used++; }
	void skillUsed4(){ m_skill4used++; }
	void skillUsed5(){ m_skill5used++; }
	void skillUsed6(){ m_skill6used++; }
	void addexploreNum(){ exploreNum++; }
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
};


#endif
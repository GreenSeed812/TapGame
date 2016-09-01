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
	void tap(){ m_tapNum++; }
	void relife(){ m_relifeNum++; }
	void maxPlayerLevel(int plevel){ if (plevel > m_maxPlayerLevelUp)m_maxPlayerLevelUp = plevel; }
	void killRareMonster(){ m_killraremonster++; }
	void addexploreNum(){ exploreNum++; }
	void skillUsed(int i);
public:
	int get1(){ return m_monsterKill; }
	MyNum get2(){ return m_coinCollect; }
	int get3(){ return m_maxLevel; }
	int get4(){ return m_ArStoneCollect; }
	int get5(){ return m_ArMax; }
	MyNum get6(){ return m_maxDpsPer; }
	int get7(){ return m_bossKill; }
	int get8(){ return m_tapNum; }
	int get9(){ return m_relifeNum; }
	int get10(){ return m_maxPlayerLevelUp; }
	int get11(){ return m_killraremonster; }
	int get12(){ return m_skill1used; }
	int get13(){ return m_skill2used; }
	int get14(){ return m_skill3used; }
	int get15(){ return m_skill4used; }
	int get16(){ return m_skill5used; }
	int get17(){ return m_skill6used; }
	int get18(){ return exploreNum; }
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
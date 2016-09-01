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
	void levelUp(){ m_maxLevel++; }

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
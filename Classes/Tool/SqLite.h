#ifndef _SqLite_H_
#define _SqLite_H_
#include <string>
#include <vector>
#include <map>
#include "Tool/sqlite3.h"
#include "MyNum.h"
struct MonsterData
{
	int ID;
	std::string png;
	std::string plist;
	std::string exportJson;
	std::string name;
	std::string showName;

};
struct HeroData
{
	int hp;
	int basedps;
	int level;
};
struct servantSkill
{
	std::string skillname;
	float effect;
	int skillID;
};
struct Servant
{
	int ID;
	std::string name;	
	servantSkill skill[7];
	std::string discribe;
	MyNum dps;
	MyNum gold;
	std::string	picture;

	
};
struct MapData
{
	int ID;
	float bossHp;
	std::string name;
	std::string bgMusic;
	std::string mapIcon;
	std::string bg;
	

	
};
struct SkillData
{
	int id; 
	std::string effect;
	float baseTime;
	float baseBanTime;
	float initEffect;
	float effPerLevel;
	MyNum unlockGold;

};
struct SkillEffect
{
	int id;
	std::string effect;
};

class SqLite
{
public:
	
	static SqLite* getInstance();
	MyNum getHpByID(int);
	MonsterData* getMonsterByID(int);
	MyNum getDropData(){ return m_dropData; }
	int m_randNpc[5];
	std::vector<MyNum> getHpData(){ return m_HpData; }
	float getBossHp(int i){ return m_bossHp[i]; }
	MyNum getDps(int i){ return m_baseDps[i]; }
	MyNum getGold(){ return m_gold; }
	MyNum getGoldByID(int);
	std::string getSkillDis(int i);
	double getEff(int i){ return m_skillData.at(i)->initEffect; }
	double getEffPer(int i){ return m_skillData.at(i)->effPerLevel; }
	MyNum getServantDpsByID(int i){ return m_servantData.at(i)->dps; }
	MyNum getServantGoldByID(int i){ return m_servantData.at(i)->gold; }
	std::string getServantNameByID(int i){ return m_servantData.at(i)->name; }
public:
	SqLite();
	~SqLite();
	void readMonster();
	void readMapData();
	void readSimpleData();
	void readSkillData();
	void readServant();
	void readServantSkill();
	sqlite3 *m_pDB; 
	std::vector<MonsterData*> m_monsterData;
	std::vector<Servant*> m_servantData;
	std::vector<MapData> m_mapData;
	std::vector<MyNum> m_HpData;
	std::map<MyNum,int> m_monsterDataMap;
	std::vector<SkillData*>m_skillData;
	std::vector<SkillEffect*>m_skillEffect;
	float m_bossHp[5];
	MyNum m_dropData;
	MyNum m_baseDps[8];
	MyNum m_gold;
	std::vector<int> m_servantUnlock;
};



#endif
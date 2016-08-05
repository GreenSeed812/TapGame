#ifndef _SqLite_H_
#define _SqLite_H_
#include <string>
#include <vector>
#include "Tool\sqlite3.h"
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

struct Servant
{
	int ID;
	int basedps;
	int level;
	
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

class SqLite
{
public:
	
	static SqLite* getInstance();
	MyNum * getHpByID(int);
	MonsterData* getMonsterByID(int);
	MyNum getDropData(){ return m_dropData; }
	int m_randNpc[5];
	std::vector<MyNum> getHpData(){ return m_HpData; }
	float getBossHp(int i){ return m_bossHp[i]; }
	MyNum getDps(int i){ return m_baseDps[i]; }
private:
	SqLite();
	~SqLite();
	void readMonster();
	void readMapData();
	void readSimpleData();
	sqlite3 *m_pDB;
	std::vector<MonsterData*> m_monsterData;
	std::vector<Servant> m_servantData;
	std::vector<MapData> m_mapData;
	std::vector<MyNum> m_HpData;
	float m_bossHp[5];
	MyNum m_dropData;
	MyNum m_baseDps[8];
	
};



#endif
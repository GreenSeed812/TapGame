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
	MyNum hp;
	MyNum drop;
	float bossHp;
	std::string name;
	std::string bgMusic;
	std::string mapIcon;
	std::string bg;
	
	int npc[5];
	
};
class SqLite
{
public:
	
	static SqLite* getInstance();
	MapData * getMapByID(int);
	MonsterData* getMonsterByID(int);
private:
	SqLite();
	~SqLite();
	void readMonster();
	void readMapData();
	sqlite3 *m_pDB;
	std::vector<MonsterData> m_monsterData;
	std::vector<Servant> m_servantData;
	std::vector<MapData> m_mapData;
};



#endif
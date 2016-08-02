#ifndef _SqLite_H_
#define _SqLite_H_
#include <string>
#include <vector>
#include "Tool\sqlite3.h"
struct MonsterData
{
	int ID;
	std::string png;
	std::string plist;
	std::string exportJson;
	std::string name;


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
	int hp;
	std::string name;
	std::string bgMusic;
	std::string mapIcon;
	std::string bg;
	std::string drop;
	std::string m1;
	std::string m2;
	std::string m3;
	std::string m4;
	std::string m5;
};
class SqLite
{
public:
	
	static SqLite* getInstance();
	void readMonster();
	void readMapData();
private:
	SqLite();
	~SqLite();
	sqlite3 *m_pDB;
	std::vector<MonsterData> m_monsterData;
	std::vector<Servant> m_servantData;
	std::vector<MapData> m_mapData;
};



#endif
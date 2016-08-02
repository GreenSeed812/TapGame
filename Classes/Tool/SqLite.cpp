#include "Tool/SqLite.h"
#include "Tool/sqlite3.h"

SqLite * g_sql = nullptr;
SqLite::SqLite()
{
	sqlite3_open("config.db",&m_pDB);
	readMonster();
}

SqLite::~SqLite()
{
}

SqLite* SqLite::getInstance()
{
	if (!g_sql)
	{
		g_sql = new SqLite();
	}
	return g_sql;
}


void SqLite::readMonster()
{
	char** dbResult;
	int nRow;
	int nColum;
	char* errmsg;
	auto tableresult = sqlite3_get_table(m_pDB, "select * from Monster", &dbResult, &nRow, &nColum, &errmsg);
	if (SQLITE_OK == tableresult)
	{
		std::string id = "ID";
		std::string name = "name";
		std::string plist = "plist";
		std::string exportJson = "exportJson";
		std::string png = "png";
		std::string showName = "showName";
		auto index = nColum;
		for (int i = 0; i < nRow; i++)
		{
			MonsterData monster = MonsterData();
			for (int j = 0; j < nColum; j++)
			{
				
				("hero %s %s", dbResult[j], dbResult[index]);
				
				if (id.compare(dbResult[j]) == 0)
					monster.ID = atoi(dbResult[index]);
				if (name.compare(dbResult[j]) == 0)
					monster.name = dbResult[index];
				if (plist.compare(dbResult[j]) == 0)
					monster.plist = dbResult[index];
				if (exportJson.compare(dbResult[j]) == 0)
					monster.exportJson = dbResult[index]; 
				if (png.compare(dbResult[j]) == 0)
					monster.png = dbResult[index];
				if (png.compare(dbResult[j]) == 0)
					monster.png = dbResult[index];
				
				++index;
			}
			m_monsterData.push_back(monster);
		}
	}
}
void SqLite::readMapData()
{
	char** dbResult;
	int nRow;
	int nColum;
	char* errmsg;
	auto tableresult = sqlite3_get_table(m_pDB, "select * from Map", &dbResult, &nRow, &nColum, &errmsg);
	if (SQLITE_OK == tableresult)
	{
		std::string id = "ID";
		std::string name = "name";
		std::string music = "bgMusic";
		std::string mapIcon = "mapIcon";
		std::string bg = "bg";
		std::string hp = "hp";
		std::string drop = "drop";
		std::string m1 = "m1";
		std::string m2 = "m2";
		std::string m3 = "m3";
		std::string m4 = "m4";
		std::string m5 = "m5";
		auto index = nColum;
		for (int i = 0; i < nRow; i++)
		{
			auto map = MapData();
			for (int j = 0; j < nColum; j++)
			{
				if (id.compare(dbResult[j]) == 0)
					map.ID = atoi(dbResult[index]);
				if (name.compare(dbResult[j]) == 0)
					map.name = dbResult[index];
				if (music.compare(dbResult[j]) == 0)
					map.bgMusic = dbResult[index];
				if (mapIcon.compare(dbResult[j]) == 0)
					map.mapIcon = dbResult[index];
				if (bg.compare(dbResult[j]) == 0)
					map.bg = dbResult[index];
				if (hp.compare(dbResult[j]) == 0)
					map.hp = atoi(dbResult[index]);
				if (drop.compare(dbResult[j]) == 0)
					map.drop = dbResult[index];
				if (m1.compare(dbResult[j]) == 0)
					map.m1 = dbResult[index];
				if (m2.compare(dbResult[j]) == 0)
					map.m2 = dbResult[index];
				if (m3.compare(dbResult[j]) == 0)
					map.m3 = dbResult[index];
				if (m4.compare(dbResult[j]) == 0)
					map.m4 = dbResult[index];
				if (m5.compare(dbResult[j]) == 0)
					map.m5 = dbResult[index];

				++index;
			}
			m_mapData.push_back(map);
		auto index = nColum;
	}
}
#include "Tool/SqLite.h"
#include "Split.h"
#include<cocos2d.h>
using namespace cocos2d;

SqLite * g_sql = nullptr;
SqLite::SqLite()
{
	sqlite3_open("config/config.db",&m_pDB);
	readMonster();
	readMapData();
	readSimpleData();
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
			MonsterData *monster = new MonsterData();
			monster->png = "monster/";
			monster->plist = "monster/";
			monster->exportJson = "monster/";
			for (int j = 0; j < nColum; j++)
			{
				
				if (id.compare(dbResult[j]) == 0)
					monster->ID = atoi(dbResult[index]);
				if (name.compare(dbResult[j]) == 0)
					monster->name = dbResult[index];
				if (plist.compare(dbResult[j]) == 0)
					monster->plist += dbResult[index];
				if (exportJson.compare(dbResult[j]) == 0)
					monster->exportJson += dbResult[index]; 
				if (png.compare(dbResult[j]) == 0)
					monster->png += dbResult[index];
				if (showName.compare(dbResult[j]) == 0)
					monster->showName = dbResult[index];
				
				++index;
			}

			m_monsterData.push_back(monster);
		}
	}
}
void SqLite::readSimpleData()
{
	char** dbResult;
	int nRow;
	int nColum;
	char* errmsg;
	auto tableresult = sqlite3_get_table(m_pDB, "select * from simpleConfig", &dbResult, &nRow, &nColum, &errmsg);
	if (SQLITE_OK == tableresult)
	{
		auto index = nColum;
		std::string tmp;

		for (int i = 0; i < nRow; i++)
		{
			std::string key = "key";
			std::string value = "value";
			std::string bossMulti = "bossMulti";
			std::string npc = "npc";
			std::string hp = "hp";
			std::string gold = "gold";
			std::string baseDps = "baseDps";
			for (int j = 0; j < nColum; j++)
			{
				if (key.compare(dbResult[j]) == 0)
				{
					if (bossMulti.compare(dbResult[index]) == 0)
					{
						list<string> list;
						tmp = dbResult[index + 1];
						list = Split::getInstance()->strsplit(tmp, ",");
						for (int i = 0; list.size()>0; i++)
						{
						
							m_bossHp[i] = atof(list.front().c_str());
							list.pop_front();
						}
					}
					if (npc.compare(dbResult[index]) == 0)
					{
						list<string> list;
						tmp = dbResult[index + 1];
						list = Split::getInstance()->strsplit(tmp, ",");
						for (int i = 0; list.size()>0; i++)
						{

							m_randNpc[i] = atoi(list.front().c_str());
							list.pop_front();
						}

					}
					if (hp.compare(dbResult[index]) == 0)
					{
						list<string> list;
						tmp = dbResult[index + 1];
						list = Split::getInstance()->strsplit(tmp, ",");
						MyNum tmpHp;
						for (int i = 0; list.size()>0; i++)
						{
							
							if (i % 2 == 0)
								tmpHp.number = atof(list.front().c_str());
							else
							{
								tmpHp.Mathbit = atoi(list.front().c_str());
								m_HpData.push_back(tmpHp);
							}
							list.pop_front();
						}

					}
					if (gold.compare(dbResult[index]) == 0)
					{
						list<string> list;
						tmp = dbResult[index + 1];
						list = Split::getInstance()->strsplit(tmp, ",");
						MyNum tmpGD;
						for (int i = 0; list.size()>0; i++)
						{

							if (i % 2 == 0)
								m_dropData.number = atof(list.front().c_str());
							else
							{
								m_dropData.Mathbit = atoi(list.front().c_str());
							}
							list.pop_front();
						}

					}
					if (baseDps.compare(dbResult[index]) == 0)
					{
						list<string> list;
						tmp = dbResult[index + 1];
						list = Split::getInstance()->strsplit(tmp, ",");
						MyNum tmpGD;
						for (int i = 0; list.size()>0; i++)
						{

							m_baseDps[i].number = atof(list.front().c_str());
							list.pop_front();
						}

					}
					
				}
				++index;
			}

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
				++index;
			}
			m_mapData.push_back(map);
		}
	}
}
MyNum * SqLite::getHpByID(int id)
{
	return &m_HpData.at(id);
	
}

MonsterData* SqLite::getMonsterByID(int id)
{
	return m_monsterData.at(id - 1);
}
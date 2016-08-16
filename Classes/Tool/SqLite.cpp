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
	readSkillData();
	readServant();
	readServantSkill();
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
			std::string servantUnlock = "servantUnlock";
			std::string monsterGold = "monsterGold";
			std::string heroUpGold = "heroUpGold";
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
					if (servantUnlock.compare(dbResult[index]) == 0)
					{
						list<string> list;
						tmp = dbResult[index + 1];
						list = Split::getInstance()->strsplit(tmp, ",");
						for (int i = 0; list.size()>0; i++)
						{
							m_servantUnlock.push_back(atoi(list.front().c_str()));
							list.pop_front();
						}

					}
					if (heroUpGold.compare(dbResult[index]) == 0)
					{
						list<string> list;
						tmp = dbResult[index + 1];
						list = Split::getInstance()->strsplit(tmp, ",");
						m_gold.number = atof(list.front().c_str());
						list.pop_front();
						m_gold.Mathbit = atoi(list.front().c_str());
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
void SqLite::readSkillData()
{
	char** dbResult;
	int nRow;
	int nColum;
	char* errmsg;
	auto tableresult = sqlite3_get_table(m_pDB, "select * from SKILL", &dbResult, &nRow, &nColum, &errmsg);
	if (SQLITE_OK == tableresult)
	{
		std::string id = "ID";
		std::string effect = "effect"; 
		std::string baseTime = "baseTime";
		std::string baseBanTime = "baseBanTime";
		std::string initEffect = "initEffect";
		std::string effPerLevel = "effPerLevel";
		std::string unlockGold = "unlockGold";
		auto index = nColum;
		for (int i = 0; i < nRow; i++)
		{
			auto skill = new SkillData();
			for (int j = 0; j < nColum; j++)
			{
				if (id.compare(dbResult[j]) == 0)
					skill->id = atoi(dbResult[index]);
				if (effect.compare(dbResult[j]) == 0)
					skill->effect = dbResult[index];
				if (baseTime.compare(dbResult[j]) == 0)
					skill->baseTime = atof(dbResult[index]);
				if (baseBanTime.compare(dbResult[j]) == 0)
					skill->baseBanTime = atof(dbResult[index]);
				if (initEffect.compare(dbResult[j]) == 0)
					skill->initEffect = atof(dbResult[index]);
				if (effPerLevel.compare(dbResult[j]) == 0)
					skill->effPerLevel = atof(dbResult[index]);
				if (unlockGold.compare(dbResult[j]) == 0)
				{
					list<string> list;
					std::string tmp = dbResult[index];
					list = Split::getInstance()->strsplit(tmp, ",");
					skill->unlockGold.number = atof(list.front().c_str());
					list.pop_front();
					skill->unlockGold.Mathbit = atof(list.front().c_str());
				}
				++index;
			}
 			m_skillData.push_back(skill);
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


MyNum SqLite::getGoldByID(int i)
{
	return m_skillData.at(i - 1)->unlockGold;
}
std::string SqLite::getSkillDis(int i)
{
	return m_skillData.at(i)->effect;
}

void SqLite::readServant()
{
	char** dbResult;
	int nRow;
	int nColum;
	char* errmsg;
	auto tableresult = sqlite3_get_table(m_pDB, "select * from Servant", &dbResult, &nRow, &nColum, &errmsg);
	if (SQLITE_OK == tableresult)
	{
		std::string id = "ID";
		std::string name = "name";
		std::string skillID[7];
		std::string skillname[7];
		std::string effect[7];
		for (int i = 0; i < 7; i++)
		{
			skillID[i] = StringUtils::format("skill%d", i + 1);
			skillname[i] = StringUtils::format("skillname%d", i + 1);
			effect[i] = StringUtils::format("effect%d", i + 1);
		}
		std::string discribe = "discribe";
		std::string dps = "dps";
		std::string gold = "gold";
		std::string	picture = "picture";
		auto index = nColum;
		for (int i = 0; i < nRow; i++)
		{
			auto servant = new Servant();
			
			for (int j = 0; j < nColum; j++)
			{
				if (id.compare(dbResult[j]) == 0)
					servant->ID = atoi(dbResult[index]);
				if (discribe.compare(dbResult[j]) == 0)
					servant->discribe = dbResult[index];
				if (name.compare(dbResult[j]) == 0)
					servant->name = dbResult[index];
				for (int i = 0; i < 7; i++)
				{
					if (skillID[i].compare(dbResult[j]) == 0)
						servant->skill[i].skillID = atoi(dbResult[index]);
					else if (skillname[i].compare(dbResult[j]) == 0)
						servant->skill[i].skillname = dbResult[index];
					else if (effect[i].compare(dbResult[j]) == 0)
						servant->skill[i].effect = atof(dbResult[index]);
				}
				if (picture.compare(dbResult[j]) == 0)
					servant->picture = dbResult[index];
				if (dps.compare(dbResult[j]) == 0)
				{
					list<string> list;
					std::string tmp = dbResult[index];
					list = Split::getInstance()->strsplit(tmp, ",");
					servant->dps.number = atof(list.front().c_str());
					list.pop_front();
					servant->dps.Mathbit = atof(list.front().c_str());
				}
				if (gold.compare(dbResult[j]) == 0)
				{
					list<string> list;
					std::string tmp = dbResult[index];
					list = Split::getInstance()->strsplit(tmp, ",");
					servant->gold.number = atof(list.front().c_str());
					list.pop_front();
					servant->gold.Mathbit = atof(list.front().c_str());
				}
				++index;
			}
			m_servantData.push_back(servant);
		}
	}
}
void SqLite::readServantSkill()
{
	char** dbResult;
	int nRow;
	int nColum;
	char* errmsg;
	auto tableresult = sqlite3_get_table(m_pDB, "select * from ServantSkill", &dbResult, &nRow, &nColum, &errmsg);
	if (SQLITE_OK == tableresult)
	{
		std::string id = "ID";
		std::string effect = "effect";
		auto index = nColum;
		for (int i = 0; i < nRow; i++)
		{
			auto skill = new SkillEffect();
			for (int j = 0; j < nColum; j++)
			{
				if (id.compare(dbResult[j]) == 0)
					skill->id = atoi(dbResult[index]);
				if (effect.compare(dbResult[j]) == 0)
					skill->effect = dbResult[index];
				++index;
			}
			m_skillEffect.push_back(skill);
		}
	}
}

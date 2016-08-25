#include "MonsterData.h"
static MonsterData * g_monster;
MonsterData::MonsterData()
{
}

MonsterData::~MonsterData()
{
}
MonsterData * MonsterData::getInstance()
{
	if (!g_monster)
	{
		g_monster = new MonsterData();
	}
	return g_monster;
}
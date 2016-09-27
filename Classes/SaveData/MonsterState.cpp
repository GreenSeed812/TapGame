#include "MonsterState.h"
static MonsterState * g_monster;
MonsterState::MonsterState()
	:m_type(NORMAL)
	, m_saveMonster(false)
{
}

MonsterState::~MonsterState()
{
}
MonsterState * MonsterState::getInstance()
{
	if (!g_monster)
	{
		g_monster = new MonsterState();
	}
	return g_monster;
}
void MonsterState::saveBoss(MonsterData* monster)
{
	m_boss = *monster;
	m_saveMonster = true;
}
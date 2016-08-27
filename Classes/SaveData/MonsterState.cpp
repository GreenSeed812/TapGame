#include "MonsterState.h"
static MonsterState * g_monster;
MonsterState::MonsterState()
	:m_type(NORMAL)
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
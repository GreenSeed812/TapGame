#include"SaveData\PlayerData.h"
#include "Tool\SqLite.h"
static PlayerData *p_dt = nullptr;
PlayerData::PlayerData()
	:m_level(0)
	, m_monsterNum(1)
	, m_playerLevel(1)
{
	m_hpNow.number = SqLite::getInstance()->getMapByID(m_level)->hp.number;
	m_hpNow.Mathbit = SqLite::getInstance()->getMapByID(m_level)->hp.Mathbit;
	m_basedps.number = 1;
	m_basedps.Mathbit = 0;
}

PlayerData::~PlayerData()
{
}
PlayerData * PlayerData::getInstance()
{
	if (!p_dt)
	{
		p_dt = new PlayerData();
	}
	return p_dt;
}
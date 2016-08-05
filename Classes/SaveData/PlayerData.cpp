#include"SaveData\PlayerData.h"
#include "Tool\SqLite.h"
#include <math.h>
static PlayerData *p_dt = nullptr;
PlayerData::PlayerData()
	: m_level(0)
	, m_monsterNum(1)
	, m_playerLevel(1)
{
	m_hpNow.number = SqLite::getInstance()->getHpByID(m_level)->number;
	m_hpNow.Mathbit = SqLite::getInstance()->getHpByID(m_level)->Mathbit;
	
	m_basedps.number = 1;
	m_basedps.Mathbit = 0;

	m_heroDpsAll.number = 1;
	m_heroDpsAll.Mathbit = 0;

	m_latest.m_dropData = SqLite::getInstance()->getDropData();
	m_latest.m_HpData = SqLite::getInstance()->getHpData();
	for (int i = 0; i < 5; i++)
	{
		m_latest.randNpc[i] = SqLite::getInstance()->m_randNpc[i];
	}
	

	
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


//MyNum PlayerData::getMaxHp()
//{
//
//}
int PlayerData::getRandNpc(int r)
{
	return m_latest.randNpc[r];
}
MyNum * PlayerData::getHpByID(int id)
{
	return &m_latest.m_HpData.at(id%5);

}

void PlayerData::levelUp()
{
	m_level++;
	if (m_level > 5)
	{
		m_latest.m_HpData[m_level % 5] = *Ruler::getInstance()->multiplay(&m_latest.m_HpData[m_level % 5], 9.54);
		if (m_level % 5 == 0)
		{
			m_latest.randNpc[0] += 5;
			m_latest.randNpc[0] %= 25;
			m_latest.randNpc[1] += 5;
			m_latest.randNpc[1] %= 25;
		}
	}


}

void PlayerData::heroLevelUp()
{
	if (m_playerLevel < 8)
	{
		m_basedps = SqLite::getInstance()->getDps(m_playerLevel);
		m_playerLevel++;
	}
	else
	{
		double f = (1 + 1 / std::pow((double)m_playerLevel, 0.6) - 1 / pow((double)m_playerLevel, 1.008));
		m_basedps = *Ruler::getInstance()->multiplay(&m_basedps, f);
		m_playerLevel++;
	}
}
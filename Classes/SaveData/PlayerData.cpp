#include"SaveData\PlayerData.h"
#include "Tool\SqLite.h"
#include <math.h>
#include<cocos2d.h>
static PlayerData *p_dt = nullptr;
PlayerData::PlayerData()
	: m_level(0)
	, m_monsterNum(1)
	, m_playerLevel(1)
	, m_waveNow(1)
	, m_dpsMul(0)
	, m_bossTime(30)
	, m_servantNum(0)
	, m_servantAllMul(1)
	, m_maxTime(30000)
	, m_maxWave(11)
{
	auto hp = SqLite::getInstance()->getHpByID(m_level);
	m_hpNow.number = hp.number;
	m_hpNow.Mathbit = hp.Mathbit;
	
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
	for (int i = 0; i < 6; i++)
	{
		m_skillLevel[i] = 0;
	}
	for (int i = 0; i < 33; i++)
	{
		m_servantLevel[i] = 0;
		m_servantBaseDps[i].Mathbit = 0; 
		m_servantBaseDps[i].number = 0;
		m_servantMul[i] = 1;
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
MyNum PlayerData::getHpByID(int id)
{
	/*auto mul = pow(10, id / 5);*/
	if (m_waveNow == 11)
	{
 		auto ret = Ruler::getInstance()->multiplay(m_latest.m_HpData.at(id % 5),SqLite::getInstance()->getBossHp(m_level % 5));
		/*ret = Ruler::getInstance()->multiplay(&ret, mul);*/
		return ret;
	}
	else
	{/*
		auto ret = Ruler::getInstance()->multiplay(&m_latest.m_HpData.at(id % 5), mul);*/
		
		return m_latest.m_HpData.at(id % 5);
	}


}

void PlayerData::levelUp()
{
	m_level++;
	if (m_level > 4)
	{
		m_latest.m_HpData[m_level % 5] = Ruler::getInstance()->multiplay(m_latest.m_HpData[m_level % 5], 9.54);
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
		m_basedps = Ruler::getInstance()->multiplay(m_basedps, f);
		m_playerLevel++;
	}
	cocos2d::CCNotificationCenter::getInstance()->postNotification("TapDpsChange");
}
void PlayerData::defeatMonsterGold()
{
	MyNum baseNum;
	baseNum.number = 1;
	baseNum.Mathbit = 0;
	if (m_level < 2)
		;
	else
	{
		for (int i = 2; i <= m_level + 1; i++)
		{
			auto tmp = Ruler::getInstance()->multiplay(baseNum, 1.58);
			baseNum = tmp;
		}
	}
	auto tmp = Ruler::getInstance()->addNumUp(m_gold, baseNum);
	m_gold = tmp;
	cocos2d::CCNotificationCenter::getInstance()->postNotification("CoinChange");
}
MyNum PlayerData::getDps()
{
	
	return m_basedps;
}
MyNum PlayerData::getHeroDps()
{
	MyNum totalDps;
	totalDps.Mathbit = 0;
	totalDps.number = 0;
	for (size_t i = 0; i < 33; i++)
	{
		totalDps = Ruler::getInstance()->addNumS(totalDps, Ruler::getInstance()->multiplay(m_servantBaseDps[i], m_servantMul[i]));
	}
	totalDps = Ruler::getInstance()->multiplay(totalDps, m_servantAllMul);
	return totalDps;
}
void PlayerData::addGold(MyNum* gold)
{
	m_gold = Ruler::getInstance()->addNum(m_gold, *gold); 
	cocos2d::CCNotificationCenter::getInstance()->postNotification("CoinChange");
}
void PlayerData::subGold(MyNum* gold)
{
	m_gold = Ruler::getInstance()->subNum(m_gold, *gold); 
	cocos2d::CCNotificationCenter::getInstance()->postNotification("CoinChange");
}

void PlayerData::setServantBaseDps(MyNum dps, int id)
{
	m_servantBaseDps[id] =  Ruler::getInstance()->addNum(m_servantBaseDps[id], dps); 
}
MyNum PlayerData::getServantDps(int i)
{
	return Ruler::getInstance()->multiplay(m_servantBaseDps[i], m_servantMul[i]);
}
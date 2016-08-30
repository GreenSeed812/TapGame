#include"SaveData\PlayerData.h"
#include "MonsterState.h"
#include "ArtifactData.h"
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
	, m_dpsMulBase(1)
	, m_bossTime(30)
	, m_servantNum(0)
	, m_servantAllMul(1)
	, m_maxTime(30000)
	, m_maxWave(11)
	, m_explorePer(1.5)
	, m_exploreProb(2)
	, m_skillexploreProb(0)
	, m_bossDpsMul(0)
	, m_TapDpsMul(0)
	, m_latestTapMul(0)
	, m_rareProb(10)
	, m_goldMulBase(0)
	, m_goldMulBox(0)
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
	for (int i = 0; i < 6; i++)
	{
		m_skillOpen[i] = false;
	}
	m_skillData = SqLite::getInstance()->getSkillData();
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
 		auto ret = Ruler::getInstance()->multiplay(m_latest.m_HpData.at(id % 5),SqLite::getInstance()->getBossHp(m_level % 5) * (1 - ArtifactData::getInstance()->getbossHpS()));
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
	if (m_playerLevel < 7)
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
	auto m_upGold = SqLite::getInstance()->getGold();
	for (int i = 1; i < m_playerLevel; i++)
	{
		auto mul = 1 / pow(i, 0.55) - 1 / pow(i, 1.03) + 1;
		m_upGold = Ruler::getInstance()->multiplayUp(m_upGold, mul);
	}
	m_upGold = Ruler::getInstance()->multiplay(m_upGold,(1 - ArtifactData::getInstance()->getHeroLevelupDown()));
	m_gold = Ruler::getInstance()->subNum(m_gold,m_upGold);
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
	auto random = cocos2d::random(0, 99);
	if (random < ArtifactData::getInstance()->gettenGoldPer())
	{
		baseNum = Ruler::getInstance()->multiplay(baseNum, 10);
	}
	baseNum = Ruler::getInstance()->multiplay(baseNum, 1 + m_goldMulBase);
	if (MonsterState::getInstance()->getTypeNow() == MONSTER_TYPE::RARE)
		baseNum = Ruler::getInstance()->multiplay(baseNum, 3 * (1 + m_goldMulBox + ArtifactData::getInstance()->getrmGoldPer()));
	else if (MonsterState::getInstance()->getTypeNow() == MONSTER_TYPE::BOSS)
		baseNum = Ruler::getInstance()->multiplay(baseNum,5);
	auto tmp = Ruler::getInstance()->addNumUp(m_gold, baseNum);
	m_gold = tmp;
	cocos2d::CCNotificationCenter::getInstance()->postNotification("CoinChange");
}
MyNum PlayerData::getdefeatMonsterGold()
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
	return tmp;
}

MyNum PlayerData::getDps()
{
	Ruler::getInstance()->multiplay(m_basedps, m_skillTap + m_dpsMulBase);
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
	if (MonsterState::getInstance()->getTypeNow() == MONSTER_TYPE::BOSS)
	{
		totalDps = Ruler::getInstance()->multiplay(totalDps, m_servantAllMul + ArtifactData::getInstance()->getAllDpsMul() + ArtifactData::getInstance()->getdpsexper() + m_bossDpsMul);
	}
	else
	totalDps = Ruler::getInstance()->multiplay(totalDps, m_servantAllMul + ArtifactData::getInstance()->getAllDpsMul() + ArtifactData::getInstance()->getdpsexper());
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

MyNum PlayerData::getTapDpsNoExp()
{
	auto num = Ruler::getInstance()->multiplay(m_basedps, m_TapDpsMul + m_servantAllMul + ArtifactData::getInstance()->getdpsexper() + ArtifactData::getInstance()->getAllDpsMul());
	auto t = Ruler::getInstance()->addNum(num, getHeroDps());
	auto num1 = Ruler::getInstance()->multiplay(t, m_latestTapMul);
	num = Ruler::getInstance()->addNum(num, num1);
	return num;
}
MyNum PlayerData::getTapDps()
{
	MyNum num;
	if(MonsterState::getInstance()->getTypeNow() == MONSTER_TYPE::BOSS)
		num = Ruler::getInstance()->multiplay(m_basedps, m_TapDpsMul + m_servantAllMul + ArtifactData::getInstance()->getdpsexper() + ArtifactData::getInstance()->getAllDpsMul() + m_bossDpsMul);
	else
		num = Ruler::getInstance()->multiplay(m_basedps, m_TapDpsMul + m_servantAllMul + ArtifactData::getInstance()->getdpsexper() + ArtifactData::getInstance()->getAllDpsMul());
	
	auto t = Ruler::getInstance()->addNum(num,getHeroDps());
	auto num1 = Ruler::getInstance()->multiplay(t,m_latestTapMul);
	num = Ruler::getInstance()->addNum(num,num1);

	auto rand = cocos2d::random(0,99);
	auto explor = m_explorePer;
	if (rand < m_exploreProb + m_skillexploreProb + ArtifactData::getInstance()->getexploreProb())
	{
		
		num = Ruler::getInstance()->multiplay(num, m_explorePer + ArtifactData::getInstance()->getexplorePer());
		return num;
	}
	else
		return num;
}
float PlayerData::getSkillEFF(int i)
{
	if (m_skillLevel[i] < 1)
		return 0;
	else
		return m_skillData.at(i)->initEffect + (m_skillData.at(i)->effPerLevel - 1) * m_skillLevel[i];
}
void PlayerData::unlockSernantSkill(int servantid, int skillid)
{
	auto servant = SqLite::getInstance()->getServantByID(servantid);
	if (servant->skill[skillid].skillID == 1)
	{
		m_servantAllMul += servant->skill[skillid].effect;
	}
	else if (servant->skill[skillid].skillID == 3)
	{
		m_servantMul[servantid] += servant->skill[skillid].effect;
	}
	else if (servant->skill[skillid].skillID == 4)
	{
		m_bossDpsMul = servant->skill[skillid].effect;
	}
	else if (servant->skill[skillid].skillID == 6)
	{
		m_exploreProb += servant->skill[skillid].effect;
	}
	else if (servant->skill[skillid].skillID == 7)
	{
		m_explorePer += servant->skill[skillid].effect;
	}
	else if (servant->skill[skillid].skillID == 8)
	{
		m_TapDpsMul = servant->skill[skillid].effect;
	}
	else if (servant->skill[skillid].skillID == 9)
	{
		m_latestTapMul += servant->skill[skillid].effect;
	}
	else if (servant->skill[skillid].skillID == 25)
	{
		m_goldMulBase += servant->skill[skillid].effect;
	}
	else if (servant->skill[skillid].skillID == 26)
	{
		m_goldMulBox += servant->skill[skillid].effect;
	}
}

void PlayerData::randRareMonster()
{
	auto r = cocos2d::random(0, 99);
	if (r < m_rareProb)
		MonsterState::getInstance()->setMonsterState(MONSTER_TYPE::RARE);
	else
		MonsterState::getInstance()->setMonsterState(MONSTER_TYPE::NORMAL);
	
}
void PlayerData::resetTime()
{
	m_maxTime = 30 * (1 + ArtifactData::getInstance()->getbossTimeUp());
}
void PlayerData::resetMaxWave()
{
	m_maxWave = 11 * (1 - ArtifactData::getInstance()->getWaveDown());
}
void PlayerData::servantLevelUp(int id)
{
	m_servantLevel[id]++;
	auto m_upGold = getservantLevelUpGold(id);
	m_gold = Ruler::getInstance()->subNum(m_gold, m_upGold);
}
MyNum PlayerData::getservantLevelUpGold(int id)
{
	
	auto m_upGold = SqLite::getInstance()->getServantGoldByID(id);

	for (int i = 1; i < m_servantLevel[id]; i++)
	{

		auto mul = 1 + 1 / (pow(i + 1, 0.45) - 1 / pow(i + 1, 6.13));
		m_upGold = Ruler::getInstance()->multiplay(m_upGold, mul);

	}
	m_gold = Ruler::getInstance()->multiplay(m_gold, (1 - ArtifactData::getInstance()->getSLUP()));
	return m_upGold;
}
int PlayerData::getRelifeStone()
{
	return getHeroRelifeStone() + getServantRelifeStone() + getLevelRelifeStone();
}
int PlayerData::getHeroRelifeStone()
{
	return (m_playerLevel - 600) / 100 + 1;
}
int PlayerData::getServantRelifeStone()
{
	return getServantAverLevel() / 33;
}

int PlayerData::getLevelRelifeStone()
{
	return m_level / 50;

}
void PlayerData::saveUserData()
{
}
int PlayerData::getServantAverLevel()
{
	int slevel = 0;
	for (int i = 0; i < m_servantNum; i++)
	{
		slevel += m_servantLevel[i];
	}
	if (m_servantNum == 0)
	{
		return 0;
	}
	return slevel / m_servantNum;

}

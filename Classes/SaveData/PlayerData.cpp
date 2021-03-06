#include"SaveData/PlayerData.h"
#include "MonsterState.h"
#include "ArtifactData.h"
#include "AchieveData.h"
#include "ShopData.h"
#include "State.h"
#include "Tool/SqLite.h"
#include "Tool/TimeTool.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "MissionData.h"
#include "SaveData/DataStatics.h"
using namespace  rapidjson;
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
	, m_relife(false)
	, m_leaveTime(0)
	, m_skillTap(0)
	, m_name("")
	, m_signCount(0)
	, m_signNum(0)
	, m_signTime(0)
	, m_bg(true)
	, m_sou(true)
{
	auto hp = SqLite::getInstance()->getHpByID(m_level%5);
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
		m_servantSkill[i] = 0;
	}
	for (int i = 0; i < 6; i++)
	{
		m_skillOpen[i] = false;
	}
	m_skillData = SqLite::getInstance()->getSkillData();

	for (int i = 0; i < 6; i++)
	{
		m_skillCD[i] = 0;
	}
	
	m_defeatMG.number = 1;
	m_defeatMG.Mathbit = 0;

}
PlayerData::~PlayerData()
{
}
void PlayerData::dataInit()
{
	if (m_playerLevel < 7)
	{
		m_playerUpDps = SqLite::getInstance()->getDps(m_playerLevel);
	}
	else
	{
		m_playerUpDps = SqLite::getInstance()->getDps(6);
		for (int i = 7; i < m_playerLevel; i++)
		{
			double f = (1 + 1 / std::pow((double)i, 0.6) - 1 / pow((double)i, 1.008));
			m_playerUpDps = Ruler::getInstance()->multiplay(m_playerUpDps, f);
		}
	}
	
	m_playerUpGold = SqLite::getInstance()->getGold();
	for (int i = 2; i <= m_playerLevel; i++)
	{
		auto mul = 1 / pow(i, 0.55) - 1 / pow(i, 1.03) + 1;
		m_playerUpGold = Ruler::getInstance()->multiplayUp(m_playerUpGold, mul);
		m_playerUpGold = Ruler::getInstance()->multiplay(m_playerUpGold, (1 - ArtifactData::getInstance()->getHeroLevelupDown()));
	}
	
	for (int i = 0; i < 33; i++)
	{
		m_servantUpGold[i] = SqLite::getInstance()->getServantGoldByID(i);
		m_servantUpDps[i] = SqLite::getInstance()->getServantDpsByID(i);
		for (int lv = 1; lv < m_servantLevel[i]; lv++)
		{
			auto mulG = 1 + 1 / (pow(lv + 1, 0.45) - 1 / pow(lv + 1, 6.13));
			m_servantUpGold[i] = Ruler::getInstance()->multiplay(m_servantUpGold[i], mulG);
			auto pow1 = pow(lv + 1, 0.7);
			auto pow2 = pow(lv + 1, 6);
			auto mul = 1 + 1 / pow1 - 1 / pow2;
			m_servantUpDps[i] = Ruler::getInstance()->multiplay(m_servantUpDps[i], mul);
		}
	}
	m_defeatMG.number = 1;
	m_defeatMG.Mathbit = 0;
	if (m_level == 0)
		;
	else if (m_level == 1)
		m_defeatMG.number = 2;
	else
	{
		for (int i = 2; i <= m_level + 1; i++)
		{
			auto tmp = Ruler::getInstance()->multiplay(m_defeatMG, 1.58);
			m_defeatMG = tmp;
		}
	}
}

PlayerData * PlayerData::getInstance()
{
	if (!p_dt)
	{
		p_dt = new PlayerData();	
		if (cocos2d::UserDefault::getInstance()->getBoolForKey("isSaved"))
		{
			p_dt->init();
		}
		p_dt->dataInit();
	}
	return p_dt;
}
bool PlayerData::init()
{
	std::string json = cocos2d::UserDefault::getInstance()->getStringForKey("UserDefault");
	rapidjson::Document jsd;
	jsd.Parse<0>(json.c_str());
	if (jsd.HasParseError() && jsd.IsObject())  //��ӡ��������
	{
		CCLOG("GetParseError %s\n", jsd.GetParseError());
	}
	
	if (jsd.IsObject() && jsd.HasMember("m_level")) 
	{
		m_gold.number = jsd["m_gold.number"].GetDouble();
		m_gold.Mathbit = jsd["m_gold.Mathbit"].GetInt();
		m_level  = jsd["m_level"].GetInt();
		m_monsterNum = jsd["m_monsterNum"].GetInt();
		m_playerLevel = jsd["m_playerLevel"].GetInt(); 
		m_waveNow = jsd["m_waveNow"].GetInt();
		m_dpsMul = jsd["m_dpsMul"].GetDouble();
		m_dpsMulBase = jsd["m_dpsMulBase"].GetDouble();
		m_bossTime = jsd["m_bossTime"].GetDouble();
		m_servantNum = jsd["m_servantNum"].GetInt();
		m_servantAllMul = jsd["m_servantAllMul"].GetDouble();
		m_maxTime = jsd["m_maxTime"].GetInt();
		m_maxWave = jsd["m_maxWave"].GetInt();
		m_explorePer = jsd["m_explorePer"].GetDouble();
		m_exploreProb = jsd["m_exploreProb"].GetInt();
		m_skillexploreProb = jsd["m_skillexploreProb"].GetInt();
		m_bossDpsMul = jsd["m_bossDpsMul"].GetDouble();
		m_TapDpsMul = jsd["m_TapDpsMul"].GetDouble();
		m_latestTapMul = jsd["m_latestTapMul"].GetDouble();
		m_rareProb = jsd["m_rareProb"].GetInt();
		m_goldMulBase = jsd["m_goldMulBase"].GetDouble();
		m_goldMulBox = jsd["m_goldMulBox"].GetDouble();
		/******************************************************************************************************************************************/
		m_hpNow.number = jsd["hpnum"].GetDouble();
		m_hpNow.Mathbit = jsd["hpmat"].GetInt();
		m_basedps.number = jsd["baseNum"].GetDouble();
		m_basedps.Mathbit = jsd["baseMat"].GetInt();
		m_basedps.number = jsd["baseNum"].GetDouble();
		m_basedps.Mathbit = jsd["baseMat"].GetInt();
		m_heroDpsAll.number = jsd["hdaNum"].GetDouble();
		m_heroDpsAll.Mathbit = jsd["hdaMat"].GetInt();
		m_latest.m_dropData.number = jsd["lstdropDataNum"].GetDouble();
		m_latest.m_dropData.Mathbit = jsd["lstdropDataMat"].GetInt();
		m_latest.randNpc[0] = jsd["lstrandnpc0"].GetInt();
		m_latest.randNpc[1] = jsd["lstrandnpc1"].GetInt();
		m_latest.randNpc[2] = jsd["lstrandnpc2"].GetInt();
		m_latest.randNpc[3] = jsd["lstrandnpc3"].GetInt();
		m_latest.randNpc[4] = jsd["lstrandnpc4"].GetInt();
		m_skillTap = jsd["m_skillTap"].GetDouble();
		for (int i = 0; i < m_latest.m_HpData.size(); i++)
		{
			m_latest.m_HpData.at(i).number = jsd[cocos2d::StringUtils::format("lsthpNum%d", i).c_str()].GetDouble();
			m_latest.m_HpData.at(i).Mathbit = jsd[cocos2d::StringUtils::format("lsthpMat%d", i).c_str()].GetInt();
		}


		for (int i = 0; i < 6; i++)
		{
			m_skillLevel[i] = jsd[cocos2d::StringUtils::format("skilllevel%d", i).c_str()].GetInt();
		}
		for (int i = 0; i < 33; i++)
		{
			if (!jsd.HasMember(cocos2d::StringUtils::format("servantLevel%d", i).c_str()))
				break;
			m_servantLevel[i] = jsd[cocos2d::StringUtils::format("servantLevel%d", i).c_str()].GetInt();
			m_servantBaseDps[i].Mathbit = jsd[cocos2d::StringUtils::format("servantBaseDpsMat%d", i).c_str()].GetInt();
			m_servantBaseDps[i].number = jsd[cocos2d::StringUtils::format("servantBaseDpsNum%d", i).c_str()].GetDouble();
			m_servantMul[i] = jsd[cocos2d::StringUtils::format("servantMul%d", i).c_str()].GetDouble();
			m_servantSkill[i] = jsd[cocos2d::StringUtils::format("m_servantSkill%d", i).c_str()].GetInt(); 
		}

	}
	m_leaveTime = jsd["m_leaveTime"].GetInt();
	m_skillCD[0] = jsd["m_skillCD[0]"].GetDouble();
	m_skillCD[1] = jsd["m_skillCD[1]"].GetDouble();
	m_skillCD[2] = jsd["m_skillCD[2]"].GetDouble();
	m_skillCD[3] = jsd["m_skillCD[3]"].GetDouble();
	m_skillCD[4] = jsd["m_skillCD[4]"].GetDouble();
	m_skillCD[5] = jsd["m_skillCD[5]"].GetDouble();
	m_signCount = jsd["m_signCount"].GetInt();
	m_signNum = jsd["m_signNum"].GetInt();
	m_signTime = jsd["m_signTime"].GetInt();
	m_bg = jsd["m_bg"].GetBool();
	m_sou = jsd["m_sou"].GetBool();

	AchieveData::getInstance()->readUserDefault();
	ArtifactData::getInstance()->readUserDefault();
	MyState::getInstance()->readUserDefault();
	ShopData::getInstance()->readUserData();
	DataStatics::getInstance()->readUserDefault();
	MissionData::getInstance()->readUserDefault();
	return true;
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
	AchieveData::getInstance()->maxLevel(m_level);
	if (m_level == 2)
	{
		m_defeatMG.number = 2;
		m_defeatMG.Mathbit = 0;
	}
	else
	{
		m_defeatMG = Ruler::getInstance()->multiplay(m_defeatMG, 1.58);
	}
	if (m_level > 4)
	{
		m_latest.m_HpData[m_level % 5] = Ruler::getInstance()->multiplay(m_latest.m_HpData[m_level % 5], 9.54);
		/*m_latest.randNpc[4] = m_latest.randNpc[3];
		m_latest.randNpc[3] = m_latest.randNpc[2];
		m_latest.randNpc[2] = m_latest.randNpc[1];*/
		if (m_level % 5 == 0)
		{
			m_latest.randNpc[0] += 5;
			m_latest.randNpc[0] %= 25;
			m_latest.randNpc[1] += 5;
			m_latest.randNpc[1] %= 25;
			if (!m_latest.randNpc[0])
				m_latest.randNpc[0]++;
			if (!m_latest.randNpc[1])
				m_latest.randNpc[1]++;
			int tmp1 = m_latest.randNpc[0];
			int tmp2 = m_latest.randNpc[1];
			m_latest.randNpc[0] = m_latest.randNpc[2]; 
			m_latest.randNpc[1] = m_latest.randNpc[3]; 
			m_latest.randNpc[2] = m_latest.randNpc[4] ;
			m_latest.randNpc[3] = tmp1;
			m_latest.randNpc[4] = tmp2;
		
		}
	}
}

void PlayerData::heroLevelUp()
{
	m_basedps = Ruler::getInstance()->addNum(m_basedps, m_playerUpDps);
	if (m_playerLevel < 6)
	{
		m_playerUpDps = SqLite::getInstance()->getDps(m_playerLevel);
		m_basedps = Ruler::getInstance()->addNum(m_basedps, m_playerUpDps);
		m_playerLevel++;
	}
	else
	{
		double f = (1 + 1 / std::pow((double)m_playerLevel, 0.6) - 1 / pow((double)m_playerLevel, 1.008));
		m_playerUpDps = Ruler::getInstance()->multiplay(m_playerUpDps, f);
		m_playerLevel++;
	}
	auto upGold = Ruler::getInstance()->multiplay(m_playerUpGold, (1 - ArtifactData::getInstance()->getHeroLevelupDown()));
	m_gold = Ruler::getInstance()->subNum(m_gold, upGold);
	auto mul = 1 / pow(m_playerLevel, 0.55) - 1 / pow(m_playerLevel, 1.03) + 1;
	m_playerUpGold = Ruler::getInstance()->multiplayUp(m_playerUpGold, mul);
	AchieveData::getInstance()->maxPlayerLevel(m_playerLevel);
	MissionData::getInstance()->addMissionTimesById(7);
	DataStatics::getInstance()->playerLevelUp();
}
MyNum PlayerData::getPlayerlvupDps()
{
	return m_playerUpDps;
}
MyNum PlayerData::getPlayerlvupGold()
{
	return m_playerUpGold;
}
MyNum PlayerData::getPlayerlvup10Gold()
{
	MyNum m_up10Gold;
	m_up10Gold.number = 0;
	m_up10Gold.Mathbit = 0;
	auto m_upGold = getPlayerlvupGold();
	for (int i = m_playerLevel; i <= m_playerLevel + 10; i++)
	{
		m_up10Gold = Ruler::getInstance()->addNum(m_upGold, m_up10Gold);
		auto mul = 1 / pow(i, 0.55) - 1 / pow(i, 1.03) + 1;
		m_upGold = Ruler::getInstance()->multiplayUp(m_upGold, mul);
	}
	m_up10Gold = Ruler::getInstance()->addNum(m_upGold, m_up10Gold);
	return m_up10Gold;
}
MyNum PlayerData::getPlayerlvup100Gold()
{
	MyNum m_up100Gold;
	m_up100Gold.number = 0;
	m_up100Gold.Mathbit = 0;
	auto m_upGold = getPlayerlvupGold();
	for (int i = m_playerLevel; i <= m_playerLevel + 100; i++)
	{
		m_up100Gold = Ruler::getInstance()->addNum(m_upGold, m_up100Gold);
		auto mul = 1 / pow(i, 0.55) - 1 / pow(i, 1.03) + 1;
		m_upGold = Ruler::getInstance()->multiplayUp(m_upGold, mul);
	}
	m_up100Gold = Ruler::getInstance()->addNum(m_upGold, m_up100Gold);
	return m_up100Gold;
}
MyNum PlayerData::defeatMonsterGold()
{
	auto baseNum = m_defeatMG;
	
	auto random = cocos2d::random(0, 99);
	if (random < ArtifactData::getInstance()->gettenGoldPer())
	{
		baseNum = Ruler::getInstance()->multiplay(baseNum, 10);
	}
	baseNum = Ruler::getInstance()->multiplay(baseNum, 1 + m_goldMulBase);
	if (MonsterState::getInstance()->getTypeNow() == MONSTER_TYPE::RARE)
	{
		baseNum = Ruler::getInstance()->multiplay(baseNum, 3 * (1 + m_goldMulBox + ArtifactData::getInstance()->getrmGoldPer()));
	}
	else if (MonsterState::getInstance()->getTypeNow() == MONSTER_TYPE::BOSS)
	{
		baseNum = Ruler::getInstance()->multiplay(baseNum, 5);
	}
	if (ShopData::getInstance()->getItemBeUsedById(10))
		baseNum = Ruler::getInstance()->multiplay(baseNum, 1.5);
	return baseNum;
}
MyNum PlayerData::getdefeatMonsterGold()
{	
	return m_defeatMG;
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
	AchieveData::getInstance()->addCoin(*gold);
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
		num = Ruler::getInstance()->multiplay(m_basedps,m_skillTap + m_TapDpsMul + m_servantAllMul + ArtifactData::getInstance()->getdpsexper() + ArtifactData::getInstance()->getAllDpsMul() + m_bossDpsMul);
	else
		num = Ruler::getInstance()->multiplay(m_basedps,m_skillTap + m_TapDpsMul + m_servantAllMul + ArtifactData::getInstance()->getdpsexper() + ArtifactData::getInstance()->getAllDpsMul());
	
	auto t = Ruler::getInstance()->addNum(num,getHeroDps());
	auto num1 = Ruler::getInstance()->multiplay(t,m_latestTapMul);
	num = Ruler::getInstance()->addNum(num,num1);

	auto rand = cocos2d::random(0,99);
	auto explor = m_explorePer;
	if (rand < m_exploreProb + m_skillexploreProb + ArtifactData::getInstance()->getexploreProb())
	{
		AchieveData::getInstance()->addexploreNum();
		if (ShopData::getInstance()->getItemBeUsedById(1))
		{
			num = Ruler::getInstance()->multiplay(num, m_explorePer + SqLite::getInstance()->getItemByID(1)->eff + ArtifactData::getInstance()->getexplorePer());
		}
		else
			num = Ruler::getInstance()->multiplay(num, m_explorePer + ArtifactData::getInstance()->getexplorePer());
		if (ShopData::getInstance()->getItemBeUsedById(2))
			num = Ruler::getInstance()->multiplay(num, 2);
		return num;
	}
	else
	{
		if (ShopData::getInstance()->getItemBeUsedById(2))
			num = Ruler::getInstance()->multiplay(num, 2);
		return num;
	}
}
float PlayerData::getSkillEFF(int i)
{
	if (m_skillLevel[i] < 1)
		return 0;
	else
		return m_skillData.at(i)->initEffect + m_skillData.at(i)->effPerLevel * (m_skillLevel[i] - 1);
}
void PlayerData::unlockSernantSkill(int servantid, int skillid)
{
	auto servant = SqLite::getInstance()->getServantByID(servantid);
	if (m_servantSkill[servantid] < 7)
	{
		m_servantSkill[servantid]++;
	}
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
	auto m_upGold = getservantLevelUpGold(id); 
	m_upGold = Ruler::getInstance()->multiplay(m_upGold, (1 - ArtifactData::getInstance()->getSLUP()));
	m_gold = Ruler::getInstance()->subNum(m_gold, m_upGold);
	m_servantLevel[id]++;
	auto pow1 = pow(m_servantLevel[id], 0.7);
	auto pow2 = pow(m_servantLevel[id], 6);
	auto mul = 1 + 1 / pow1 - 1 / pow2;
	m_servantBaseDps[id] = Ruler::getInstance()->addNum(m_servantUpDps[id], m_servantBaseDps[id]);
	m_servantUpDps[id] = Ruler::getInstance()->multiplay(m_servantUpDps[id], mul);
	auto mulG  = 1 + 1 / (pow(m_servantLevel[id] + 1, 0.45) - 1 / pow(m_servantLevel[id] + 1, 6.13));
	m_upGold = Ruler::getInstance()->multiplay(m_upGold, mul);
	m_servantUpGold[id] = Ruler::getInstance()->multiplay(m_servantUpGold[id], mulG);

}
MyNum PlayerData::getservantToalDps(int id)
{
	auto servantDps = Ruler::getInstance()->multiplay(m_servantBaseDps[id],m_servantMul[id]);
	return servantDps;
	
}
MyNum PlayerData::getservantLevelUpDps(int id)
{
	return m_servantUpDps[id];
}
MyNum PlayerData::getservantLevelUp10Dps(int id)
{
	MyNum upDps;
	upDps.Mathbit = 0;
	upDps.number = 0;
	auto servantLsDps = getservantLevelUpDps(id);
	for (int i = m_servantLevel[id]; i < m_servantLevel[id]+10; i++)
	{
		upDps = Ruler::getInstance()->addNum(upDps, servantLsDps);
		auto pow1 = pow(i + 1, 0.7);
		auto pow2 = pow(i + 1, 6);
		auto mul = 1 + 1 / pow1 - 1 / pow2;
		servantLsDps = Ruler::getInstance()->multiplay(servantLsDps, mul);
	}
	return upDps;
}
MyNum PlayerData::getservantLevelUp100Dps(int id)
{
	MyNum upDps;
	upDps.Mathbit = 0;
	upDps.number = 0;
	auto servantLsDps = getservantLevelUpDps(id);
	for (int i = m_servantLevel[id]; i < m_servantLevel[id] + 100; i++)
	{
		upDps = Ruler::getInstance()->addNum(upDps, servantLsDps);
		auto pow1 = pow(i + 1, 0.7);
		auto pow2 = pow(i + 1, 6);
		auto mul = 1 + 1 / pow1 - 1 / pow2;
		servantLsDps = Ruler::getInstance()->multiplay(servantLsDps, mul);
	}
	return upDps;
}
MyNum PlayerData::getservantLevelUpGold(int id)
{	
	return m_servantUpGold[id];
}
MyNum PlayerData::getservantLevelUp10Gold(int id)
{
	MyNum m_up10Gold;
	m_up10Gold.number = 0;
	m_up10Gold.Mathbit = 0;
	auto m_upGold = getservantLevelUpGold(id);
	for (size_t i = m_servantLevel[id]; i <= m_servantLevel[id]+10; i++)
	{
		m_up10Gold = Ruler::getInstance()->addNum(m_up10Gold, m_upGold);
		auto mul = 1 + 1 / (pow(i + 1, 0.45) - 1 / pow(i + 1, 6.13));
		m_upGold = Ruler::getInstance()->multiplay(m_upGold, mul);
	}
	m_up10Gold = Ruler::getInstance()->addNum(m_up10Gold, m_upGold);
	return m_up10Gold;
}

MyNum PlayerData::getservantLevelUp100Gold(int id)
{
	MyNum m_up100Gold;
	m_up100Gold.number = 0;
	m_up100Gold.Mathbit = 0;
	auto m_upGold = getservantLevelUpGold(id);
	for (size_t i = m_servantLevel[id]; i <= m_servantLevel[id] + 100; i++)
	{
		m_up100Gold = Ruler::getInstance()->addNum(m_up100Gold, m_upGold);
		auto mul = 1 + 1 / (pow(i + 1, 0.45) - 1 / pow(i + 1, 6.13));
		m_upGold = Ruler::getInstance()->multiplay(m_upGold, mul);
	}
	m_up100Gold = Ruler::getInstance()->addNum(m_up100Gold, m_upGold);
	return m_up100Gold;
}
int PlayerData::getRelifeStone()
{
	if (ShopData::getInstance()->getItemBeUsedById(8))
	{
		return (getHeroRelifeStone() + getServantRelifeStone() + getLevelRelifeStone()) * 2;
		
	}
	else
	return getHeroRelifeStone() + getServantRelifeStone() + getLevelRelifeStone();
}
int PlayerData::getHeroRelifeStone()
{
	return (m_playerLevel - 600) / 100 + 1;
}
int PlayerData::getServantRelifeStone()
{
	return getServantAverLevel() * m_servantNum / 66;
}

int PlayerData::getLevelRelifeStone()
{
	return m_level / 50;
}
void PlayerData::saveUserData()
{
	m_leaveTime = TimeTool::getInstance()->getTime();
	Document document;
	document.SetObject();
	Document::AllocatorType& allocator = document.GetAllocator();
	rapidjson::Value array(kArrayType);
	rapidjson::Value object(kObjectType);
	document.AddMember("m_gold.number", m_gold.number, allocator); 
	document.AddMember("m_gold.Mathbit", m_gold.Mathbit, allocator);
	document.AddMember("m_level", m_level, allocator);
	document.AddMember("m_monsterNum", m_monsterNum, allocator);
	document.AddMember("m_playerLevel", m_playerLevel, allocator);
	document.AddMember("m_waveNow", m_waveNow, allocator);
	document.AddMember("m_dpsMul", m_dpsMul, allocator);
	document.AddMember("m_dpsMulBase", m_dpsMulBase, allocator);
	document.AddMember("m_bossTime", m_bossTime, allocator);
	document.AddMember("m_servantNum", m_servantNum, allocator);
	document.AddMember("m_servantAllMul", m_servantAllMul, allocator);
	document.AddMember("m_maxTime", m_maxTime, allocator);
	document.AddMember("m_maxWave", m_maxWave, allocator);
	document.AddMember("m_explorePer", m_explorePer, allocator);
	document.AddMember("m_exploreProb", m_exploreProb, allocator);
	document.AddMember("m_skillexploreProb", m_skillexploreProb, allocator);
	document.AddMember("m_bossDpsMul", m_bossDpsMul, allocator);
	document.AddMember("m_TapDpsMul", m_TapDpsMul, allocator);
	document.AddMember("m_latestTapMul", m_latestTapMul, allocator);
	document.AddMember("m_rareProb", m_rareProb, allocator);
	document.AddMember("m_goldMulBase", m_goldMulBase, allocator);
	document.AddMember("m_goldMulBox", m_goldMulBox, allocator);
	document.AddMember("hpnum", m_hpNow.number, allocator);
	document.AddMember("hpmat", m_hpNow.Mathbit, allocator);
	document.AddMember("baseNum", m_basedps.number, allocator);
	document.AddMember("baseMat", m_basedps.Mathbit, allocator);
	document.AddMember("hdaNum", m_heroDpsAll.number, allocator);
	document.AddMember("hdaMat", m_heroDpsAll.Mathbit, allocator);
	document.AddMember("lstdropDataNum", m_latest.m_dropData.number, allocator);
	document.AddMember("lstdropDataMat", m_latest.m_dropData.Mathbit, allocator);
	document.AddMember("lstrandnpc0", m_latest.randNpc[0], allocator);
	document.AddMember("lstrandnpc1", m_latest.randNpc[1], allocator);
	document.AddMember("lstrandnpc2", m_latest.randNpc[2], allocator);
	document.AddMember("lstrandnpc3", m_latest.randNpc[3], allocator);
	document.AddMember("lstrandnpc4", m_latest.randNpc[4], allocator);


	document.AddMember("lsthpNum0", m_latest.m_HpData.at(0).number, allocator);
	document.AddMember("lsthpNum1", m_latest.m_HpData.at(1).number, allocator);
	document.AddMember("lsthpNum2", m_latest.m_HpData.at(2).number, allocator);
	document.AddMember("lsthpNum3", m_latest.m_HpData.at(3).number, allocator);
	document.AddMember("lsthpNum4", m_latest.m_HpData.at(4).number, allocator);
	document.AddMember("lsthpMat0", m_latest.m_HpData.at(0).Mathbit, allocator);
	document.AddMember("lsthpMat1", m_latest.m_HpData.at(1).Mathbit, allocator);
	document.AddMember("lsthpMat2", m_latest.m_HpData.at(2).Mathbit, allocator);
	document.AddMember("lsthpMat3", m_latest.m_HpData.at(3).Mathbit, allocator);
	document.AddMember("lsthpMat4", m_latest.m_HpData.at(4).Mathbit, allocator);

	
	document.AddMember("skilllevel0", m_skillLevel[0], allocator);
	document.AddMember("skilllevel1", m_skillLevel[1], allocator);
	document.AddMember("skilllevel2", m_skillLevel[2], allocator);
	document.AddMember("skilllevel3", m_skillLevel[3], allocator);
	document.AddMember("skilllevel4", m_skillLevel[4], allocator);
	document.AddMember("skilllevel5", m_skillLevel[5], allocator);

	
	document.AddMember("servantLevel0", m_servantLevel[0], allocator);
	document.AddMember("servantBaseDpsMat0", m_servantBaseDps[0].Mathbit, allocator);
	document.AddMember("servantMul0",  m_servantMul[0], allocator);
	document.AddMember("servantBaseDpsNum0", m_servantBaseDps[0].number, allocator);
	document.AddMember("servantLevel1", m_servantLevel[1], allocator);
	document.AddMember("servantBaseDpsMat1", m_servantBaseDps[1].Mathbit, allocator);
	document.AddMember("servantMul1", m_servantMul[1], allocator);
	document.AddMember("servantBaseDpsNum1", m_servantBaseDps[1].number, allocator);
	document.AddMember("servantLevel2", m_servantLevel[2], allocator);
	document.AddMember("servantBaseDpsMat2", m_servantBaseDps[2].Mathbit, allocator);
	document.AddMember("servantMul2", m_servantMul[2], allocator);
	document.AddMember("servantBaseDpsNum2", m_servantBaseDps[2].number, allocator);
	document.AddMember("servantLevel3", m_servantLevel[3], allocator);
	document.AddMember("servantBaseDpsMat3", m_servantBaseDps[3].Mathbit, allocator);
	document.AddMember("servantMul3", m_servantMul[3], allocator);
	document.AddMember("servantBaseDpsNum3", m_servantBaseDps[3].number, allocator);
	document.AddMember("servantLevel4", m_servantLevel[4], allocator);
	document.AddMember("servantBaseDpsMat4", m_servantBaseDps[4].Mathbit, allocator);
	document.AddMember("servantMul4", m_servantMul[4], allocator);
	document.AddMember("servantBaseDpsNum4", m_servantBaseDps[4].number, allocator);
	document.AddMember("servantLevel5", m_servantLevel[5], allocator);
	document.AddMember("servantBaseDpsMat5", m_servantBaseDps[5].Mathbit, allocator);
	document.AddMember("servantMul5", m_servantMul[5], allocator);
	document.AddMember("servantBaseDpsNum5", m_servantBaseDps[5].number, allocator);
	document.AddMember("servantLevel6", m_servantLevel[6], allocator);
	document.AddMember("servantBaseDpsMat6", m_servantBaseDps[6].Mathbit, allocator);
	document.AddMember("servantMul6", m_servantMul[6], allocator);
	document.AddMember("servantBaseDpsNum6", m_servantBaseDps[6].number, allocator);
	document.AddMember("servantLevel7", m_servantLevel[7], allocator);
	document.AddMember("servantBaseDpsMat7", m_servantBaseDps[7].Mathbit, allocator);
	document.AddMember("servantMul7", m_servantMul[7], allocator);
	document.AddMember("servantBaseDpsNum7", m_servantBaseDps[7].number, allocator);
	document.AddMember("servantLevel8", m_servantLevel[8], allocator);
	document.AddMember("servantBaseDpsMat8", m_servantBaseDps[8].Mathbit, allocator);
	document.AddMember("servantMul8", m_servantMul[8], allocator);
	document.AddMember("servantBaseDpsNum8", m_servantBaseDps[8].number, allocator);
	document.AddMember("servantLevel9", m_servantLevel[9], allocator);
	document.AddMember("servantBaseDpsMat9", m_servantBaseDps[9].Mathbit, allocator);
	document.AddMember("servantMul9", m_servantMul[9], allocator);
	document.AddMember("servantBaseDpsNum9", m_servantBaseDps[9].number, allocator);
	document.AddMember("servantLevel10", m_servantLevel[10], allocator);
	document.AddMember("servantBaseDpsMat10", m_servantBaseDps[10].Mathbit, allocator);
	document.AddMember("servantMul10", m_servantMul[10], allocator);
	document.AddMember("servantBaseDpsNum10", m_servantBaseDps[10].number, allocator);
	document.AddMember("servantLevel11", m_servantLevel[11], allocator);
	document.AddMember("servantBaseDpsMat11", m_servantBaseDps[11].Mathbit, allocator);
	document.AddMember("servantMul11", m_servantMul[11], allocator);
	document.AddMember("servantBaseDpsNum11", m_servantBaseDps[11].number, allocator);
	document.AddMember("servantLevel12", m_servantLevel[12], allocator);
	document.AddMember("servantBaseDpsMat12", m_servantBaseDps[12].Mathbit, allocator);
	document.AddMember("servantMul12", m_servantMul[12], allocator);
	document.AddMember("servantBaseDpsNum12", m_servantBaseDps[12].number, allocator);
	document.AddMember("servantLevel13", m_servantLevel[13], allocator);
	document.AddMember("servantBaseDpsMat13", m_servantBaseDps[13].Mathbit, allocator);
	document.AddMember("servantMul13", m_servantMul[13], allocator);
	document.AddMember("servantBaseDpsNum13", m_servantBaseDps[13].number, allocator);
	document.AddMember("servantLevel14", m_servantLevel[14], allocator);
	document.AddMember("servantBaseDpsMat14", m_servantBaseDps[14].Mathbit, allocator);
	document.AddMember("servantMul14", m_servantMul[14], allocator);
	document.AddMember("servantBaseDpsNum14", m_servantBaseDps[14].number, allocator);
	document.AddMember("servantLevel15", m_servantLevel[15], allocator);
	document.AddMember("servantBaseDpsMat15", m_servantBaseDps[15].Mathbit, allocator);
	document.AddMember("servantMul15", m_servantMul[15], allocator);
	document.AddMember("servantBaseDpsNum15", m_servantBaseDps[15].number, allocator);
	document.AddMember("servantLevel16", m_servantLevel[16], allocator);
	document.AddMember("servantBaseDpsMat16", m_servantBaseDps[16].Mathbit, allocator);
	document.AddMember("servantMul16", m_servantMul[16], allocator);
	document.AddMember("servantBaseDpsNum16", m_servantBaseDps[16].number, allocator);
	document.AddMember("servantLevel17", m_servantLevel[17], allocator);
	document.AddMember("servantBaseDpsMat17", m_servantBaseDps[17].Mathbit, allocator);
	document.AddMember("servantMul17", m_servantMul[17], allocator);
	document.AddMember("servantBaseDpsNum17", m_servantBaseDps[17].number, allocator);
	document.AddMember("servantLevel18", m_servantLevel[18], allocator);
	document.AddMember("servantBaseDpsMat18", m_servantBaseDps[18].Mathbit, allocator);
	document.AddMember("servantMul18", m_servantMul[18], allocator);
	document.AddMember("servantBaseDpsNum18", m_servantBaseDps[18].number, allocator);
	document.AddMember("servantLevel19", m_servantLevel[19], allocator);
	document.AddMember("servantBaseDpsMat19", m_servantBaseDps[19].Mathbit, allocator);
	document.AddMember("servantMul19", m_servantMul[19], allocator);
	document.AddMember("servantBaseDpsNum19", m_servantBaseDps[19].number, allocator);
	document.AddMember("servantLevel20", m_servantLevel[20], allocator);
	document.AddMember("servantBaseDpsMat20", m_servantBaseDps[20].Mathbit, allocator);
	document.AddMember("servantMul20", m_servantMul[20], allocator);
	document.AddMember("servantBaseDpsNum20", m_servantBaseDps[20].number, allocator);
	document.AddMember("servantLevel21", m_servantLevel[21], allocator);
	document.AddMember("servantBaseDpsMat21", m_servantBaseDps[21].Mathbit, allocator);
	document.AddMember("servantMul21", m_servantMul[21], allocator);
	document.AddMember("servantBaseDpsNum21", m_servantBaseDps[21].number, allocator);
	document.AddMember("servantLevel22", m_servantLevel[22], allocator);
	document.AddMember("servantBaseDpsMat22", m_servantBaseDps[22].Mathbit, allocator);
	document.AddMember("servantMul22", m_servantMul[22], allocator);
	document.AddMember("servantBaseDpsNum22", m_servantBaseDps[22].number, allocator);
	document.AddMember("servantLevel23", m_servantLevel[23], allocator);
	document.AddMember("servantBaseDpsMat23", m_servantBaseDps[23].Mathbit, allocator);
	document.AddMember("servantMul23", m_servantMul[23], allocator);
	document.AddMember("servantBaseDpsNum23", m_servantBaseDps[23].number, allocator);
	document.AddMember("servantLevel24", m_servantLevel[24], allocator);
	document.AddMember("servantBaseDpsMat24", m_servantBaseDps[24].Mathbit, allocator);
	document.AddMember("servantMul24", m_servantMul[24], allocator);
	document.AddMember("servantBaseDpsNum24", m_servantBaseDps[24].number, allocator);
	document.AddMember("servantLevel25", m_servantLevel[25], allocator);
	document.AddMember("servantBaseDpsMat25", m_servantBaseDps[25].Mathbit, allocator);
	document.AddMember("servantMul25", m_servantMul[25], allocator);
	document.AddMember("servantBaseDpsNum25", m_servantBaseDps[25].number, allocator);
	document.AddMember("servantLevel26", m_servantLevel[26], allocator);
	document.AddMember("servantBaseDpsMat26", m_servantBaseDps[26].Mathbit, allocator);
	document.AddMember("servantMul26", m_servantMul[26], allocator);
	document.AddMember("servantBaseDpsNum26", m_servantBaseDps[26].number, allocator);
	document.AddMember("servantLevel27", m_servantLevel[27], allocator);
	document.AddMember("servantBaseDpsMat27", m_servantBaseDps[27].Mathbit, allocator);
	document.AddMember("servantMul27", m_servantMul[27], allocator);
	document.AddMember("servantBaseDpsNum27", m_servantBaseDps[27].number, allocator);
	document.AddMember("servantLevel28", m_servantLevel[28], allocator);
	document.AddMember("servantBaseDpsMat28", m_servantBaseDps[28].Mathbit, allocator);
	document.AddMember("servantMul28", m_servantMul[28], allocator);
	document.AddMember("servantBaseDpsNum28", m_servantBaseDps[28].number, allocator);
	document.AddMember("servantLevel29", m_servantLevel[29], allocator);
	document.AddMember("servantBaseDpsMat29", m_servantBaseDps[29].Mathbit, allocator);
	document.AddMember("servantMul29", m_servantMul[29], allocator);
	document.AddMember("servantBaseDpsNum29", m_servantBaseDps[29].number, allocator);
	document.AddMember("servantLevel30", m_servantLevel[30], allocator);
	document.AddMember("servantBaseDpsMat30", m_servantBaseDps[30].Mathbit, allocator);
	document.AddMember("servantMul30", m_servantMul[30], allocator);
	document.AddMember("servantBaseDpsNum30", m_servantBaseDps[30].number, allocator);
	document.AddMember("servantLevel31", m_servantLevel[31], allocator);
	document.AddMember("servantBaseDpsMat31", m_servantBaseDps[31].Mathbit, allocator);
	document.AddMember("servantMul31", m_servantMul[31], allocator);
	document.AddMember("servantBaseDpsNum31", m_servantBaseDps[31].number, allocator);
	document.AddMember("servantLevel32", m_servantLevel[32], allocator);
	document.AddMember("servantBaseDpsMat32", m_servantBaseDps[32].Mathbit, allocator);
	document.AddMember("servantMul32", m_servantMul[32], allocator);
	document.AddMember("servantBaseDpsNum32", m_servantBaseDps[32].number, allocator);
	document.AddMember("m_servantSkill0", m_servantSkill[0], allocator);
	document.AddMember("m_servantSkill1", m_servantSkill[1], allocator);
	document.AddMember("m_servantSkill2", m_servantSkill[2], allocator);
	document.AddMember("m_servantSkill3", m_servantSkill[3], allocator);
	document.AddMember("m_servantSkill4", m_servantSkill[4], allocator);
	document.AddMember("m_servantSkill5", m_servantSkill[5], allocator);
	document.AddMember("m_servantSkill6", m_servantSkill[6], allocator);
	document.AddMember("m_servantSkill7", m_servantSkill[7], allocator);
	document.AddMember("m_servantSkill8", m_servantSkill[8], allocator);
	document.AddMember("m_servantSkill9", m_servantSkill[9], allocator);
	document.AddMember("m_servantSkill10", m_servantSkill[10], allocator);
	document.AddMember("m_servantSkill11", m_servantSkill[11], allocator);
	document.AddMember("m_servantSkill12", m_servantSkill[12], allocator);
	document.AddMember("m_servantSkill13", m_servantSkill[13], allocator);
	document.AddMember("m_servantSkill14", m_servantSkill[14], allocator);
	document.AddMember("m_servantSkill15", m_servantSkill[15], allocator);
	document.AddMember("m_servantSkill16", m_servantSkill[16], allocator);
	document.AddMember("m_servantSkill17", m_servantSkill[17], allocator);
	document.AddMember("m_servantSkill18", m_servantSkill[18], allocator);
	document.AddMember("m_servantSkill19", m_servantSkill[19], allocator);
	document.AddMember("m_servantSkill20", m_servantSkill[20], allocator);
	document.AddMember("m_servantSkill21", m_servantSkill[21], allocator);
	document.AddMember("m_servantSkill22", m_servantSkill[22], allocator);
	document.AddMember("m_servantSkill23", m_servantSkill[23], allocator);
	document.AddMember("m_servantSkill24", m_servantSkill[24], allocator);
	document.AddMember("m_servantSkill25", m_servantSkill[25], allocator);
	document.AddMember("m_servantSkill26", m_servantSkill[26], allocator);
	document.AddMember("m_servantSkill27", m_servantSkill[27], allocator);
	document.AddMember("m_servantSkill28", m_servantSkill[28], allocator);
	document.AddMember("m_servantSkill29", m_servantSkill[29], allocator);
	document.AddMember("m_servantSkill30", m_servantSkill[30], allocator);
	document.AddMember("m_servantSkill31", m_servantSkill[31], allocator);
	document.AddMember("m_servantSkill32", m_servantSkill[32], allocator);
	document.AddMember("m_leaveTime", m_leaveTime, allocator);
	document.AddMember("m_skillTap", m_skillTap, allocator);
	document.AddMember("m_skillCD[0]", m_skillCD[0], allocator);
	document.AddMember("m_skillCD[1]", m_skillCD[1], allocator);
	document.AddMember("m_skillCD[2]", m_skillCD[2], allocator);
	document.AddMember("m_skillCD[3]", m_skillCD[3], allocator);
	document.AddMember("m_skillCD[4]", m_skillCD[4], allocator);
	document.AddMember("m_skillCD[5]", m_skillCD[5], allocator);
	document.AddMember("m_signCount", m_signCount, allocator);
	document.AddMember("m_signTime", m_signTime, allocator);
	document.AddMember("m_bg", m_bg, allocator);
	document.AddMember("m_sou", m_sou, allocator);
	document.AddMember("m_signNum", m_signNum, allocator);

	ArtifactData::getInstance()->saveUserDefault(document);
	AchieveData::getInstance()->saveUserDefault(document);
	MyState::getInstance()->saveUserDefault(document);
	ShopData::getInstance()->saveUserData(document);
	DataStatics::getInstance()->saveUserDefault(document);
	MissionData::getInstance()->saveUserDefault(document);
	StringBuffer buffer;
	rapidjson::Writer<StringBuffer> writer(buffer);
	document.Accept(writer);
	auto json = buffer.GetString();
	
	cocos2d::UserDefault::getInstance()->setStringForKey("UserDefault", buffer.GetString());
	cocos2d::UserDefault::getInstance()->setBoolForKey("isSaved", true);
	cocos2d::UserDefault::getInstance()->flush();
	
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
void PlayerData::relife()
{
	ArtifactData::getInstance()->addArtiStone(getRelifeStone());
	ShopData::getInstance()->stopItemById(8);
	delete p_dt;
	p_dt = new PlayerData();
	p_dt->dataInit();
	m_relife = true;
	
}
MyNum PlayerData::getServantUnlockGold(int id,int skillid)
{
	auto m_upGold = SqLite::getInstance()->getServantGoldByID(id);
	if (skillid >= 7)
	{
		skillid = 6;
	}
	for (int i = 1; i <= SqLite::getInstance()->m_servantUnlock.at(skillid); i++)
	{
		auto mul = 1 + 1 / (pow(i + 1, 0.45) - 1 / pow(i + 1, 6.13));
		m_upGold = Ruler::getInstance()->multiplay(m_upGold, mul);
	}
	m_upGold = Ruler::getInstance()->multiplay(m_upGold, (1 - ArtifactData::getInstance()->getSSUD()));
	m_upGold = Ruler::getInstance()->multiplay(m_upGold, 5);
	return m_upGold;
}
MyNum PlayerData::getPlayerlvup10Dps()
{
	auto m_upDps = getPlayerlvupDps();
	for (int i = m_playerLevel; i < m_playerLevel + 10; i++)
	{
		double f = (1 + 1 / std::pow((double)m_playerLevel, 0.6) - 1 / pow((double)m_playerLevel, 1.008));
		m_upDps = Ruler::getInstance()->multiplay(m_upDps, f);
	}
	return m_upDps;
}
MyNum PlayerData::getPlayerlvup100Dps()
{
	auto m_upDps = getPlayerlvupDps();
	for (int i = m_playerLevel; i < m_playerLevel + 100; i++)
	{
		double f = (1 + 1 / std::pow((double)m_playerLevel, 0.6) - 1 / pow((double)m_playerLevel, 1.008));
		m_upDps = Ruler::getInstance()->multiplay(m_upDps, f);
	}
	return m_upDps;
}
void PlayerData::setSkillCD(int id,float t)
{
	m_skillCD[id-1] = t;
}
void PlayerData::addServantNum()
{
	m_servantNum++; 
	if (DataStatics::getInstance()->getservantMaxNum() < m_servantNum)
		DataStatics::getInstance()->setservantNumMax(m_servantNum);
}

void PlayerData::setSignCount()
{
	if (m_signCount >= 6)
	{
		m_signNum++;
		m_signCount = 0;
	}
	else
	{
		m_signCount++;
	}
	if (m_signNum > 1)
	{
		m_signNum = 0;
	}
}

int PlayerData::getSignTime()
{
	if (m_signTime == 0)
	{
		return TimeTool::getInstance()->getTime();
	}
	return m_signTime;
}
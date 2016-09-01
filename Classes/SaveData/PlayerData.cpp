#include"SaveData/PlayerData.h"
#include "MonsterState.h"
#include "ArtifactData.h"
#include "AchieveData.h"
#include "Tool/SqLite.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
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
		if (cocos2d::UserDefault::getInstance()->isXMLFileExist())
		{
			//remove(cocos2d::UserDefault::getInstance()->getXMLFilePath().c_str());
			p_dt->init();
		}
	}
	return p_dt;
}
bool PlayerData::init()
{
	std::string json = cocos2d::UserDefault::getInstance()->getStringForKey("UserDefault");
	rapidjson::Document jsd;
	jsd.Parse<0>(json.c_str());
	if (jsd.HasParseError() && jsd.IsObject())  //¥Ú”°Ω‚Œˆ¥ÌŒÛ
	{
		CCLOG("GetParseError %s\n", jsd.GetParseError());
	}
	
	if (jsd.IsObject() && jsd.HasMember("m_level")) 
	{
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
		}
	}
	AchieveData::getInstance()->readUserDefault();
	ArtifactData::getInstance()->readUserDefault();
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
	AchieveData::getInstance()->maxPlayerLevel(m_playerLevel);
	auto m_upGold = getPlayerlvupGold();
	m_gold = Ruler::getInstance()->subNum(m_gold,m_upGold);
}
MyNum PlayerData::getPlayerlvupDps()
{
	MyNum m_upDps;
	if (m_playerLevel < 7)
	{
		m_upDps = SqLite::getInstance()->getDps(m_playerLevel);
	}
	else
	{
		m_upDps  = SqLite::getInstance()->getDps(6);
		for (int i = 7; i <= m_playerLevel; i++)
		{
			double f = (1 + 1 / std::pow((double)m_playerLevel, 0.6) - 1 / pow((double)m_playerLevel, 1.008));
			m_upDps = Ruler::getInstance()->multiplay(m_upDps, f);
		}

	}
	return m_upDps;
}
MyNum PlayerData::getPlayerlvupGold()
{

	auto m_upGold = SqLite::getInstance()->getGold();
	for (int i = 1; i <= m_playerLevel; i++)
	{
		auto mul = 1 / pow(i, 0.55) - 1 / pow(i, 1.03) + 1;
		m_upGold = Ruler::getInstance()->multiplayUp(m_upGold, mul);
	}
	m_upGold = Ruler::getInstance()->multiplay(m_upGold, (1 - ArtifactData::getInstance()->getHeroLevelupDown()));
	return m_upGold;
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
	AchieveData::getInstance()->killMonster();
	baseNum = Ruler::getInstance()->multiplay(baseNum, 1 + m_goldMulBase);
	if (MonsterState::getInstance()->getTypeNow() == MONSTER_TYPE::RARE)
	{
		baseNum = Ruler::getInstance()->multiplay(baseNum, 3 * (1 + m_goldMulBox + ArtifactData::getInstance()->getrmGoldPer()));
		AchieveData::getInstance()->killRareMonster();
	}
	else if (MonsterState::getInstance()->getTypeNow() == MONSTER_TYPE::BOSS)
	{
		baseNum = Ruler::getInstance()->multiplay(baseNum, 5);
		AchieveData::getInstance()->killBoss();
	}
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
	
	return baseNum;
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
		AchieveData::getInstance()->addexploreNum();
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
		return m_skillData.at(i)->initEffect + m_skillData.at(i)->effPerLevel * (m_skillLevel[i] - 1);
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
	m_servantBaseDps[id] = getservantLevelUpDps(id);
	m_gold = Ruler::getInstance()->subNum(m_gold, m_upGold);
}
MyNum PlayerData::getservantToalDps(int id)
{
	auto servantDps = SqLite::getInstance()->getServantDpsByID(id);
	for (int i = 0; i < m_servantLevel[id]; i++)
	{
		auto pow1 = pow(i + 1, 0.7);
		auto pow2 = pow(i + 1, 6);
		auto mul = 1 + 1 / pow1 - 1 / pow2;
		servantDps = Ruler::getInstance()->multiplay(servantDps, mul);
	}
	return servantDps;
	
}
MyNum PlayerData::getservantLevelUpDps(int id)
{
	
	auto servantLsDps = SqLite::getInstance()->getServantDpsByID(id);
	for (int i = 0; i <= m_servantLevel[id]; i++)
	{
		auto pow1 = pow(i + 1, 0.7);
		auto pow2 = pow(i + 1, 6);
		auto mul = 1 + 1 / pow1 - 1 / pow2;
		servantLsDps = Ruler::getInstance()->multiplay(servantLsDps, mul);
	}
	auto upDps = Ruler::getInstance()->subNum(servantLsDps, getservantToalDps(id));
	return upDps;
}
MyNum PlayerData::getservantLevelUpGold(int id)
{
	auto m_upGold = SqLite::getInstance()->getServantGoldByID(id);

	for (int i = 1; i < m_servantLevel[id]; i++)
	{

		auto mul = 1 + 1 / (pow(i + 1, 0.45) - 1 / pow(i + 1, 6.13));
		m_upGold = Ruler::getInstance()->multiplay(m_upGold, mul);

	}
	m_upGold = Ruler::getInstance()->multiplay(m_upGold, (1 - ArtifactData::getInstance()->getSLUP()));
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
void PlayerData::saveUserData(float dt)
{
	Document document;
	document.SetObject();
	Document::AllocatorType& allocator = document.GetAllocator();
	Value array(kArrayType);
	Value object(kObjectType);
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

	for (int i = 0; i < m_latest.m_HpData.size(); i++)
	{
		auto str1 = cocos2d::StringUtils::format("lsthpNum%d", i);
		auto str2 = cocos2d::StringUtils::format("lsthpMat%d", i);
		document.AddMember(Value(str1.c_str(), allocator), m_latest.m_HpData.at(i).number, allocator);
		document.AddMember(Value(str2.c_str(), allocator), m_latest.m_HpData.at(i).Mathbit, allocator);
	}
	for (int i = 0; i < 6; i++)
	{
		document.AddMember(rapidjson::Value(cocos2d::StringUtils::format("skilllevel%d", i).c_str(), allocator), m_skillLevel[i], allocator);
		
	}
	for (int i = 0; i < 33; i++)
	{
		if (!m_servantLevel[i])
			break;
		document.AddMember(Value(cocos2d::StringUtils::format("servantLevel%d", i).c_str(), allocator), m_servantLevel[i], allocator);
		document.AddMember(Value(cocos2d::StringUtils::format("servantBaseDpsMat%d", i).c_str(), allocator), m_servantBaseDps[i].Mathbit, allocator);
		document.AddMember(Value(cocos2d::StringUtils::format("servantMul%d", i).c_str(), allocator), m_servantMul[i], allocator);
		document.AddMember(Value(cocos2d::StringUtils::format("servantBaseDpsNum%d", i).c_str(), allocator), m_servantBaseDps[i].number, allocator);

		
	}
	ArtifactData::getInstance()->saveUserDefault(document);
	AchieveData::getInstance()->saveUserDefault(document);
	StringBuffer buffer;
	rapidjson::Writer<StringBuffer> writer(buffer);
	document.Accept(writer);
	auto json = buffer.GetString();
	
	cocos2d::UserDefault::getInstance()->setStringForKey("UserDefault", buffer.GetString());

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
	
}

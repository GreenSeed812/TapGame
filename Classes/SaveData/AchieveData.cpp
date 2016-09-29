#include "AchieveData.h"
#include "MissionData.h"
#include "cocos2d.h"
#include "Tool/Rule.h"
static AchieveData * g_Ac = nullptr;
AchieveData::AchieveData()
	:m_monsterKill(0)
	,m_maxLevel(0)
	,m_ArStoneCollect(0)
	,m_ArMax(0)
	,m_bossKill(0)
	,m_tapNum(0)
	,m_relifeNum(0)
	,m_maxPlayerLevelUp(0)
	,m_killraremonster(0)
	, m_skill1used(0)
	, m_skill2used(0)
	, m_skill3used(0)
	, m_skill4used(0)
	, m_skill5used(0)
	, m_skill6used(0)
	, exploreNum(0)
	, m_totalrewords(0)
{
	for (size_t i = 0; i < 23; i++)
	{
		starNum[i] = 0;
	}		
	m_coinCollect.number = 0;
	m_maxDpsPer.Mathbit = 0;
}

AchieveData::~AchieveData()
{
}


AchieveData* AchieveData::getInstance()
{
	if (!g_Ac)
	{
		g_Ac = new AchieveData();
	}
	return g_Ac;
}

void AchieveData::saveUserDefault(Document& document)
{
	Document::AllocatorType& allocator = document.GetAllocator();
	document.AddMember("m_monsterKill", m_monsterKill, allocator);
	document.AddMember("m_maxLevel", m_maxLevel, allocator);
	document.AddMember("m_ArStoneCollect", m_ArStoneCollect, allocator);
	document.AddMember("m_ArMax", m_ArMax, allocator);
	document.AddMember("m_bossKill", m_bossKill, allocator);
	document.AddMember("m_tapNum", m_tapNum, allocator);
	document.AddMember("m_relifeNum", m_relifeNum, allocator);
	document.AddMember("m_maxPlayerLevelUp", m_maxPlayerLevelUp, allocator);
	document.AddMember("m_killraremonster", m_killraremonster, allocator);
	document.AddMember("m_skill1used", m_skill1used, allocator);
	document.AddMember("m_skill2used", m_skill2used, allocator);
	document.AddMember("m_skill3used", m_skill3used, allocator);
	document.AddMember("m_skill4used", m_skill4used, allocator);
	document.AddMember("m_skill5used", m_skill5used, allocator);
	document.AddMember("m_skill6used", m_skill6used, allocator);
	document.AddMember("exploreNum", exploreNum, allocator);
	document.AddMember("m_coinCollect.number",m_coinCollect.number, allocator);
	document.AddMember("m_coinCollect.Mathbit", m_coinCollect.Mathbit, allocator);
	document.AddMember("m_maxDpsPer.number", m_maxDpsPer.number, allocator);
	document.AddMember("m_maxDpsPer.Mathbit", m_maxDpsPer.Mathbit, allocator);
	document.AddMember("starNum[0]", starNum[0], allocator);
	document.AddMember("starNum[1]", starNum[1], allocator);
	document.AddMember("starNum[2]", starNum[2], allocator);
	document.AddMember("starNum[3]", starNum[3], allocator);
	document.AddMember("starNum[4]", starNum[4], allocator);
	document.AddMember("starNum[5]", starNum[5], allocator);
	document.AddMember("starNum[6]", starNum[6], allocator);
	document.AddMember("starNum[7]", starNum[7], allocator);
	document.AddMember("starNum[8]", starNum[8], allocator);
	document.AddMember("starNum[9]", starNum[9], allocator);
	document.AddMember("starNum[10]", starNum[10], allocator);
	document.AddMember("starNum[11]", starNum[11], allocator);
	document.AddMember("starNum[12]", starNum[12], allocator);
	document.AddMember("starNum[13]", starNum[13], allocator);
	document.AddMember("starNum[14]", starNum[14], allocator);
	document.AddMember("starNum[15]", starNum[15], allocator);
	document.AddMember("starNum[16]", starNum[16], allocator);
	document.AddMember("starNum[17]", starNum[17], allocator);
	document.AddMember("starNum[18]", starNum[18], allocator);
	document.AddMember("starNum[19]", starNum[19], allocator);
	document.AddMember("starNum[20]", starNum[20], allocator);
	document.AddMember("starNum[21]", starNum[21], allocator);
	document.AddMember("starNum[22]", starNum[22], allocator);
	document.AddMember("m_totalrewords", m_totalrewords, allocator);
}
void AchieveData::readUserDefault()
{
	std::string json = cocos2d::UserDefault::getInstance()->getStringForKey("UserDefault");
	rapidjson::Document jsd;
	jsd.Parse<0>(json.c_str());
	if (jsd.IsObject() && jsd.HasMember("m_monsterKill"))
	{
		m_monsterKill = jsd["m_monsterKill"].GetInt();
		m_maxLevel = jsd["m_maxLevel"].GetInt();
		m_ArStoneCollect = jsd["m_ArStoneCollect"].GetInt();
		m_ArMax = jsd["m_ArMax"].GetInt();
		m_bossKill = jsd["m_bossKill"].GetInt();
		m_tapNum = jsd["m_tapNum"].GetInt();
		m_relifeNum = jsd["m_relifeNum"].GetInt();
		m_maxPlayerLevelUp = jsd["m_maxPlayerLevelUp"].GetInt();
		m_killraremonster = jsd["m_killraremonster"].GetInt();
		m_skill1used = jsd["m_skill1used"].GetInt();
		m_skill2used = jsd["m_skill2used"].GetInt();
		m_skill3used = jsd["m_skill3used"].GetInt();
		m_skill4used = jsd["m_skill4used"].GetInt();
		m_skill5used = jsd["m_skill5used"].GetInt();
		m_skill6used = jsd["m_skill6used"].GetInt();
		exploreNum = jsd["exploreNum"].GetInt();
		m_coinCollect.number = jsd["m_coinCollect.number"].GetDouble();
		m_coinCollect.Mathbit = jsd["m_coinCollect.Mathbit"].GetInt();
		m_maxDpsPer.number = jsd["m_maxDpsPer.number"].GetDouble();
		m_maxDpsPer.Mathbit = jsd["m_maxDpsPer.Mathbit"].GetInt();
		starNum[0] = jsd["starNum[0]"].GetInt();
		starNum[1] = jsd["starNum[1]"].GetInt();
		starNum[2] = jsd["starNum[2]"].GetInt();
		starNum[3] = jsd["starNum[3]"].GetInt();
		starNum[4] = jsd["starNum[4]"].GetInt();
		starNum[5] = jsd["starNum[5]"].GetInt();
		starNum[6] = jsd["starNum[6]"].GetInt();
		starNum[7] = jsd["starNum[7]"].GetInt();
		starNum[8] = jsd["starNum[8]"].GetInt();
		starNum[9] = jsd["starNum[9]"].GetInt();
		starNum[10] = jsd["starNum[10]"].GetInt();
		starNum[11] = jsd["starNum[11]"].GetInt();
		starNum[12] = jsd["starNum[12]"].GetInt();
		starNum[13] = jsd["starNum[13]"].GetInt();
		starNum[14] = jsd["starNum[14]"].GetInt();
		starNum[15] = jsd["starNum[15]"].GetInt();
		starNum[16] = jsd["starNum[16]"].GetInt();
		starNum[17] = jsd["starNum[17]"].GetInt();
		starNum[18] = jsd["starNum[18]"].GetInt();
		starNum[19] = jsd["starNum[19]"].GetInt();
		starNum[20] = jsd["starNum[20]"].GetInt();
		starNum[21] = jsd["starNum[21]"].GetInt();
		starNum[22] = jsd["starNum[22]"].GetInt();
		m_totalrewords = jsd["m_totalrewords"].GetInt();
	}
}

void AchieveData::addCoin(MyNum add)
{
	m_coinCollect = Ruler::getInstance()->addNum(m_coinCollect, add);
}
void AchieveData::skillUsed(int i)
{
	if (i == 0)
	{
		m_skill1used++;
	}
	else if (i == 1)
	{
		m_skill2used++;
	}
	else if (i == 2)
	{
		m_skill3used++;
	}
	else if (i == 3)
	{
		m_skill4used++;
	}
	else if (i == 4)
	{
		m_skill5used++;
	}
	else if (i == 5)
	{
		m_skill6used++;
	}

}

int AchieveData::getNumByID(int id)
{
	switch (id)
	{
	case 1:
		return m_monsterKill;
	case 3:
		return m_maxLevel;
	case 4:
		return m_ArStoneCollect;
	case 5:
		return m_ArMax;
	case 7:
		return m_bossKill;
	case 8:
		return m_tapNum;
	case 9:
		return m_relifeNum;
	case 10:
		return m_maxPlayerLevelUp;
	case 11:
		return m_killraremonster;
	case 12:
		return m_skill1used;
	case 13:
		return m_skill2used;
	case 14:
		return m_skill3used;
	case 15:
		return m_skill4used;
	case 16:
		return m_skill5used;
	case 17:
		return m_skill6used;
	case 18:
		return exploreNum;
	}
}

MyNum AchieveData::getMyNumByID(int id)
{
	switch (id)
	{
	case 2:
		return m_coinCollect;
	case 6:
		return m_maxDpsPer;
	}
}
void AchieveData::tap()
{
	m_tapNum++;
	MissionData::getInstance()->addMissionTimesById(4);
}
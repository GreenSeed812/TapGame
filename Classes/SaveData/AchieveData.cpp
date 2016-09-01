#include "AchieveData.h"
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
{
	
		
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

}
void AchieveData::readUserDefault()
{
	std::string json = cocos2d::UserDefault::getInstance()->getStringForKey("UserDefault");
	rapidjson::Document jsd;
	jsd.Parse<0>(json.c_str());
	if (jsd.IsObject() && jsd.HasMember("m_monsterKill"))
	{
		m_monsterKill = jsd[m_monsterKill].GetInt();
		m_maxLevel = jsd[m_maxLevel].GetInt();
		m_ArStoneCollect = jsd[m_ArStoneCollect].GetInt();
		m_ArMax = jsd[m_ArMax].GetInt();
		m_bossKill = jsd[m_bossKill].GetInt();
		m_tapNum = jsd[m_tapNum].GetInt();
		m_relifeNum = jsd[m_relifeNum].GetInt();
		m_maxPlayerLevelUp = jsd[m_maxPlayerLevelUp].GetInt();
		m_killraremonster = jsd[m_killraremonster].GetInt();
		m_skill1used = jsd[m_skill1used].GetInt();
		m_skill2used = jsd[m_skill2used].GetInt();
		m_skill3used = jsd[m_skill3used].GetInt();
		m_skill4used = jsd[m_skill4used].GetInt();
		m_skill5used = jsd[m_skill5used].GetInt();
		m_skill6used = jsd[m_skill6used].GetInt();
		exploreNum = jsd[exploreNum].GetInt();
		m_coinCollect.number = jsd[m_coinCollect.number].GetDouble();
		m_coinCollect.Mathbit = jsd[m_coinCollect.Mathbit].GetInt();
		m_maxDpsPer.number = jsd[m_maxDpsPer.number].GetDouble();
		m_maxDpsPer.Mathbit = jsd[m_maxDpsPer.Mathbit].GetInt();
	}
}

void AchieveData::addCoin(MyNum add)
{
	Ruler::getInstance()->addNum(m_coinCollect, add);
}
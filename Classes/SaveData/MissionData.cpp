#include"MissionData.h"
#include "cocos2d.h"
USING_NS_CC;
static MissionData* g_md;
MissionData::MissionData()
{
	reset();
}

MissionData::~MissionData()
{
}

MissionData* MissionData::getInstance()
{
	if (!g_md)
	{
		g_md = new MissionData();
	}
	return g_md;
}
void MissionData::reset()
{
	for (int i = 0; i < 9; i++)
	{
		m_missionTimes[i] = 0;
	}
}
void MissionData::addMissionTimesById(int id)
{
	m_missionTimes[id]++;
}

void MissionData::saveUserDefault(Document& document)
{
	Document::AllocatorType& allocator = document.GetAllocator();
	document.AddMember("m_missionTimes[0]", m_missionTimes[0], allocator);
	document.AddMember("m_missionTimes[1]", m_missionTimes[1], allocator);
	document.AddMember("m_missionTimes[2]", m_missionTimes[2], allocator);
	document.AddMember("m_missionTimes[3]", m_missionTimes[3], allocator);
	document.AddMember("m_missionTimes[4]", m_missionTimes[4], allocator);
	document.AddMember("m_missionTimes[5]", m_missionTimes[5], allocator);
	document.AddMember("m_missionTimes[6]", m_missionTimes[6], allocator);
	document.AddMember("m_missionTimes[7]", m_missionTimes[7], allocator);
	document.AddMember("m_missionTimes[8]", m_missionTimes[8], allocator);
}

void MissionData::readUserDefault()
{
	std::string json = cocos2d::UserDefault::getInstance()->getStringForKey("UserDefault");
	rapidjson::Document jsd;
	jsd.Parse<0>(json.c_str());
	m_missionTimes[0] = jsd["m_missionTimes[0]"].GetInt();
	m_missionTimes[1] = jsd["m_missionTimes[1]"].GetInt();
	m_missionTimes[2] = jsd["m_missionTimes[2]"].GetInt();
	m_missionTimes[3] = jsd["m_missionTimes[3]"].GetInt();
	m_missionTimes[4] = jsd["m_missionTimes[4]"].GetInt();
	m_missionTimes[5] = jsd["m_missionTimes[5]"].GetInt();
	m_missionTimes[6] = jsd["m_missionTimes[6]"].GetInt();
	m_missionTimes[7] = jsd["m_missionTimes[7]"].GetInt();
	m_missionTimes[8] = jsd["m_missionTimes[8]"].GetInt();
}
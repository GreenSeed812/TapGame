#include"MissionData.h"
static MissionData* g_md;
MissionData::MissionData()
{
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
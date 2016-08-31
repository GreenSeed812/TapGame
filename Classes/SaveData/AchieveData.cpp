#include "AchieveData.h"
static AchieveData * g_Ac = nullptr;
AchieveData::AchieveData()
{
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
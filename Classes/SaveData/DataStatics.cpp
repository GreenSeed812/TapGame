#include "DataStatics.h"
#include "ArtifactData.h"
#include "PlayerData.h"
#include "ShopData.h"
#include <cocos2d.h>
using namespace cocos2d;
static DataStatics* g_data;
DataStatics::DataStatics()
	:m_playerTotalLevel(0)
	, m_servantMaxNum(0)
	, m_exploreNum(0)
{
}

DataStatics::~DataStatics()
{
}
DataStatics* DataStatics::getInstance()
{
	if (!g_data)
	{
		g_data = new DataStatics();
	}
	return g_data;
}
std::string DataStatics::getCurrent(int id)
{
	if (id == 3)
	{
		return StringUtils::format("%f%", (PlayerData::getInstance()->getgoldMul() + ArtifactData::getInstance()->getrmGoldPer()) * 100);
	}
	if (id == 4)
	{		
		return StringUtils::format("%f%", (PlayerData::getInstance()->getexploreProb() + ArtifactData::getInstance()->getexploreProb()) * 100);
	}
	if (id == 5)
	{
		if (ShopData::getInstance()->getItemBeUsedById(1))
		{
			return StringUtils::format("%f%",(PlayerData::getInstance()->getexplorePer() + SqLite::getInstance()->getItemByID(1)->eff + ArtifactData::getInstance()->getexplorePer())*100);
		}
		else
		{
			return StringUtils::format("%f%", (PlayerData::getInstance()->getexplorePer() + ArtifactData::getInstance()->getexplorePer()) * 100);
		}
	}
	if (id == 6)
	{

	}
}
std::string DataStatics::getStatic(int id)
{
	if (id == 1)
	{
		return StringUtils::format("%d", m_playerTotalLevel);
	}
	if (id == 2)
	{
		return Ruler::getInstance()->showNum(AchieveData::getInstance()->getCoinCollect());
	}
	if (id == 3)
	{
		return StringUtils::format("%d", AchieveData::getInstance()->getTapNum());
	}
	if (id == 4)
	{
		return StringUtils::format("%d", AchieveData::getInstance()->getMonsterKill());
	}
	if (id == 5)
	{
		return StringUtils::format("%d", AchieveData::getInstance()->getRareKill());
	}
	if (id == 6)
	{
		return StringUtils::format("%d", AchieveData::getInstance()->getBossKill());
	}
	if (id == 7)
	{
		return StringUtils::format("%d", m_exploreNum);
	}
	if (id == 8)
	{
		return StringUtils::format("%d", AchieveData::getInstance()->getMaxxLevel());
	}
	if (id == 9)
	{
		return StringUtils::format("%d", AchieveData::getInstance()->getRelifeNum());
	}
	if (id == 10)
	{
		
	}
	if (id == 11)
	{
		return StringUtils::format("%d", m_servantMaxNum);
	}
}
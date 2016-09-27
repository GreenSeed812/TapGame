#include "DataStatics.h"
#include "ArtifactData.h"
#include "PlayerData.h"
#include "ShopData.h"
#include "Tool/TimeTool.h"
#include <cocos2d.h>
using namespace cocos2d;
static DataStatics* g_data;
DataStatics::DataStatics()
	:m_playerTotalLevel(0)
	, m_servantMaxNum(0)
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
		return StringUtils::format("%.1f%%", (PlayerData::getInstance()->getgoldMul() + ArtifactData::getInstance()->getrmGoldPer()) * 100);
	}
	if (id == 4)
	{		
		return StringUtils::format("%.1f%%", (PlayerData::getInstance()->getexploreProb() + ArtifactData::getInstance()->getexploreProb()));
	}
	if (id == 5)
	{
		if (ShopData::getInstance()->getItemBeUsedById(1))
		{
			return StringUtils::format("%.1f%%",(PlayerData::getInstance()->getexplorePer() + SqLite::getInstance()->getItemByID(1)->eff + ArtifactData::getInstance()->getexplorePer())*100);
		}
		else
		{
			return StringUtils::format("%.1f%%", (PlayerData::getInstance()->getexplorePer() + ArtifactData::getInstance()->getexplorePer()) * 100);
		}
	}
	if (id == 6)
	{
		auto timeNow = TimeTool::getInstance()->getTime();
		auto time = (float)(timeNow - m_lastRelife) / 86400;
		if (time < 1)
		{
			time = (float)(timeNow - m_lastRelife) / 3600;
			if (time < 24)
			{
				time = (float)(timeNow - m_lastRelife) / 60;
				if (time < 60)
				{
					auto _time = (int)time;
					return StringUtils::format("%ds", _time).c_str();
				}
				auto _time = (int)time;
				return StringUtils::format("%dm", _time).c_str();
			}
			auto _time = (int)time;
			return StringUtils::format("%dh", _time).c_str();
		}
		else
		{
			auto _time = (int)time;
			return StringUtils::format("%dd",_time).c_str();
		}
		return StringUtils::format("%ds", 0).c_str();
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
		return StringUtils::format("%d", AchieveData::getInstance()->getexploreNum());
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
		auto timeNow = TimeTool::getInstance()->getTime();
		auto day = ((float)(timeNow - m_initGameDay)) / 86400;
		if (day > 1)
		{
			auto _day = (int)day;
			return StringUtils::format("%dd", _day).c_str();
		}
		return StringUtils::format("%dd", 0).c_str();
	}
	if (id == 11)
	{
		return StringUtils::format("%d", m_servantMaxNum);
	}
}
void DataStatics::saveUserDefault(Document& document)
{
	Document::AllocatorType& allocator = document.GetAllocator();
	document.AddMember("m_playerTotalLevel",m_playerTotalLevel, allocator);
	document.AddMember("m_lastRelife", m_lastRelife, allocator);
	document.AddMember("m_initGameDay", m_initGameDay, allocator);
	document.AddMember("m_servantMaxNum", m_servantMaxNum, allocator);
}
void DataStatics::readUserDefault()
{
	std::string json = cocos2d::UserDefault::getInstance()->getStringForKey("UserDefault");
	rapidjson::Document jsd;
	jsd.Parse<0>(json.c_str());
	if (jsd.IsObject())
	{
		m_playerTotalLevel = jsd["m_playerTotalLevel"].GetInt();
		m_lastRelife = jsd["m_lastRelife"].GetInt();
		m_initGameDay = jsd["m_initGameDay"].GetInt();
		m_servantMaxNum = jsd["m_servantMaxNum"].GetInt();
	}
}
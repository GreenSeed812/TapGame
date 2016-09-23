
#include "SaveData/LeaveGold.h"

LeaveGold::LeaveGold()
{
	int time;
	if (cocos2d::UserDefault::getInstance()->getBoolForKey("isSaved"))
	{
		time = PlayerData::getInstance()->getLeaveTime();
	}
	else
	{
		time = 0;
	}
	if (time != 0)
	{
		auto timeNow = TimeTool::getInstance()->getTime();
		auto num = timeNow - time;
		auto dps = PlayerData::getInstance()->getHeroDps();
		auto gold = PlayerData::getInstance()->getdefeatMonsterGold();
		auto hp = Ruler::getInstance()->multiplay(PlayerData::getInstance()->getHpNow(), 2);
		if (num >= 72000)
		{
			m_golds = Ruler::getInstance()->multiplay(Ruler::getInstance()->multiplay(gold, 72000), hp);
			log("Max%d", num);
		}
		else
		{
			if (num > 300)
			{
				m_golds = Ruler::getInstance()->multiplay(Ruler::getInstance()->multiplay(gold, num), hp);
				log("Min%d", num);
			}
		}
	}
}

LeaveGold::~LeaveGold()
{

}

#include "SaveData/LeaveGold.h"

LeaveGold::LeaveGold()
{
	auto time = PlayerData::getInstance()->getLeaveTime();
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
		}
		else
		{
			m_golds = Ruler::getInstance()->multiplay(Ruler::getInstance()->multiplay(gold, num), hp);
		}
	}
}

LeaveGold::~LeaveGold()
{

}

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
		MyNum golds;
		if (num >= 72000)
		{
			Ruler::getInstance()->multiplay(gold, 72000);
			
		}
		else
		{
			Ruler::getInstance()->multiplay(gold, num);
		}
		PlayerData::getInstance()->addGold(&golds);
	}
	
}
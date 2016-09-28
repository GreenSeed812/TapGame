
#include "SaveData/LeaveGold.h"
#include "SaveData/ShopData.h"

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
		MyNum dou;
		if (ShopData::getInstance()->getItemDataById(11)->leftTime > 0)
		{
			dou = Ruler::getInstance()->multiplay(Ruler::getInstance()->multiplay(gold, ShopData::getInstance()->getItemDataById(11)->leftTime), hp);
		}
		if (num >= 72000)
		{
			m_golds = Ruler::getInstance()->multiplay(Ruler::getInstance()->multiplay(gold, 72000), hp);
		}
		else
		{
			if (num > 300)
			{
				m_golds = Ruler::getInstance()->multiplay(Ruler::getInstance()->multiplay(gold, num), hp);
			}
		}
		m_golds = Ruler::getInstance()->addNum(m_golds,dou);
	}
}

LeaveGold::~LeaveGold()
{

}
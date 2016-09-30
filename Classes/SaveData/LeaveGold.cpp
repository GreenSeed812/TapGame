
#include "SaveData/LeaveGold.h"
#include "SaveData/ShopData.h"

LeaveGold::LeaveGold()
{
	calculate();
}

LeaveGold::~LeaveGold()
{

}

void LeaveGold::calculate()
{
	m_golds.number = 0;
	m_golds.Mathbit = 0;
	int time = 0;
	if (cocos2d::UserDefault::getInstance()->getBoolForKey("isSaved"))
	{
		time = PlayerData::getInstance()->getLeaveTime();
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
			m_golds = Ruler::getInstance()->multiplay(gold, 72000);
			m_golds = Ruler::getInstance()->multiplay(m_golds, dps);
			m_golds = Ruler::getInstance()->devide(m_golds, hp);
		}
		else
		{
			if (num > 300)
			{
				m_golds = Ruler::getInstance()->multiplay(gold, num);
				m_golds = Ruler::getInstance()->multiplay(m_golds, dps);
				m_golds = Ruler::getInstance()->devide(m_golds, hp);
			}
			else
			{
				m_golds.number = 0;
				m_golds.Mathbit = 0;
			}
		}
		//¼ÆËã¼Ó³É
		MyNum addition;
		addition.number = 0;
		addition.Mathbit = 0;
		auto time= ShopData::getInstance()->getItemDataById(11)->leftTime;
		if (time > 0)
		{
			if (num > 43200)
			{
				time = 0;
			}
			else
			{
				time -= num;
			}
			ShopData::getInstance()->getItemDataById(11)->leftTime = time;
			addition = Ruler::getInstance()->multiplay(Ruler::getInstance()->multiplay(gold, time), hp);
		}
		m_golds = Ruler::getInstance()->addNum(m_golds, addition);
	}
}
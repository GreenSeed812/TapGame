
#include "Ui/Statistics.h"
#include "ui/CocosGUI.h"
#include <cocostudio/CocoStudio.h> 
#include "SaveData/PlayerData.h"
#include "SaveData/ArtifactData.h"
#include "Tool/SqLite.h"
#include "Tool/Rule.h"
using namespace ui;

bool Statistics::init()
{
	if (!Layer::init())
	{
		return false;
	}

	m_rootNode = CSLoader::createNode("shujutongji.csb");
	this->setContentSize(m_rootNode->getContentSize());
	this->addChild(m_rootNode);

	return true;
}

void Statistics::initStatistics()
{
	CCNotificationCenter::getInstance()->addObserver(this, callfuncO_selector(Statistics::statisticsChange), "StatisticsChange", nullptr);

	auto escBtn = (Button*)m_rootNode->getChildByName("esc");

	escBtn->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type){
		if (type == Widget::TouchEventType::ENDED)
		{
			m_rootNode->removeFromParent();
		}
	});
	statisticsChange(this);
}

void Statistics::statisticsChange(Ref* ref)
{
	auto playerLv = (TextBMFont*)m_rootNode->getChildByName("playerLv");
	auto servantLv = (TextBMFont*)m_rootNode->getChildByName("ServantLv");
	auto gold = (TextBMFont*)m_rootNode->getChildByName("gold");
	auto crit = (TextBMFont*)m_rootNode->getChildByName("Crit");
	auto critHurt = (TextBMFont*)m_rootNode->getChildByName("critHurt");
	auto relifeTime = (TextBMFont*)m_rootNode->getChildByName("relifeTime");
	auto playerLvZ = (TextBMFont*)m_rootNode->getChildByName("playerLvZ");
	auto goldZ = (TextBMFont*)m_rootNode->getChildByName("goldZ");
	auto clickNum = (TextBMFont*)m_rootNode->getChildByName("clickNum");
	auto monsterNum = (TextBMFont*)m_rootNode->getChildByName("monsterNum");
	auto monsterRareNum = (TextBMFont*)m_rootNode->getChildByName("monsterRareNum");
	auto boosNum = (TextBMFont*)m_rootNode->getChildByName("boosNum");
	auto critNum = (TextBMFont*)m_rootNode->getChildByName("critNum");
	auto maxLv = (TextBMFont*)m_rootNode->getChildByName("maxLv");
	auto relifeNum = (TextBMFont*)m_rootNode->getChildByName("relifeNum");
	auto playDays = (TextBMFont*)m_rootNode->getChildByName("playDays");
	auto maxSerNum = (TextBMFont*)m_rootNode->getChildByName("maxSerNum");

	playerLv->setString(StringUtils::format("%d", PlayerData::getInstance()->getPlayerLevel()).c_str());
	servantLv->setString(StringUtils::format("%d", PlayerData::getInstance()->getServantAverLevel()).c_str());
	gold->setString(StringUtils::format("%d%%", ArtifactData::getInstance()->getrmGoldPer() * 100).c_str());
	crit->setString(StringUtils::format("%d", 0).c_str());
	critHurt->setString(StringUtils::format("%d", 0).c_str());
	relifeTime->setString(StringUtils::format("%d", 0).c_str());
	playerLvZ->setString(StringUtils::format("%d", 0).c_str());
	goldZ->setString(StringUtils::format("%d", 0).c_str());
	clickNum->setString(StringUtils::format("%d", 0).c_str());
	monsterNum->setString(StringUtils::format("%d", 0).c_str());
	monsterRareNum->setString(StringUtils::format("%d", 0).c_str());
	boosNum->setString(StringUtils::format("%d", 0).c_str());
	critNum->setString(StringUtils::format("%d", 0).c_str());
	maxLv->setString(StringUtils::format("%d", 0).c_str());
	relifeNum->setString(StringUtils::format("%d", 0).c_str());
	playDays->setString(StringUtils::format("%d", 0).c_str());
	maxSerNum->setString(StringUtils::format("%d", 0).c_str());
}
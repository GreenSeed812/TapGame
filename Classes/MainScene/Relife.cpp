
#include "Relife.h"
#include "ui/CocosGUI.h"
#include <cocostudio/CocoStudio.h> 
#include "SaveData/PlayerData.h"
#include "SaveData/ArtifactData.h"
#include "SaveData/ShopData.h"
#include "Tool/SqLite.h"
using namespace ui;

bool Relife::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	m_node = CSLoader::createNode("zhuansheng.csb");
	m_layer = (Layer*)m_node->getChildByName("layerBg");
	this->setContentSize(m_node->getContentSize());
	this->addChild(m_node);
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [](Touch*, Event*)->bool{return true; };
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, m_layer);

	return true;
}

void Relife::initRelife()
{
	auto escBtn = (Button*)m_layer->getChildByName("esc");
	auto submitBtn = (Button*)m_layer->getChildByName("submit");
	auto head = (ImageView*)m_layer->getChildByName("head");
	auto playerLv = (TextBMFont*)m_layer->getChildByName("infoBg")->getChildByName("plLv");
	auto playerStone = (TextBMFont*)m_layer->getChildByName("infoBg")->getChildByName("playerStone");
	auto servantLv = (TextBMFont*)m_layer->getChildByName("infoBg")->getChildByName("serLv");
	auto serStone = (TextBMFont*)m_layer->getChildByName("infoBg")->getChildByName("serStone");
	auto count = (TextBMFont*)m_layer->getChildByName("infoBg")->getChildByName("count");
	auto countStone = (TextBMFont*)m_layer->getChildByName("infoBg")->getChildByName("countStone");
	auto allLv = (TextBMFont*)m_layer->getChildByName("infoBg")->getChildByName("allLv");
	auto allStone = (TextBMFont*)m_layer->getChildByName("infoBg")->getChildByName("allStone");

	playerLv->setString(StringUtils::format(":%d", PlayerData::getInstance()->getPlayerLevel()).c_str());
	playerStone->setString(StringUtils::format("X%d",PlayerData::getInstance()->getHeroRelifeStone()).c_str());
	servantLv->setString(StringUtils::format(":%d", PlayerData::getInstance()->getServantAverLevel()).c_str());
	serStone->setString(StringUtils::format("X%d", PlayerData::getInstance()->getServantRelifeStone()).c_str());
	count->setString(StringUtils::format(":%d", PlayerData::getInstance()->getLevel()).c_str());
	countStone->setString(StringUtils::format("X%d", PlayerData::getInstance()->getLevelRelifeStone()).c_str());
	allLv->setString(StringUtils::format(":").c_str());
	allStone->setString(StringUtils::format("X%d", PlayerData::getInstance()->getRelifeStone()).c_str());

	escBtn->addTouchEventListener([this](Ref* Sender, Widget::TouchEventType Event)
	{
		if (Event == Widget::TouchEventType::ENDED)
		{
			m_node->removeFromParent();
		}
	});

	submitBtn->addTouchEventListener([this](Ref* Sender, Widget::TouchEventType Event)
	{
		if (Event == Widget::TouchEventType::ENDED)
		{

			CCNotificationCenter::destroyInstance();
			AchieveData::getInstance()->relife();
			PlayerData::getInstance()->relife();
		}
	});
}
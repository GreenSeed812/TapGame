
#include "PlayerInfo.h"
#include "ui/CocosGUI.h"
#include <cocostudio/CocoStudio.h> 
#include "SaveData/PlayerData.h"
#include "SaveData/ArtifactData.h"
#include "SaveData/ShopData.h"
#include "Tool/SqLite.h"
using namespace ui;

bool PlayerInfo::init()
{
	if (!Layer::init())
	{
		return false;
	}

	m_node = CSLoader::createNode("zhujiaojieshao.csb");
	m_layer = (Layer*)m_node->getChildByName("LayerBg");
	this->setContentSize(m_node->getContentSize());
	this->addChild(m_node);
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [](Touch*, Event*)->bool{return true; };
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, m_layer);

	return true;
}

void PlayerInfo::initPlayerInfo()
{
	auto escBtn = (Button*)m_layer->getChildByName("esc");
	auto name = (Text*)m_layer->getChildByName("infoBg")->getChildByName("name");
	auto level = (TextBMFont*)m_layer->getChildByName("infoBg")->getChildByName("lv");
	auto dps = (TextBMFont*)m_layer->getChildByName("infoBg")->getChildByName("dps");

	for (size_t i = 0; i < 7; i++)
	{
		auto skillName = (Text*)m_layer->getChildByName("skillBg")->getChildByName(StringUtils::format("skill%d", i + 1).c_str())->getChildByName(StringUtils::format("skillName_%d", i + 1).c_str());
		auto skillInfo = (Text*)m_layer->getChildByName("skillBg")->getChildByName(StringUtils::format("skill%d", i + 1).c_str())->getChildByName(StringUtils::format("skillInfo_%d", i + 1).c_str());
		auto eff = SqLite::getInstance()->getEff(i) + SqLite::getInstance()->getEffPer(i) * PlayerData::getInstance()->getSkillLevel(i);
		skillName->setString(StringUtils::format("%s", SqLite::getInstance()->getSkillNameByID(i).c_str()));
		skillInfo->setString(StringUtils::format(SqLite::getInstance()->getSkillDis(i).c_str(), eff));

	}

	name->setString(PlayerData::getInstance()->getName());
	level->setString(StringUtils::format("Lv%d", PlayerData::getInstance()->getPlayerLevel()));
	dps->setString(Ruler::getInstance()->showNum(PlayerData::getInstance()->getTapDpsNoExp()));

	escBtn->addTouchEventListener([this](Ref* Sender, Widget::TouchEventType Event)
	{
		if (Event == Widget::TouchEventType::ENDED)
		{
			m_node->removeFromParent();
		}
	});

	//for (size_t i = 0; i < 7; i++)
	//{
	//	auto lv = (ImageView*)m_node->getChildByName(StringUtils::format("lv%d", i + 1).c_str());
	//	auto lvNum = (ImageView*)m_node->getChildByName(StringUtils::format("lvNum%d", i + 1).c_str());
	//	auto headBg = (ImageView*)m_node->getChildByName(StringUtils::format("headBg%d", i + 1).c_str());
	//	auto head = (ImageView*)m_layer->getChildByName("skillBg")->getChildByName(StringUtils::format("head%d", i + 1).c_str());
	//	if (PlayerData::getInstance()->getSkillLevel(i) >= 1)
	//	{	
	//		lv->setVisible(false);
	//		lvNum->setVisible(false);
	//		headBg->setVisible(false);
	//		head->setVisible(true);
	//	}
	//	else
	//	{
	//		lv->setVisible(true);
	//		lvNum->setVisible(true);
	//		headBg->setVisible(true);
	//		head->setVisible(false);
	//	}
	//}
}


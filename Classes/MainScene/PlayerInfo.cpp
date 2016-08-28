
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

	//获取控件
	auto escBtn = (Button*)m_layer->getChildByName("esc");
	auto name = (Text*)m_layer->getChildByName("infoBg")->getChildByName("name");
	auto level = (TextBMFont*)m_layer->getChildByName("infoBg")->getChildByName("lv");
	auto dps = (TextBMFont*)m_layer->getChildByName("infoBg")->getChildByName("dps");
	//技能名称
	auto skillName_1 = (Text*)m_layer->getChildByName("skillBg")->getChildByName("skill1")->getChildByName("skillName_1");
	auto skillName_2 = (Text*)m_layer->getChildByName("skillBg")->getChildByName("skill2")->getChildByName("skillName_2");
	auto skillName_3 = (Text*)m_layer->getChildByName("skillBg")->getChildByName("skill3")->getChildByName("skillName_3");
	auto skillName_4 = (Text*)m_layer->getChildByName("skillBg")->getChildByName("skill4")->getChildByName("skillName_4");
	auto skillName_5 = (Text*)m_layer->getChildByName("skillBg")->getChildByName("skill5")->getChildByName("skillName_5");
	auto skillName_6 = (Text*)m_layer->getChildByName("skillBg")->getChildByName("skill6")->getChildByName("skillName_6");
	auto skillName_7 = (Text*)m_layer->getChildByName("skillBg")->getChildByName("skill7")->getChildByName("skillName_7");
	//技能效果
	auto skillInfo_1 = (Text*)m_layer->getChildByName("skillBg")->getChildByName("skill1")->getChildByName("skillInfo_1");
	auto skillInfo_2 = (Text*)m_layer->getChildByName("skillBg")->getChildByName("skill2")->getChildByName("skillInfo_2");
	auto skillInfo_3 = (Text*)m_layer->getChildByName("skillBg")->getChildByName("skill3")->getChildByName("skillInfo_3");
	auto skillInfo_4 = (Text*)m_layer->getChildByName("skillBg")->getChildByName("skill4")->getChildByName("skillInfo_4");
	auto skillInfo_5 = (Text*)m_layer->getChildByName("skillBg")->getChildByName("skill5")->getChildByName("skillInfo_5");
	auto skillInfo_6 = (Text*)m_layer->getChildByName("skillBg")->getChildByName("skill6")->getChildByName("skillInfo_6");	
	auto skillInfo_7 = (Text*)m_layer->getChildByName("skillBg")->getChildByName("skill7")->getChildByName("skillInfo_7");
	
	//设置控件显示信息
	name->setString(StringUtils::format("Player"));
	level->setString(StringUtils::format("Lv%d",PlayerData::getInstance()->getLevel()));
	dps->setString(Ruler::getInstance()->showNum(PlayerData::getInstance()->getTapDpsNoExp()));
	skillName_1->setString(StringUtils::format("%s", SqLite::getInstance()->getSkillNameByID(0).c_str()));
	skillName_2->setString(StringUtils::format("%s", SqLite::getInstance()->getSkillNameByID(1).c_str()));
	skillName_3->setString(StringUtils::format("%s", SqLite::getInstance()->getSkillNameByID(2).c_str()));
	skillName_4->setString(StringUtils::format("%s", SqLite::getInstance()->getSkillNameByID(3).c_str()));
	skillName_5->setString(StringUtils::format("%s", SqLite::getInstance()->getSkillNameByID(4).c_str()));
	skillName_6->setString(StringUtils::format("%s", SqLite::getInstance()->getSkillNameByID(5).c_str()));
	skillName_7->setString(StringUtils::format("%s", SqLite::getInstance()->getSkillNameByID(6).c_str()));
	auto eff1 = SqLite::getInstance()->getEff(0) + SqLite::getInstance()->getEffPer(0) * PlayerData::getInstance()->getSkillLevel(0);
	auto eff2 = SqLite::getInstance()->getEff(1) + SqLite::getInstance()->getEffPer(1) * PlayerData::getInstance()->getSkillLevel(1);
	auto eff3 = SqLite::getInstance()->getEff(2) + SqLite::getInstance()->getEffPer(2) * PlayerData::getInstance()->getSkillLevel(2);
	auto eff4 = SqLite::getInstance()->getEff(3) + SqLite::getInstance()->getEffPer(3) * PlayerData::getInstance()->getSkillLevel(3);
	auto eff5 = SqLite::getInstance()->getEff(4) + SqLite::getInstance()->getEffPer(4) * PlayerData::getInstance()->getSkillLevel(4);
	auto eff6 = SqLite::getInstance()->getEff(5) + SqLite::getInstance()->getEffPer(5) * PlayerData::getInstance()->getSkillLevel(5);
	auto eff7 = SqLite::getInstance()->getEff(6) + SqLite::getInstance()->getEffPer(6) * PlayerData::getInstance()->getSkillLevel(6);
	skillInfo_1->setString(StringUtils::format(SqLite::getInstance()->getSkillDis(0).c_str(),eff1));
	skillInfo_2->setString(StringUtils::format(SqLite::getInstance()->getSkillDis(1).c_str(),eff2));
	skillInfo_3->setString(StringUtils::format(SqLite::getInstance()->getSkillDis(2).c_str(),eff3));
	skillInfo_4->setString(StringUtils::format(SqLite::getInstance()->getSkillDis(3).c_str(),eff4));
	skillInfo_5->setString(StringUtils::format(SqLite::getInstance()->getSkillDis(4).c_str(),eff5));
	skillInfo_6->setString(StringUtils::format(SqLite::getInstance()->getSkillDis(5).c_str(),eff6));
	skillInfo_7->setString(StringUtils::format(SqLite::getInstance()->getSkillDis(6).c_str(),eff7));


	escBtn->addTouchEventListener([this](Ref* Sender, Widget::TouchEventType Event)
	{
		if (Event == Widget::TouchEventType::ENDED)
		{
			m_node->removeFromParent();
		}
	});
}

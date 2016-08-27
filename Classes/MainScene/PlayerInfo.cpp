
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
	name->setString(StringUtils::format(""));
	level->setString(StringUtils::format(""));
	dps->setString(StringUtils::format(""));
	skillName_1->setString("");
	skillName_2->setString("");
	skillName_3->setString("");
	skillName_4->setString("");
	skillName_5->setString("");
	skillName_6->setString("");
	skillName_7->setString("");
	skillInfo_1->setString("");
	skillInfo_2->setString("");
	skillInfo_3->setString("");
	skillInfo_4->setString("");
	skillInfo_5->setString("");
	skillInfo_6->setString("");
	skillInfo_7->setString("");


	escBtn->addTouchEventListener([this](Ref* Sender, Widget::TouchEventType Event)
	{
		if (Event == Widget::TouchEventType::ENDED)
		{
			m_node->removeFromParent();
		}
	});
}


#include "ServantInfo.h"
#include "ui/CocosGUI.h"
#include <cocostudio/CocoStudio.h> 
#include "SaveData/PlayerData.h"
#include "SaveData/ArtifactData.h"
#include "SaveData/ShopData.h"
#include "Tool/SqLite.h"
using namespace ui;

bool ServantInfo::init()
{
	if (!Layer::init())
	{
		return false;
	}
	m_node = CSLoader::createNode("yongbing.csb");
	m_layer = (Layer*)m_node->getChildByName("layerBg");
	this->setContentSize(m_node->getContentSize());
	this->addChild(m_node);
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [](Touch*, Event*)->bool{return true; };
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, m_layer);

	return true;
}

void ServantInfo::initServantInfo(int id)
{
	auto escBtn = (Button*)m_layer->getChildByName("esc");
	auto head = (ImageView*)m_layer->getChildByName("headBg")->getChildByName("head");
	auto name = (Text*)m_layer->getChildByName("serInfo")->getChildByName("name");
	auto level = (TextBMFont*)m_layer->getChildByName("serInfo")->getChildByName("lv");
	auto dps = (TextBMFont*)m_layer->getChildByName("serInfo")->getChildByName("dps");
	auto skillHead_1 = (ImageView*)m_layer->getChildByName("skillInfoBg")->getChildByName("skillHead_1");
	auto skillHead_2 = (ImageView*)m_layer->getChildByName("skillInfoBg")->getChildByName("skillHead_2");
	auto skillHead_3 = (ImageView*)m_layer->getChildByName("skillInfoBg")->getChildByName("skillHead_3");
	auto skillHead_4 = (ImageView*)m_layer->getChildByName("skillInfoBg")->getChildByName("skillHead_4");
	auto skillHead_5 = (ImageView*)m_layer->getChildByName("skillInfoBg")->getChildByName("skillHead_5");
	auto skillHead_6 = (ImageView*)m_layer->getChildByName("skillInfoBg")->getChildByName("skillHead_6");
	auto skillHead_7 = (ImageView*)m_layer->getChildByName("skillInfoBg")->getChildByName("skillHead_7");
	auto skillName_1 = (Text*)m_layer->getChildByName("skillInfoBg")->getChildByName("skillBg_1")->getChildByName("skillName_1");
	auto skillName_2 = (Text*)m_layer->getChildByName("skillInfoBg")->getChildByName("skillBg_2")->getChildByName("skillName_2");
	auto skillName_3 = (Text*)m_layer->getChildByName("skillInfoBg")->getChildByName("skillBg_3")->getChildByName("skillName_3");
	auto skillName_4 = (Text*)m_layer->getChildByName("skillInfoBg")->getChildByName("skillBg_4")->getChildByName("skillName_4");
	auto skillName_5 = (Text*)m_layer->getChildByName("skillInfoBg")->getChildByName("skillBg_5")->getChildByName("skillName_5");
	auto skillName_6 = (Text*)m_layer->getChildByName("skillInfoBg")->getChildByName("skillBg_6")->getChildByName("skillName_6");
	auto skillName_7 = (Text*)m_layer->getChildByName("skillInfoBg")->getChildByName("skillBg_7")->getChildByName("skillName_7");
	auto skillInfo_1 = (Text*)m_layer->getChildByName("skillInfoBg")->getChildByName("skillBg_1")->getChildByName("skillInfo_1");
	auto skillInfo_2 = (Text*)m_layer->getChildByName("skillInfoBg")->getChildByName("skillBg_2")->getChildByName("skillInfo_2");
	auto skillInfo_3 = (Text*)m_layer->getChildByName("skillInfoBg")->getChildByName("skillBg_3")->getChildByName("skillInfo_3");
	auto skillInfo_4 = (Text*)m_layer->getChildByName("skillInfoBg")->getChildByName("skillBg_4")->getChildByName("skillInfo_4");
	auto skillInfo_5 = (Text*)m_layer->getChildByName("skillInfoBg")->getChildByName("skillBg_5")->getChildByName("skillInfo_5");
	auto skillInfo_6 = (Text*)m_layer->getChildByName("skillInfoBg")->getChildByName("skillBg_6")->getChildByName("skillInfo_6");
	auto skillInfo_7 = (Text*)m_layer->getChildByName("skillInfoBg")->getChildByName("skillBg_7")->getChildByName("skillInfo_7");
	
	escBtn->addTouchEventListener([this](Ref* Sender, Widget::TouchEventType Event)
	{
		if (Event == Widget::TouchEventType::ENDED)
		{
			m_node->removeFromParent();
		}
	});
}

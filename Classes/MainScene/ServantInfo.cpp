
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
	m_bgLayer = LayerColor::create(Color4B(50,50,50,155));
	this->addChild(m_bgLayer);
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
	auto head = (Sprite*)m_layer->getChildByName("headBg")->getChildByName("head");
	auto name = (Text*)m_layer->getChildByName("serInfo")->getChildByName("name");
	auto level = (TextBMFont*)m_layer->getChildByName("serInfo")->getChildByName("lv");
	auto dps = (TextBMFont*)m_layer->getChildByName("serInfo")->getChildByName("dps");
	auto serInfo = (Text*)m_layer->getChildByName("infoText");
	
	for (size_t i = 0; i < 7; i++)
	{	
		auto skillName = (Text*)m_layer->getChildByName("skillInfoBg")->getChildByName(StringUtils::format("skillBg_%d", i + 1).c_str())->getChildByName(StringUtils::format("skillName_%d", i + 1).c_str());
		auto skillInfo = (Text*)m_layer->getChildByName("skillInfoBg")->getChildByName(StringUtils::format("skillBg_%d", i + 1).c_str())->getChildByName(StringUtils::format("skillInfo_%d", i + 1).c_str());
		skillName->setString(SqLite::getInstance()->getServantByID(id)->skill[i].skillname);
		skillInfo->setString(SqLite::getInstance()->getSkillEffDis(SqLite::getInstance()->getServantByID(id)->skill[i].skillID));
		for (size_t j = 0; j < PlayerData::getInstance()->getServantSkillNum(id); j++)
		{
			auto skillHead = (ImageView*)m_layer->getChildByName("skillInfoBg")->getChildByName(StringUtils::format("skillHead_%d", j + 1).c_str());
			auto lv = (ImageView*)m_layer->getChildByName("skillInfoBg")->getChildByName(StringUtils::format("skillHead_%d", j + 1).c_str())->getChildByName("lv");
			auto num = (ImageView*)m_layer->getChildByName("skillInfoBg")->getChildByName(StringUtils::format("skillHead_%d", j + 1).c_str())->getChildByName("num");
			lv->setVisible(false);
			num->setVisible(false);
			skillHead->loadTexture(StringUtils::format("ui/downUi/servant/skillBig/%d/%d.png", id + 1, j + 1).c_str());
		}	
	}

	head->setTexture(StringUtils::format("ui/downUi/servant/head/big/%d.png", id + 1));
	name->setString(SqLite::getInstance()->getServantNameByID(id));
	level->setString(StringUtils::format("Lv%d", PlayerData::getInstance()->getServantLevel(id)));
	dps->setString(Ruler::getInstance()->showNum(PlayerData ::getInstance()->getServantDps(id)));
	serInfo->setString(SqLite::getInstance()->getServantByID(id)->discribe);
	
	escBtn->addTouchEventListener([this](Ref* Sender, Widget::TouchEventType Event)
	{
		if (Event == Widget::TouchEventType::ENDED)
		{
			m_node->removeFromParent();
			m_bgLayer->removeFromParent();
		}
	});
}

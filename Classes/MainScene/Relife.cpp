
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
	auto playerLv = (Text*)m_layer->getChildByName("infoBg")->getChildByName("plLv");
	auto playerStone = (Text*)m_layer->getChildByName("infoBg")->getChildByName("playerStone");
	auto servantLv = (Text*)m_layer->getChildByName("infoBg")->getChildByName("serLv");
	auto serStone = (Text*)m_layer->getChildByName("infoBg")->getChildByName("serStone");
	auto count = (Text*)m_layer->getChildByName("infoBg")->getChildByName("count");
	auto countStone = (Text*)m_layer->getChildByName("infoBg")->getChildByName("countStone");
	auto allLv = (Text*)m_layer->getChildByName("infoBg")->getChildByName("allLv");
	auto alStone = (Text*)m_layer->getChildByName("infoBg")->getChildByName("allStone");

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

		}
	});
}
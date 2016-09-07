#include "Ui/ItemLayer.h"
#include "ui/CocosGUI.h"
#include <cocostudio/CocoStudio.h> 
#include "SaveData/PlayerData.h"
#include "SaveData/ShopData.h"
#include "Tool/SqLite.h"
#include "Tool/Rule.h"
using namespace ui;

bool ItemLayer::init()
{
	if(!Layer::init())
	{
		return false;
	}

	m_rootNode = CSLoader::createNode("ItemLayer.csb");
	m_layer = m_rootNode->getChildByName("bg");
	this->setContentSize(m_rootNode->getContentSize());
	this->addChild(m_rootNode);
	return true;
}

void ItemLayer::initItemLayer(int id)
{
	CCNotificationCenter::getInstance()->addObserver(this, callfuncO_selector(ItemLayer::itemChange), "itemChange", nullptr);

	auto name = (Text*)m_layer->getChildByName("infoBg")->getChildByName("name");
	auto info = (Text*)m_layer->getChildByName("infoBg")->getChildByName("info");
	auto money = (Text*)m_layer->getChildByName("infoBg")->getChildByName("moneyNum");
	auto time = (Text*)m_layer->getChildByName("time");
	auto up = (Button*)m_layer->getChildByName("up");

	//head->setTexture("");
	//name->setString("");
	//info->setString("");
	//money->setString("");

	up->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type)
	{
		
	});
}

void ItemLayer::itemChange(Ref * ref)
{

}
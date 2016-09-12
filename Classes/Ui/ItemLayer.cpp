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
	m_id = id;
	auto name = (Text*)m_layer->getChildByName("name");
	auto info = (Text*)m_layer->getChildByName("infoBg")->getChildByName("info");
	auto money = (Text*)m_layer->getChildByName("up")->getChildByName("moneyNum");
	auto time = (Text*)m_layer->getChildByName("time");
	auto up = (Button*)m_layer->getChildByName("up");

	name->setString(SqLite::getInstance()->getItemByID(m_id)->name);
	info->setString(SqLite::getInstance()->getItemByID(m_id)->effdis);
	money->setString(StringUtils::format("-%d", SqLite::getInstance()->getItemByID(m_id)->expense).c_str());
	if (SqLite::getInstance()->getItemByID(m_id)->type)
	{
		time->setString(StringUtils::format("%dS", 0));		
	}
	else
	{
		time->setString(StringUtils::format("%d", 0));
	}

	up->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			switch (m_id)
			{
			case 0:
			case 1:
			case 2:
			case 3:
				if (ShopData::getInstance()->getCount(m_id)>0)
				{
					ShopData::getInstance()->useItemByID(m_id);
				}
				else
				{
					ShopData::getInstance()->buyItemByID(m_id);
					ShopData::getInstance()->subShopGold(SqLite::getInstance()->getItemByID(m_id)->expense);
				}
				break;
			default:
				ShopData::getInstance()->buyItemByID(m_id);
				ShopData::getInstance()->subShopGold(SqLite::getInstance()->getItemByID(m_id)->expense);
				break;
			}
			CCNotificationCenter::getInstance()->postNotification("itemChange");
		}
	});
	itemChange(this);
}

void ItemLayer::itemChange(Ref * ref)
{
	auto name = (Text*)m_layer->getChildByName("name");
	auto info = (Text*)m_layer->getChildByName("infoBg")->getChildByName("info");
	auto money = (Text*)m_layer->getChildByName("up")->getChildByName("moneyNum");

	name->setString(SqLite::getInstance()->getItemByID(m_id)->name);
	info->setString(SqLite::getInstance()->getItemByID(m_id)->effdis);
	money->setString(StringUtils::format("-%d", SqLite::getInstance()->getItemByID(m_id)->expense).c_str());

	btnChange();
	timeCalculate();

}

void ItemLayer::timeCalculate()
{
	auto time = (Text*)m_layer->getChildByName("time");
	auto timeText = (Text*)m_layer->getChildByName("timeText");
	if (SqLite::getInstance()->getItemByID(m_id)->type)
	{
		if (ShopData::getInstance()->getItemBeUsedById(m_id))
		{
			m_time = SqLite::getInstance()->getItemByID(m_id)->time;
			if ((m_time / 60) < 1)
			{
				time->setString(StringUtils::format("%ds", (int)m_time).c_str());
			}
			else if ((m_time / 60) >= 1 && (m_time / 60) < 60)
			{
				m_time /= 60;
				time->setString(StringUtils::format("%dm", (int)m_time).c_str());
			}
			if ((m_time / 60) >= 60)
			{
				m_time /= 3600;
				time->setString(StringUtils::format("%dh", (int)m_time).c_str());
			}
			
		}
		else
		{
			time->setString(StringUtils::format("%ds", 0).c_str());
		}
		
	}
	else
	{
		timeText->setVisible(false);
		time->setVisible(false);
	}
}

void ItemLayer::btnChange()
{
	auto up = (Button*)m_layer->getChildByName("up");
	auto money = (Text*)up->getChildByName("moneyNum");

	if (ShopData::getInstance()->getItemBeUsedById(m_id))
	{
		up->setEnabled(false);
		money->setVisible(true);
		up->getChildByName("money")->setVisible(true);
		up->getChildByName("text")->setVisible(false);
	}
	else
	{
		auto judge = ShopData::getInstance()->getShopGold() - SqLite::getInstance()->getItemByID(m_id)->expense;
		if (judge >= 0)
		{
			up->setEnabled(true);
			if (m_id < 4)
			{
				if (ShopData::getInstance()->getCount(m_id)>0)
				{
					money->setVisible(false);
					up->getChildByName("money")->setVisible(false);
					up->getChildByName("text")->setVisible(true);
				}
				else
				{
					money->setVisible(true);
					up->getChildByName("money")->setVisible(true);
					up->getChildByName("text")->setVisible(false);
				}
			}
		}
		else
		{
			up->setEnabled(false);
		}
	}
}
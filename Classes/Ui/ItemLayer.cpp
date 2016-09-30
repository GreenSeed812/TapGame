#include "Ui/ItemLayer.h"
#include "ui/CocosGUI.h"
#include "Ui/ArStarUp.h"
#include <cocostudio/CocoStudio.h> 
#include "SaveData/PlayerData.h"
#include "SaveData/ShopData.h"
#include "SaveData/ArtifactData.h"
#include "Tool/SqLite.h"
#include "Tool/Rule.h"
using namespace ui;

bool ItemLayer::init()
{
	if(!Layer::init())
	{
		return false;
	}
	m_time = 0;
	m_rootNode = CSLoader::createNode("ItemLayer.csb");
	m_rootNode->setTag(0);
	m_layer = m_rootNode->getChildByName("bg");
	this->setContentSize(m_rootNode->getContentSize());
	this->addChild(m_rootNode);
	return true;
}

void ItemLayer::initItemLayer(int id)
{
	ArStarUp::getInstance()->setNode(m_node);
	auto strings = FileUtils::getInstance()->getValueMapFromFile("fonts/text.xml");
	m_text = TextFieldTTF::createWithTTF(strings["text2"].asString(), "fonts/FZDH.ttf", 48);
	m_text->setPosition(m_node->getContentSize() / 2);
	m_text->setName("itemText");
	m_text->setColor(ccc3(239,203,148));
	m_node->addChild(m_text);
	m_text->setVisible(false);
	this->setTag(0);
	CCNotificationCenter::getInstance()->addObserver(this, callfuncO_selector(ItemLayer::itemChange), "itemChange", nullptr);
	m_id = id;
	auto info = (Text*)m_layer->getChildByName("infoBg")->getChildByName("info");
	auto money = (Text*)m_layer->getChildByName("up")->getChildByName("moneyNum");
	auto time = (Text*)m_layer->getChildByName("time");
	auto up = (Button*)m_layer->getChildByName("up");
	auto head = (Sprite*)m_layer->getChildByName("head");

	head->setTexture(StringUtils::format("item/%d.png",m_id+1).c_str());

	info->setString(SqLite::getInstance()->getItemByID(m_id)->effdis);
	money->setString(StringUtils::format("%d", SqLite::getInstance()->getItemByID(m_id)->expense).c_str());
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
			if (m_id < 4)
			{
				if (ShopData::getInstance()->getCount(m_id)>0)
				{
					ShopData::getInstance()->useItemByID(m_id);
				}
				else
				{
					ShopData::getInstance()->buyItemByID(m_id);
					ShopData::getInstance()->subShopGold(SqLite::getInstance()->getItemByID(m_id)->expense);
				}
			}
			else
			{
				ShopData::getInstance()->buyItemByID(m_id);		
				if (m_id == 7)
				{
					if (!ArtifactData::getInstance()->arStarUp())
					{
						m_text->setVisible(true);
						auto action = Sequence::create(DelayTime::create(3), CallFuncN::create(CC_CALLBACK_1(ItemLayer::callBack, this)),nullptr);
						m_text->runAction(action);					
					}
					else
					{
						ShopData::getInstance()->subShopGold(SqLite::getInstance()->getItemByID(m_id)->expense);
					}
				}
				else
				{
					ShopData::getInstance()->subShopGold(SqLite::getInstance()->getItemByID(m_id)->expense);
				}
			}
			CCNotificationCenter::getInstance()->postNotification("itemChange");
		}
	});
	itemChange(this);
}

void ItemLayer::itemChange(Ref * ref)
{
	auto info = (Text*)m_layer->getChildByName("infoBg")->getChildByName("info");
	auto money = (Text*)m_layer->getChildByName("up")->getChildByName("moneyNum");

	info->setString(SqLite::getInstance()->getItemByID(m_id)->effdis);
	money->setString(StringUtils::format("%d", SqLite::getInstance()->getItemByID(m_id)->expense).c_str());

	timeCalculate();
	btnChange();
}

void ItemLayer::timeCalculate()
{
	auto time = (Text*)m_layer->getChildByName("time");
	auto timeText = (Text*)m_layer->getChildByName("timeText");
	if (SqLite::getInstance()->getItemByID(m_id)->type)
	{
		if (ShopData::getInstance()->getItemDataById(m_id)->isUsing)
		{
			ShopData::getInstance()->setNum(m_id);
			setTime();
			if (m_time < 60)
			{
				time->setString(StringUtils::format("%.0fs", m_time).c_str());
			}
			else if ((m_time / 60) >= 1 && (m_time / 60) < 60)
			{
				m_time /= 60;
				time->setString(StringUtils::format("%.0fm", m_time).c_str());
			}
			if ((m_time / 60) >= 60)
			{
				m_time /= 3600;
				time->setString(StringUtils::format("%.0fh", m_time).c_str());
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
	if (ShopData::getInstance()->getItemDataById(m_id)->isUsing)
	{
		if (SqLite::getInstance()->getItemByID(m_id)->type)
		{
			up->setEnabled(false);
		}
		else
		{
			auto judge = ShopData::getInstance()->getShopGold() - SqLite::getInstance()->getItemByID(m_id)->expense;
			if (judge >= 0)
			{
				up->setEnabled(true);
			}
			else
			{
				up->setEnabled(false);
			}
			if (m_id == 8)
			{
				up->setEnabled(false);
			}
		}
		money->setVisible(true);
		up->getChildByName("money")->setVisible(true);
		up->getChildByName("text")->setVisible(false);
	}
	else
	{
		auto judge = ShopData::getInstance()->getShopGold() - SqLite::getInstance()->getItemByID(m_id)->expense;
		if (judge >= 0 && !ShopData::getInstance()->getItemBeUsedById(m_id))
		{
			up->setEnabled(true);
			if (m_id < 4)
			{
				auto count = ShopData::getInstance()->getCount(m_id);
				if (count > 0)
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

void ItemLayer::setTime()
{
	m_time = ShopData::getInstance()->getItemDataById(m_id)->leftTime;
}

void ItemLayer::callBack(Node* node)
{
	m_text->setVisible(false);
}
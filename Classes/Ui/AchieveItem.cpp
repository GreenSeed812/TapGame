
#include "Ui/AchieveItem.h"
#include "Ui/AchieveLayer.h"
#include "ui/CocosGUI.h"
#include <cocostudio/CocoStudio.h> 
#include "Tool/SqLite.h"
#include "SaveData/PlayerData.h"
#include "SaveData/ShopData.h"
#include "SaveData/AchieveData.h"
#include "AppDelegate.h"
using namespace cocostudio;
using namespace cocos2d;
using namespace ui;

Node * AchieveItem::g_node = nullptr;

bool AchieveItem::init()
{
	if (!Layer::init())
	{
		return false;
	}
	m_Rate = 1;
	m_money = 5;
	m_starUp = false;
	m_starUped = false;
	m_click = false;
	m_node = CSLoader::createNode("AchieveItem.csb");
	auto btn = (Button*)m_node->getChildByName("bgAchieve")->getChildByName("btn");
	btn->addTouchEventListener([this,btn](Ref* sender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			m_starUped = true;
			ShopData::getInstance()->addShopGold(m_money);
			AchieveData::getInstance()->addTotalReword(m_money);
			if (m_starNum < 5)
			{
				auto star = (ImageView*)m_node->getChildByName("bgAchieve")->getChildByName(StringUtils::format("star%d", m_starNum+1).c_str());
				star->loadTexture("xing1.png");
			}		
			m_starUped = false;
			m_starNum++;
			if (m_starNum >= 5)
			{
				m_starNum = 5;
			}
			AchieveData::getInstance()->setStarNumByID(m_id, m_starNum);
			initAchieveItem(m_id);			
			CCNotificationCenter::getInstance()->postNotification("AchieveChange");
		}
	});
	this->setContentSize(m_node->getContentSize());
	this->addChild(m_node);
	return true;
}

void AchieveItem::initAchieveItem(int id)
{
	m_id = id;
	auto text = (Text*)m_node->getChildByName("bgAchieve")->getChildByName("Text");
	auto num = (TextBMFont*)m_node->getChildByName("bgAchieve")->getChildByName("num");
	auto money = (TextBMFont*)m_node->getChildByName("bgAchieve")->getChildByName("btn")->getChildByName("money");
	m_starNum = AchieveData::getInstance()->getStarNumByID(m_id);
	if (AppDelegate::getPhoneType())
	{
		m_Rate = 1;
	}
	else
	{
		m_Rate = 10;
	}
	if (m_starNum < 5)
	{
		switch (m_starNum)
		{
		case 0:
			m_money = (5 * m_Rate);
			m_countMax = SqLite::getInstance()->getAchieveByID(m_id)->Star_1;
			break;
		case 1:
			m_money = (10 * m_Rate);
			m_countMax = SqLite::getInstance()->getAchieveByID(m_id)->Star_2;
			break;
		case 2:
			m_money = (15 * m_Rate);
			m_countMax = SqLite::getInstance()->getAchieveByID(m_id)->Star_3;
			break;
		case 3:
			m_money = (30 * m_Rate);
			m_countMax = SqLite::getInstance()->getAchieveByID(m_id)->Star_4;
			break;
		case 4:
			m_money = (50 * m_Rate);
			m_countMax = SqLite::getInstance()->getAchieveByID(m_id)->Star_5;
			break;
		}
	}
	else
	{
		m_countMax = SqLite::getInstance()->getAchieveByID(m_id)->Star_5;
	}
	stateChange();	

	for (size_t i = 0; i < m_starNum; i++)
	{
		auto star = (ImageView*)m_node->getChildByName("bgAchieve")->getChildByName(StringUtils::format("star%d", i+1).c_str());
		star->loadTexture("xing1.png");
	}

	auto numMax = Ruler::getInstance()->showNum(m_countMax);
	money->setString(StringUtils::format("%d", m_money).c_str());
	text->setString(SqLite::getInstance()->getAchieveByID(m_id)->discribe);
	m_starUp = false;

}

void AchieveItem::stateChange()
{
	auto btn = (Button*)m_node->getChildByName("bgAchieve")->getChildByName("btn");
	auto num = (TextBMFont*)m_node->getChildByName("bgAchieve")->getChildByName("num");
	auto numMax = Ruler::getInstance()->showNum(m_countMax);
	std::string numCount;
	switch (m_id)
	{
	case 2:
	case 6:
	{
		auto count = AchieveData::getInstance()->getMyNumByID(m_id);
		numCount = Ruler::getInstance()->showNum(count);
		if (Ruler::getInstance()->Zero(Ruler::getInstance()->subNum(m_countMax, AchieveData::getInstance()->getMyNumByID(m_id))))
		{
			m_starUp = true;
			if (m_starNum >= 5)
			{
				m_click = false;
				m_starUped = false;
			}
			else
			{
				m_click = true;
			}
		}
		else
		{
			m_click = false;
		}
	}
		break;
	case 19:
	case 20:
	case 21:
	case 22:
	case 23:
		numCount = StringUtils::format("%d", 0).c_str();
		break;
	default:
	{
		numCount = StringUtils::format("%d", AchieveData::getInstance()->getNumByID(m_id)).c_str();
		if ((m_countMax.number - AchieveData::getInstance()->getNumByID(m_id)) <= 0)
		{
			m_starUp = true;
			if (m_starNum >= 5)
			{
				m_click = false;
				m_starUped = false;
			}
			else
			{
				m_click = true;
			}
		}
		else
		{
			m_click = false;
		}
	}
		break;
	}

	if (m_click)
	{
		btn->setEnabled(true);
	}
	else
	{
		btn->setEnabled(false);
		if (m_starNum >= 5)
		{
			auto money = (TextBMFont*)m_node->getChildByName("bgAchieve")->getChildByName("btn")->getChildByName("money");
			auto btn = (Button*)m_node->getChildByName("bgAchieve")->getChildByName("btn");
			btn->loadTextureDisabled("cjdc.png");
			money->setVisible(false);
		}
	}

	num->setString(StringUtils::format("%s/%s", numCount.c_str(), numMax.c_str()).c_str());
}

#include "Ui/AchieveItem.h"
#include "Ui/AchieveLayer.h"
#include "ui/CocosGUI.h"
#include <cocostudio/CocoStudio.h> 
#include "Tool/SqLite.h"
#include "SaveData/PlayerData.h"
#include "SaveData/ShopData.h"
#include "SaveData/AchieveData.h"
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
	m_money = 5;
	m_starUp = false;
	m_starUped = false;
	m_click = false;
	m_node = CSLoader::createNode("AchieveItem.csb");
	auto btn = (Button*)m_node->getChildByName("bgAchieve")->getChildByName("btn");
	btn->addTouchEventListener([this,btn](Ref* sender, Widget::TouchEventType type)
	{
		AchieveLayer::setMoney(m_money);
		ShopData::getInstance()->addShopGold(m_money);
		m_click = false;
		initAchieveItem(m_id);
	});
	this->setContentSize(m_node->getContentSize());
	this->addChild(m_node);
	return true;
}

void AchieveItem::initAchieveItem(int id)
{
	m_id = id;
	m_starNum = AchieveData::getInstance()->getStarNumByID(m_id);
	if (m_starNum != 0)
	{
		m_starUped = true;
	}
	auto btn = (Button*)m_node->getChildByName("bgAchieve")->getChildByName("btn");
	auto text = (Text*)m_node->getChildByName("bgAchieve")->getChildByName("Text");
	auto num = (TextBMFont*)m_node->getChildByName("bgAchieve")->getChildByName("num");
	auto numMax = (TextBMFont*)m_node->getChildByName("bgAchieve")->getChildByName("numMax");
	auto money = (TextBMFont*)m_node->getChildByName("bgAchieve")->getChildByName("btn")->getChildByName("money");

	switch (m_starNum)
	{
	case 0:
		m_money = 5;
		m_countMax = SqLite::getInstance()->getAchieveByID(m_id)->Star_1;
		numMax->setString(Ruler::getInstance()->showNum(m_countMax));
		break;
	case 1:
		m_money = 10;
		m_countMax = SqLite::getInstance()->getAchieveByID(m_id)->Star_2;
		numMax->setString(Ruler::getInstance()->showNum(m_countMax));
		break;
	case 2:
		m_money = 15;
		m_countMax = SqLite::getInstance()->getAchieveByID(m_id)->Star_3;
		numMax->setString(Ruler::getInstance()->showNum(m_countMax));
		break;
	case 3:
		m_money = 30;
		m_countMax = SqLite::getInstance()->getAchieveByID(m_id)->Star_4;
		numMax->setString(Ruler::getInstance()->showNum(m_countMax));
		break;
	case 4:
		m_money = 50;
		m_countMax = SqLite::getInstance()->getAchieveByID(m_id)->Star_5;
		numMax->setString(Ruler::getInstance()->showNum(m_countMax));
		break;
	}

	switch (m_id)
	{
	case 2:
	case 6:
		num->setString(Ruler::getInstance()->showNum(AchieveData::getInstance()->getMyNumByID(m_id)));
		if (Ruler::getInstance()->Zero(Ruler::getInstance()->subNum(m_countMax, AchieveData::getInstance()->getMyNumByID(m_id))))
		{
			m_starUp = true;
			m_click = true;
			m_starNum++;
		}
	case 19:
	case 20:
	case 21:
	case 22:
	case 23:
		break;
	default:
		num->setString(StringUtils::format("%d", AchieveData::getInstance()->getNumByID(m_id)).c_str());
		if ((m_countMax.number - AchieveData::getInstance()->getNumByID(m_id)) <= 0)
		{
			m_starUp = true;
			m_click = true;
			m_starNum++;
		}
	}

	if (m_click)
	{
		btn->setEnabled(true);
	}
	else
	{
		btn->setEnabled(false);
	}

	for (size_t i = 0; i < m_starNum; i++)
	{
		auto star = (ImageView*)m_node->getChildByName("bgAchieve")->getChildByName(StringUtils::format("star%d", m_starNum).c_str());
		if (m_starUp || m_starUped)
		{
			star->loadTexture("xing1.png");
			AchieveData::getInstance()->setStarNumByID(m_id, m_starNum);
			m_starUped = true;
		}
		else
		{
			star->loadTexture("xing2.png");
		}
	}
	m_starUp = false;
	money->setString(StringUtils::format("%d", m_money).c_str());
	text->setString(SqLite::getInstance()->getAchieveByID(m_id)->discribe);
}

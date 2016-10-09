#include "Ui/SignLayer.h"
#include "ui/CocosGUI.h"
#include <cocostudio/CocoStudio.h> 
#include "Tool/SqLite.h"
#include "Tool/Rule.h"
#include "Tool/TimeTool.h"
#include "SaveData/PlayerData.h"
#include "SaveData/ShopData.h"
#include "SaveData/ArtifactData.h"
#include "AppDelegate.h"
using namespace cocostudio;
using namespace cocos2d;
using namespace ui;
USING_NS_CC;
bool SignLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	m_Rate = 1;
	m_bgLayer = LayerColor::create(Color4B(50, 50, 50, 155));
	this->addChild(m_bgLayer);
	m_state = true;
	rootNode = CSLoader::createNode("singLayer.csb");
	this->addChild(rootNode);
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(SignLayer::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
	initSignLayer();
	return true;
}

void SignLayer::initSignLayer()
{	
	CCNotificationCenter::getInstance()->addObserver(this, callfuncO_selector(SignLayer::signChange), "signChange", nullptr);
	if (AppDelegate::getPhoneType())
	{
		m_Rate = 1;
	}
	else
	{
		m_Rate = 2;
	}
	m_strings = FileUtils::getInstance()->getValueMapFromFile("fonts/skillState.xml");
	auto bt = (Button*)rootNode->getChildByName("bg")->getChildByName("esc");	
	bt->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type){
		if (type == Widget::TouchEventType::ENDED)
		{
			m_bgLayer->removeFromParent();
			this->removeFromParent();	
		}
	});

	for (size_t i = 0; i < 7; i++)
	{
		auto btn = (Button*)rootNode->getChildByName(StringUtils::format("btn%d", (i + 1)).c_str());
		switch (i)
		{
		case 0:
			btn->addTouchEventListener([this, btn](Ref* sender, Widget::TouchEventType type){
				if (type == Widget::TouchEventType::ENDED)
				{
					if (m_day == 0)
					{
						if (m_state)
						{
							auto gold = Ruler::getInstance()->multiplay(PlayerData::getInstance()->getdefeatMonsterGold(), 100);
							PlayerData::getInstance()->addGold(&gold);
							PlayerData::getInstance()->setSignCount();
							btn->setEnabled(false);
							m_state = false;
							PlayerData::getInstance()->setSignTime();
							PlayerData::getInstance()->saveUserData();
							signChange(this);
							auto num = (TextBMFont*)rootNode->getChildByName("bg")->getChildByName("dayNum");
							num->setString(StringUtils::format("%d", 1).c_str());
						}
					}
				}
			});
			break;
		case 1:
			btn->addTouchEventListener([this,btn](Ref* sender, Widget::TouchEventType type){
				if (type == Widget::TouchEventType::ENDED)
				{
					if (m_day == 1)
					{
						if (m_state)
						{
							int num = 1 * m_Rate;
							if (PlayerData::getInstance()->getSignNum() == 0)
							{
								ShopData::getInstance()->getItemDataById(0)->itemNum += ShopData::getInstance()->getItemDataById(0)->itemNum + num;
							}
							else
							{
								ShopData::getInstance()->getItemDataById(2)->itemNum += ShopData::getInstance()->getItemDataById(2)->itemNum + num;
							}
							PlayerData::getInstance()->setSignCount();
							btn->setEnabled(false);
							m_state = false;
							PlayerData::getInstance()->setSignTime();
							PlayerData::getInstance()->saveUserData();
							signChange(this);
							CCNotificationCenter::getInstance()->postNotification("itemChange");
						}	
					}
				}
			});
			break;
		case 2:
			btn->addTouchEventListener([this,btn](Ref* sender, Widget::TouchEventType type){
				if (type == Widget::TouchEventType::ENDED)
				{
					if (m_day == 2)
					{
						if (m_state)
						{
							ShopData::getInstance()->addShopGold(10);
							btn->setEnabled(false);
							PlayerData::getInstance()->setSignCount();
							m_state = false;
							PlayerData::getInstance()->setSignTime();
							PlayerData::getInstance()->saveUserData();
							signChange(this);
						}					
					}
				}
			});
			break;
		case 3:
			btn->addTouchEventListener([this,btn](Ref* sender, Widget::TouchEventType type){
				if (type == Widget::TouchEventType::ENDED)
				{
					if (m_day == 3)
					{
						if (m_state)
						{
							auto gold = Ruler::getInstance()->multiplay(PlayerData::getInstance()->getdefeatMonsterGold(), 1000);
							PlayerData::getInstance()->addGold(&gold);
							btn->setEnabled(false);
							PlayerData::getInstance()->setSignCount();
							PlayerData::getInstance()->setSignTime();
							m_state = false;
							PlayerData::getInstance()->saveUserData();
							signChange(this);
						}
					}
				}
			});
			break;
		case 4:
			btn->addTouchEventListener([this,btn](Ref* sender, Widget::TouchEventType type){
				if (type == Widget::TouchEventType::ENDED)
				{
					if (m_day == 4)
					{
						if (m_state)
						{
							int num = 1 * m_Rate;
							if (PlayerData::getInstance()->getSignNum() == 0)
							{
								ShopData::getInstance()->getItemDataById(1)->itemNum += ShopData::getInstance()->getItemDataById(1)->itemNum + num;
							}
							else
							{
								ShopData::getInstance()->getItemDataById(3)->itemNum += ShopData::getInstance()->getItemDataById(3)->itemNum + num;
							}
							btn->setEnabled(false);
							PlayerData::getInstance()->setSignCount();
							PlayerData::getInstance()->setSignTime();
							m_state = false;
							PlayerData::getInstance()->saveUserData();
							signChange(this);
							CCNotificationCenter::getInstance()->postNotification("itemChange");
						}						
					}

				}
			});
			break;
		case 5:
			btn->addTouchEventListener([this,btn](Ref* sender, Widget::TouchEventType type){
				if (type == Widget::TouchEventType::ENDED)
				{
					if (m_day == 5)
					{
						if (m_state)
						{
							ShopData::getInstance()->addShopGold(50);
							btn->setEnabled(false);
							PlayerData::getInstance()->setSignCount();
							PlayerData::getInstance()->setSignTime();
							m_state = false;
							PlayerData::getInstance()->saveUserData();
							signChange(this);
						}					
					}
				}
			});
			break;
		case 6:
			btn->addTouchEventListener([this,btn](Ref* sender, Widget::TouchEventType type){
				if (type == Widget::TouchEventType::ENDED)
				{
					if (m_day == 6)
					{
						if (m_state)
						{
							ArtifactData::getInstance()->addArtiStone(1);
							btn->setEnabled(false);
							PlayerData::getInstance()->setSignCount();
							PlayerData::getInstance()->setSignTime();
							m_state = false;
							auto num = (TextBMFont*)rootNode->getChildByName("bg")->getChildByName("dayNum");
							num->setString(StringUtils::format("%d",7).c_str());
							PlayerData::getInstance()->saveUserData();
							signChange(this);
						}					
					}
				}
			});
			break;
		}
	}
	signChange(this);
}

void SignLayer::signChange(Ref*ref)
{	
	if (ref)
	{
		m_day = PlayerData::getInstance()->getSignCount();
		auto dayNum = (TextBMFont*)rootNode->getChildByName("bg")->getChildByName("dayNum");
		dayNum->setString(StringUtils::format("%d", m_day));

		stateChange();
		btnChange();
	}
}

void SignLayer::stateChange()
{
	auto timeNow = *(TimeTool::getInstance()->getcurrTime());
	auto signTime = *(TimeTool::getInstance()->calTime(PlayerData::getInstance()->getSignTime()));
	auto num = timeNow.tm_yday - signTime.tm_yday;
	//num += 1;
	if (timeNow.tm_year == signTime.tm_year && num <= 0)
	{
		if (m_day == 0)
		{
			m_state = true;
			auto btn = (Button*)rootNode->getChildByName(StringUtils::format("btn%d", (m_day + 1)).c_str());
			btn->getChildByName("text")->setVisible(true);
		}
		else
		{
			m_state = false;
		}	
	}
	else
	{
		m_state = true;
		auto btn = (Button*)rootNode->getChildByName(StringUtils::format("btn%d", (m_day + 1)).c_str());
		btn->getChildByName("text")->setVisible(true);
		auto dayNum = (TextBMFont*)rootNode->getChildByName("bg")->getChildByName("dayNum");
		dayNum->setString(StringUtils::format("%d", m_day).c_str());
	}
}

void SignLayer::dayChange()
{
	if (m_day == 0)
	{
		auto timeNow = *(TimeTool::getInstance()->getcurrTime());
		auto signTime = *(TimeTool::getInstance()->calTime(PlayerData::getInstance()->getSignTime()));
		auto num = timeNow.tm_yday - signTime.tm_yday;
		auto dayNum = (TextBMFont*)rootNode->getChildByName("bg")->getChildByName("dayNum");
		auto btn1 = (Button*)rootNode->getChildByName("btn1");
		if (timeNow.tm_year == signTime.tm_year && num > 0)
		{
			btn1->getChildByName("text")->setVisible(true);
			for (size_t i = 0; i < 7; i++)
			{
				auto btn = (Button*)rootNode->getChildByName(StringUtils::format("btn%d", (i + 1)).c_str());
				dayNum->setString(StringUtils::format("%d", m_day).c_str());
				btn->setEnabled(true);
			}
		}
		else
		{
			btn1->getChildByName("text")->setVisible(false);
			dayNum->setString(StringUtils::format("%d", 7).c_str());
			stateChange();
		}
	}
	reset();
}

void SignLayer::reset()
{
	for (size_t i = 0; i < 7; i++)
	{
		auto btn = (Button*)rootNode->getChildByName(StringUtils::format("btn%d", (i + 1)).c_str());
		if (!btn->isEnabled())
		{
			btn->getChildByName("text")->setVisible(false);
		}
	}
}

void SignLayer::btnChange()
{
	for (size_t i = 0; i < 7; i++)
	{
		auto btn = (Button*)rootNode->getChildByName(StringUtils::format("btn%d", (i + 1)).c_str());
		auto text = (TextBMFont *)rootNode->getChildByName("bg")->getChildByName(StringUtils::format("day%d", (i + 1)).c_str());

		switch (i)
		{
		case 0:
		{
			if (m_day > 0)
			{
				btn->setEnabled(false);
			}
		}
		break;
		case 1:
		{
			if (PlayerData::getInstance()->getSignNum() == 0)
			{
				btn->loadTextureNormal("sign/sign1.png");
				btn->loadTexturePressed("sign/sign1.png");
				btn->loadTextureDisabled("sign/signed1.png");
			}
			else if (PlayerData::getInstance()->getSignNum() == 1)
			{
				btn->loadTextureNormal("sign/sign3.png");
				btn->loadTexturePressed("sign/sign3.png");
				btn->loadTextureDisabled("sign/signed3.png");
			}
			if (m_day > 1)
			{
				btn->setEnabled(false);
			}
		}
		break;
		case 2:
			if (m_day > 2)
			{
				btn->setEnabled(false);
			}
			break;
		case 3:
		{
			if (m_day > 3)
			{
				btn->setEnabled(false);
			}
		}
		break;
		case 4:
		{
			if (PlayerData::getInstance()->getSignNum() == 0)
			{
				btn->loadTextureNormal("sign/sign2.png");
				btn->loadTexturePressed("sign/sign2.png");
				btn->loadTextureDisabled("sign/signed2.png");
			}
			else if (PlayerData::getInstance()->getSignNum() == 1)
			{
				btn->loadTextureNormal("sign/sign4.png");
				btn->loadTexturePressed("sign/sign4.png");
				btn->loadTextureDisabled("sign/signed4.png");
			}
			if (m_day > 4)
			{
				btn->setEnabled(false);
			}
		}
		break;
		case 5:
			if (m_day > 5)
			{
				btn->setEnabled(false);
			}
			break;
		case 6:
			if (PlayerData::getInstance()->getSignNum() > 1)
			{
				btn->setEnabled(false);
			}
			break;
		}
	}
	dayChange();
}
#include "Ui/SignLayer.h"
#include "ui/CocosGUI.h"
#include <cocostudio/CocoStudio.h> 
#include <MainScene/HelloWorldScene.h>
#include "Tool/SqLite.h"
#include "Tool/Rule.h"
#include "Tool/TimeTool.h"
#include "SaveData/PlayerData.h"
#include "SaveData/ShopData.h"
#include "SaveData/ArtifactData.h"
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

	m_bgLayer = LayerColor::create(Color4B(50, 50, 50, 155));
	this->addChild(m_bgLayer);
	m_state = true;
	m_day = HelloWorld::getDay();
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
							HelloWorld::dayChange();
							btn->setEnabled(false);
							m_state = false;
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
							if (HelloWorld::getSignCount() == 0)
							{
								ShopData::getInstance()->getItemDataById(0)->itemNum++;
							}
							else
							{
								ShopData::getInstance()->getItemDataById(2)->itemNum++;
							}
							HelloWorld::dayChange();
							btn->setEnabled(false);
							m_state = false;
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
							HelloWorld::dayChange();
							m_state = false;
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
							HelloWorld::dayChange();
							m_state = false;
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
							if (HelloWorld::getSignCount() == 0)
							{
								ShopData::getInstance()->getItemDataById(1)->itemNum++;
							}
							else
							{
								ShopData::getInstance()->getItemDataById(3)->itemNum++;
							}
							btn->setEnabled(false);
							HelloWorld::dayChange();
							m_state = false;
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
							HelloWorld::dayChange();
							m_state = false;
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
							HelloWorld::dayChange();
							m_state = false;
							auto num = (TextBMFont*)rootNode->getChildByName("bg")->getChildByName("dayNum");
							num->setString(StringUtils::format("%d",7).c_str());
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
		m_day = HelloWorld::getDay();
		m_time = HelloWorld::getTime();
		auto num = (TextBMFont*)rootNode->getChildByName("bg")->getChildByName("dayNum");
		num->setString(StringUtils::format("%d", m_day));
		stateChange();
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
				if (HelloWorld::getSignCount() == 0)
				{
					btn->loadTextureNormal("sign/sign1.png");
					btn->loadTexturePressed("sign/sign1.png");
					btn->loadTextureDisabled("sign/signed1.png");
				}
				else if (HelloWorld::getSignCount() == 1)
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
				if (HelloWorld::getSignCount() == 0)
				{
					btn->loadTextureNormal("sign/sign2.png");
					btn->loadTexturePressed("sign/sign2.png");
					btn->loadTextureDisabled("sign/signed2.png");
				}
				else if (HelloWorld::getSignCount() == 1)
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
				if (m_day > 6)
				{
					btn->setEnabled(false);
				}
				break;
			}
		}
		if (m_day == 0)
		{
			for (size_t i = 0; i < 7; i++)
			{
				auto btn = (Button*)rootNode->getChildByName(StringUtils::format("btn%d", (i + 1)).c_str());
				btn->setEnabled(true);
			}
		}
	}
}

void SignLayer::stateChange()
{
	auto dayNum = HelloWorld::getDay();
	auto time = TimeTool::getInstance()->getcurrTime();
	auto year = time->tm_year;
	auto mon = time->tm_mon;
	auto day = time->tm_mday;
	
	if (m_time->tm_year == year && m_time->tm_mon == mon && m_time->tm_mday == day)
	{
		if (m_day == 0)
		{
			m_state = true;
		}
		else
		{
			m_state = false;
		}	
	}
	else
	{
		m_state = true;
	}
}

#include "SignLayer.h"
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
			this->removeFromParent();
		}
	});

	for (size_t i = 0; i < 7; i++)
	{
		auto btn = (Button*)rootNode->getChildByName(StringUtils::format("btn%d",(i+1)).c_str());
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
							auto img = (ImageView *)rootNode->getChildByName("img1");
							img->setVisible(false);
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
							if (m_day<7)
							{
								ShopData::getInstance()->buyItemByID(0);
							}
							else
							{
								ShopData::getInstance()->buyItemByID(2);
							}
							HelloWorld::dayChange();
							btn->setEnabled(false);
							m_state = false;
							signChange(this);
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
							if (m_day<7)
							{
								ShopData::getInstance()->buyItemByID(1);
							}
							else
							{
								ShopData::getInstance()->buyItemByID(3);
							}
							btn->setEnabled(false);
							HelloWorld::dayChange();
							m_state = false;
							signChange(this);
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
							auto img = (ImageView *)rootNode->getChildByName("img7");
							img->setVisible(false);
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
		//stateChange();
		for (size_t i = 0; i < 7; i++)
		{
			auto btn = (Button*)rootNode->getChildByName(StringUtils::format("btn%d", (i + 1)).c_str());
			auto text = (TextBMFont *)rootNode->getChildByName(StringUtils::format("day%d", (i + 1)).c_str());
			auto img = (ImageView *)rootNode->getChildByName(StringUtils::format("img%d", (i + 1)).c_str());
			switch (i)
			{
			case 0:
			{
				auto gold = Ruler::getInstance()->multiplay(PlayerData::getInstance()->getdefeatMonsterGold(), 100);
				text->setString(Ruler::getInstance()->showNum(gold));
				if (m_day > 0)
				{
					btn->setEnabled(false);
					img->setVisible(false);
				}
			}
			break;
			case 1:
			{
				auto texts = (Text *)rootNode->getChildByName(StringUtils::format("day%d", (i + 1)).c_str());
				if (HelloWorld::getSignCount() == 0)
				{
					texts->setString(m_strings["A"].asString());
				}
				else if (HelloWorld::getSignCount() == 1)
				{
					texts->setString(m_strings["C"].asString());
				}
				if (m_day > 1)
				{
					btn->setEnabled(false);
					img->setVisible(false);
				}
			}
			break;
			case 2:
				text->setString(StringUtils::format("%d", 10).c_str());
				if (m_day > 2)
				{
					btn->setEnabled(false);
					img->setVisible(false);
				}
				break;
			case 3:
			{
				auto gold = Ruler::getInstance()->multiplay(PlayerData::getInstance()->getdefeatMonsterGold(), 1000);
				text->setString(Ruler::getInstance()->showNum(gold));
				if (m_day > 3)
				{
					btn->setEnabled(false);
					img->setVisible(false);
				}
			}
			break;
			case 4:
			{
				auto texts = (Text *)rootNode->getChildByName(StringUtils::format("day%d", (i + 1)).c_str());
				if (HelloWorld::getSignCount() == 0)
				{
					texts->setString(m_strings["B"].asString());
				}
				else if (HelloWorld::getSignCount() == 1)
				{
					texts->setString(m_strings["D"].asString());
				}
				if (m_day > 4)
				{
					btn->setEnabled(false);
					img->setVisible(false);
				}
			}
			break;
			case 5:
				text->setString(StringUtils::format("%d", 50).c_str());
				if (m_day > 5)
				{
					btn->setEnabled(false);
					img->setVisible(false);
				}
				break;
			case 6:
				text->setString(StringUtils::format("%d", 1).c_str());
				if (m_day > 6)
				{
					btn->setEnabled(false);
					img->setVisible(false);
				}
				break;
			}
		}
		if (m_day == 0)
		{
			for (size_t i = 0; i < 7; i++)
			{
				auto btn = (Button*)rootNode->getChildByName(StringUtils::format("btn%d", (i + 1)).c_str());
				auto img = (ImageView *)rootNode->getChildByName(StringUtils::format("img%d", (i + 1)).c_str());
				btn->setEnabled(true);
				img->setVisible(true);
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

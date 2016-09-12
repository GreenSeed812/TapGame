#include "SignLayer.h"
#include "ui/CocosGUI.h"
#include <cocostudio/CocoStudio.h> 
#include <MainScene/HelloWorldScene.h>
#include "Tool/SqLite.h"
#include "Tool/Rule.h"
#include "SaveData/PlayerData.h"
#include "SaveData/ShopData.h"
#include "SaveData/ArtifactData.h"
using namespace cocostudio;
using namespace cocos2d;
using namespace ui;
bool SignLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	m_receive1 = false;
	m_receive2 = false;
	m_receive3 = false;
	m_receive4 = false;
	m_receive5 = false;
	m_receive6 = false;
	m_receive7 = false;
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
					if (m_receive1)
					{
						auto gold =Ruler::getInstance()->multiplay(PlayerData::getInstance()->getdefeatMonsterGold(),100);
						PlayerData::getInstance()->addGold(&gold);
						HelloWorld::dayChange();
						m_day++;
						m_receive1 = false;
						btn->setEnabled(false);
					}
				}
			});
			break;
		case 1:
			btn->addTouchEventListener([this,btn](Ref* sender, Widget::TouchEventType type){
				if (type == Widget::TouchEventType::ENDED)
				{
					if (m_receive2)
					{
						if (m_day<7)
						{
							ShopData::getInstance()->buyItemByID(0);
						}
						else
						{
							ShopData::getInstance()->buyItemByID(2);
						}	
						m_day++;
						HelloWorld::dayChange();
						m_receive2 = false;
						btn->setEnabled(false);
					}
				}
			});
			break;
		case 2:
			btn->addTouchEventListener([this,btn](Ref* sender, Widget::TouchEventType type){
				if (type == Widget::TouchEventType::ENDED)
				{
					if (m_receive3)
					{
						ShopData::getInstance()->addShopGold(10);
						m_receive3 = false;
						btn->setEnabled(false);
						m_day++;
						HelloWorld::dayChange();
					}
				}
			});
			break;
		case 3:
			btn->addTouchEventListener([this,btn](Ref* sender, Widget::TouchEventType type){
				if (type == Widget::TouchEventType::ENDED)
				{
					if (m_receive4)
					{
						auto gold = Ruler::getInstance()->multiplay(PlayerData::getInstance()->getdefeatMonsterGold(), 1000);
						PlayerData::getInstance()->addGold(&gold);
						m_receive4 = false;
						btn->setEnabled(false);
						m_day++;
						HelloWorld::dayChange();
					}
				}
			});
			break;
		case 4:
			btn->addTouchEventListener([this,btn](Ref* sender, Widget::TouchEventType type){
				if (type == Widget::TouchEventType::ENDED)
				{
					if (m_receive5)
					{
						if (m_day<7)
						{
							ShopData::getInstance()->buyItemByID(1);
						}
						else
						{
							ShopData::getInstance()->buyItemByID(3);
						}
						m_receive5 = false;
						btn->setEnabled(false);
						m_day++;
						HelloWorld::dayChange();
					}
				}
			});
			break;
		case 5:
			btn->addTouchEventListener([this,btn](Ref* sender, Widget::TouchEventType type){
				if (type == Widget::TouchEventType::ENDED)
				{
					if (m_receive6)
					{
						ShopData::getInstance()->addShopGold(50);
						m_receive6 = false;
						btn->setEnabled(false);
						m_day++;
						HelloWorld::dayChange();
					}
				}
			});
			break;
		case 6:
			btn->addTouchEventListener([this,btn](Ref* sender, Widget::TouchEventType type){
				if (type == Widget::TouchEventType::ENDED)
				{
					if (m_receive7)
					{
						ArtifactData::getInstance()->addArtiStone(1);
						m_receive7 = false;
						btn->setEnabled(false);
						m_day++;
						HelloWorld::dayChange();
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
	m_day = HelloWorld::getDay();
	for (size_t i = 0; i < 7; i++)
	{
		auto btn = (Button*)rootNode->getChildByName(StringUtils::format("btn%d", (i + 1)).c_str());
		auto text = (TextBMFont *)rootNode->getChildByName(StringUtils::format("day%d", (i + 1)).c_str());
		switch (i)
		{
		case 0:
		{
			auto gold = Ruler::getInstance()->multiplay(PlayerData::getInstance()->getdefeatMonsterGold(), 100);
			text->setString(Ruler::getInstance()->showNum(gold));
		}	
			break;
		case 1:
		{
			auto texts = (Text *)rootNode->getChildByName(StringUtils::format("day%d", (i + 1)).c_str());
			if (m_day<7)
			{
				texts->setString(m_strings["A"].asString());
			}
			else
			{
				texts->setString(m_strings["C"].asString());
			}
		}			
			break;
		case 2:
			text->setString(StringUtils::format("%d",10).c_str());
			break;
		case 3:
		{
			auto gold = Ruler::getInstance()->multiplay(PlayerData::getInstance()->getdefeatMonsterGold(), 1000);
			text->setString(Ruler::getInstance()->showNum(gold));
		}	
			break;
		case 4:
		{
			auto texts = (Text *)rootNode->getChildByName(StringUtils::format("day%d", (i + 1)).c_str());
			if (m_day<7)
			{
				texts->setString(m_strings["B"].asString());
			}
			else
			{
				texts->setString(m_strings["D"].asString());
			}
		}			
			break;
		case 5:
			text->setString(StringUtils::format("%d", 50).c_str());
			break;
		case 6:
			text->setString(StringUtils::format("%d", 1).c_str());
			text->setVisible(false);
			break;
		}
		switch (m_day)
		{
		case 0:
		case 7:
			m_receive1 = true;
			break;
		case 1:
		case 8:
			((Button*)rootNode->getChildByName("btn1"))->setEnabled(false);
			m_receive2 = true;
			break;
		case 2:
		case 9:
			m_receive3 = true;
			break;
		case 3:
		case 10:
			m_receive4 = true;
			break;
		case 4:
		case 11:
			m_receive5 = true;
			break;
		case 5:
		case 12:
			m_receive6 = true;
			break;
		case 6:
		case 13:
			m_receive7 = true;
			break;
		}
	}
}
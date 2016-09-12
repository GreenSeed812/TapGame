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
					if (m_day == 0 || m_day == 7)
					{
						auto gold =Ruler::getInstance()->multiplay(PlayerData::getInstance()->getdefeatMonsterGold(),100);
						PlayerData::getInstance()->addGold(&gold);
						HelloWorld::dayChange();
						m_day++;
						btn->setEnabled(false);
					}
				}
			});
			break;
		case 1:
			btn->addTouchEventListener([this,btn](Ref* sender, Widget::TouchEventType type){
				if (type == Widget::TouchEventType::ENDED)
				{
					if (m_day == 1 || m_day == 8)
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
						btn->setEnabled(false);
					}
				}
			});
			break;
		case 2:
			btn->addTouchEventListener([this,btn](Ref* sender, Widget::TouchEventType type){
				if (type == Widget::TouchEventType::ENDED)
				{
					if (m_day == 2 || m_day == 9)
					{
						ShopData::getInstance()->addShopGold(10);
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
					if (m_day == 3 || m_day == 10)
					{
						auto gold = Ruler::getInstance()->multiplay(PlayerData::getInstance()->getdefeatMonsterGold(), 1000);
						PlayerData::getInstance()->addGold(&gold);
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
					if (m_day == 4 || m_day == 11)
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
					if (m_day == 5 || m_day == 12)
					{
						ShopData::getInstance()->addShopGold(50);
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
					if (m_day == 6 || m_day == 13)
					{
						ArtifactData::getInstance()->addArtiStone(1);
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
	if (m_day > 0 && m_day != 7 || m_day > 7)
	{

	}
	if (m_day > 1 && m_day != 8 || m_day > 8)
	{

	}
	if (m_day > 2 && m_day != 9 || m_day > 9)
	{

	}
	if (m_day > 3 && m_day != 10 || m_day > 10)
	{

	}
	if (m_day > 4 && m_day != 11 || m_day > 11)
	{

	}
	if (m_day > 5 && m_day != 12 || m_day > 12)
	{

	}
	if (m_day > 6 && m_day != 13 || m_day > 13)
	{

	}

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
			if (m_day < 7)
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
			text->setString(StringUtils::format("%d", 10).c_str());
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
			if (m_day < 7)
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
			break;
		}
	}
}
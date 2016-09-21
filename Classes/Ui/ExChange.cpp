#include "Ui/ExChange.h"
#include "ui/CocosGUI.h"
#include <cocostudio/CocoStudio.h> 
#include "SaveData/PlayerData.h"
#include "SaveData/ShopData.h"
#include "SaveData/MissionData.h"
#include "MainScene/HelloWorldScene.h"
#include "Tool/SqLite.h"
#include "Tool/Rule.h"
using namespace ui;

Node * ExChange::g_node = nullptr;
int ExChange::g_countNow = 0;

bool ExChange::init()
{
	if(!Layer::init())
	{
		return false;
	}
	m_countMax = 5;
	m_money = 100;
	m_gold = Ruler::getInstance()->multiplay(PlayerData::getInstance()->getdefeatMonsterGold(),100);
	m_rootNode = CSLoader::createNode("jinbi.csb");
	this->setContentSize(m_rootNode->getContentSize());
	this->addChild(m_rootNode);
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [](Touch*, Event*)->bool{return true; };
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, m_rootNode);
	return true;
}

void ExChange::initExchange()
{
	CCNotificationCenter::getInstance()->addObserver(this, callfuncO_selector(ExChange::exChange), "exChange", nullptr);

	auto money = (TextBMFont*)m_rootNode->getChildByName("money");
	auto gold = (TextBMFont*)m_rootNode->getChildByName("gold");
	auto countMax = (TextBMFont*)m_rootNode->getChildByName("countMax");
	auto count = (TextBMFont*)m_rootNode->getChildByName("count");
	auto exchange = (Button*)m_rootNode->getChildByName("exchange");
	auto escBtn = (Button*)m_rootNode->getChildByName("esc");

	money->setString(StringUtils::format("%d",m_money).c_str());
	gold->setString(Ruler::getInstance()->showNum(m_gold));
	countMax->setString(StringUtils::format("/%d",m_countMax).c_str());
	count->setString(StringUtils::format("%d",g_countNow).c_str());

	exchange->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type){
		if (type == Widget::TouchEventType::ENDED)
		{
			if (ShopData::getInstance()->getShopGold()>m_money)
			{
				if (g_countNow>0)
				{
					HelloWorld::changeCount(true);
					g_countNow--;
					ShopData::getInstance()->subShopGold(m_money);
					PlayerData::getInstance()->addGold(&m_gold);
				}
				else
				{
					auto text = (Text*)m_rootNode->getChildByName("text");
					auto strings = FileUtils::getInstance()->getValueMapFromFile("fonts/skillState.xml");
					text->setString(strings["text1"].asString());
					text->setVisible(true);
					auto action = Sequence::create(DelayTime::create(2), CallFuncN::create(CC_CALLBACK_1(ExChange::callback, this)), nullptr);
					text->runAction(action);
				}
			}
			else
			{
				auto text = (Text*)m_rootNode->getChildByName("text");
				auto strings = FileUtils::getInstance()->getValueMapFromFile("fonts/skillState.xml");
				text->setString(strings["text2"].asString());
				text->setVisible(true);
				auto action = Sequence::create(DelayTime::create(2), CallFuncN::create(CC_CALLBACK_1(ExChange::callback, this)), nullptr);
				text->runAction(action);
			}
			MissionData::getInstance()->addMissionTimesById(3);
			exChange(this);
		}
	});

	escBtn->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type){
		if (type == Widget::TouchEventType::ENDED)
		{
			m_rootNode->removeFromParent();
		}
	});

}

void ExChange::exChange(Ref * ref)
{
		auto gold = (TextBMFont*)m_rootNode->getChildByName("gold");
		auto count = (TextBMFont*)m_rootNode->getChildByName("count");
		gold->setString(Ruler::getInstance()->showNum(m_gold));
		count->setString(StringUtils::format("%d", g_countNow).c_str());	
}

void ExChange::callback(Node *node)
{
	auto text = (Text*)m_rootNode->getChildByName("text");
	text->setVisible(false);
}

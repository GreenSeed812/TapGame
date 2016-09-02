#include "AchieveLayer.h"
#include "AchieveItem.h"
#include "ui/CocosGUI.h"
#include <cocostudio/CocoStudio.h> 
#include "Tool/SqLite.h"
#include "SaveData/PlayerData.h"
using namespace cocostudio;
using namespace cocos2d;
using namespace ui;

int AchieveLayer::g_money = 0;

bool AchieveLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	m_rootNode = CSLoader::createNode("achieveLayer.csb");
	m_bg = m_rootNode->getChildByName("bg");
	this->addChild(m_rootNode);
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(AchieveLayer::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
	Button* bt = (Button*)m_rootNode->getChildByName("esc");
	bt->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type){
		if (type == Widget::TouchEventType::ENDED)
		{
			this->removeFromParent();
		}
	});
	initAchieveLayer();
	return true;
}

void AchieveLayer::initAchieveLayer()
{
	CCNotificationCenter::getInstance()->addObserver(this, callfuncO_selector(AchieveLayer::achieveChange), "AchieveChange", nullptr);

	auto allStone = (TextBMFont*)m_rootNode->getChildByName("allStone");
	allStone->setString(StringUtils::format("%d", 0).c_str());
	auto listview = (ListView*)m_bg->getChildByName("ListView");
	for (size_t i = 1; i < 24; i++)
	{
		auto item = AchieveItem::create();
		item->initAchieveItem(i);
		auto widget = Widget::create();
		widget->setContentSize(item->getContentSize());
		widget->addChild(item);
		listview->pushBackCustomItem(widget);
	}
}

void AchieveLayer::achieveChange(Ref* ref)
{
	auto allStone = (TextBMFont*)m_rootNode->getChildByName("allStone");
	allStone->setString(StringUtils::format("%d", g_money).c_str());
}
#include "MissionLayer.h"
#include "Ui/TaskItem.h"
#include "ui/CocosGUI.h"
#include <cocostudio/CocoStudio.h> 
#include "Tool/SqLite.h"
#include "SaveData/PlayerData.h"
using namespace cocostudio;
using namespace cocos2d;
using namespace ui;
bool MissionLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	m_bgLayer = LayerColor::create(Color4B(50, 50, 50, 155));
	this->addChild(m_bgLayer);
	m_suc = false;
	rootNode = CSLoader::createNode("everydayLayer.csb");
	this->addChild(rootNode);
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(MissionLayer::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
	Button* bt = (Button*)rootNode->getChildByName("bg")->getChildByName("esc");
	bt->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type){
		if (type == Widget::TouchEventType::ENDED)
		{
			m_bgLayer->removeFromParent();
			this->removeFromParent();
		}
	});
	initMission();
	return true;
}

void MissionLayer::initMission()
{
	auto lv = (ListView*)rootNode->getChildByName("bg")->getChildByName("lv");
	for (size_t i = 0; i < 8; i++)
	{
		auto item = TaskItem::create();
		item->initTaskItem(i);
		auto widget = Widget::create();
		widget->addChild(item);
		widget->setContentSize(item->getContentSize());
		lv->pushBackCustomItem(widget);
	}
}

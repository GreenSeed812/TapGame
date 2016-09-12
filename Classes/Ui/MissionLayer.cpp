#include "MissionLayer.h"
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
	m_suc = false;
	rootNode = CSLoader::createNode("everydayLayer.csb");
	this->addChild(rootNode);
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(MissionLayer::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
	Button* bt = (Button*)rootNode->getChildByName("bgLayer")->getChildByName("esc");
	bt->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type){
		if (type == Widget::TouchEventType::ENDED)
		{
			this->removeFromParent();
		}
	});
	initMission();
	return true;
}

void MissionLayer::initMission()
{
	for (size_t i = 0; i < 5; i++)
	{
		auto btn = (Button*)rootNode->getChildByName(StringUtils::format("Button%d", i + 1).c_str());
		btn->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type){
			if (type == Widget::TouchEventType::ENDED)
			{
				
			}
		});
	}
	missionChange(this);
}

void MissionLayer::missionChange(Ref* ref)
{
	auto strings = FileUtils::getInstance()->getValueMapFromFile("fonts/skillState.xml");
	for (size_t i = 0; i < 5; i++)
	{
		auto head = (ImageView*)rootNode->getChildByName("bgLayer")->getChildByName(StringUtils::format("TaskHead%d", i + 1).c_str());
		auto img = (ImageView*)rootNode->getChildByName(StringUtils::format("img%d", i + 1).c_str());
		auto name = (Text*)rootNode->getChildByName(StringUtils::format("name%d", i + 1).c_str());
		auto text = (Text*)rootNode->getChildByName(StringUtils::format("text%d", i + 1).c_str());
		auto gold = (TextBMFont*)rootNode->getChildByName("bgLayer")->getChildByName(StringUtils::format("TaskGold%d", i + 1).c_str());
		auto btn = (Button*)rootNode->getChildByName(StringUtils::format("Button%d", i + 1).c_str());
		switch (i)
		{
		case 0:
		case 1:
		{
			gold->setString(StringUtils::format("%d", SqLite::getInstance()->getQuestById(i)->reward).c_str());
		}
			img->loadTexture("dim.png");
			break;
		case 3:
		{
			gold->setString(StringUtils::format("%d", SqLite::getInstance()->getQuestById(i)->reward).c_str());
		}
			img->loadTexture("stone.png");
			break;
		case 2:
		case 4:
		{
			auto num = Ruler::getInstance()->multiplay(PlayerData::getInstance()->getdefeatMonsterGold(), SqLite::getInstance()->getQuestById(i)->reward);
			gold->setString(Ruler::getInstance()->showNum(num));
		}			
			img->loadTexture("gold.png");
			break;
		}
		name->setString(SqLite::getInstance()->getQuestById(i)->MissionName);
		text->setString(SqLite::getInstance()->getQuestById(i)->MissionDis);
		if (m_suc)
		{
			btn->setEnabled(true);			
		}
	}
}

#include "Ui/TaskItem.h"
#include "ui/CocosGUI.h"
#include "MainScene/HelloWorldScene.h"
#include <cocostudio/CocoStudio.h> 
#include "Tool/SqLite.h"
#include "Tool/Rule.h"
#include "Tool/TimeTool.h"
#include "SaveData/PlayerData.h"
#include "SaveData/ShopData.h"
#include "SaveData/AchieveData.h"
#include "SaveData/ArtifactData.h"
USING_NS_CC;
using namespace cocostudio;
using namespace ui;

bool TaskItem::init()
{
	if (!Layer::init())
	{
		return false;
	}

	m_skillCount = 0;
	m_levelUpCount = 0;
	m_state = false;
	m_rootNode = CSLoader::createNode("TaskItem.csb");
	this->setContentSize(m_rootNode->getContentSize());
	this->addChild(m_rootNode);
	return true;
}

void TaskItem::initTaskItem(int id)
{
	m_id = id;
	auto btn = (Button*)m_rootNode->getChildByName("btn");
	switch (m_id)
	{
	case 0:
	case 1:
	case 5:
	case 6:
		btn->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type){
			if (type == Widget::TouchEventType::ENDED)
			{
				ShopData::getInstance()->addShopGold(SqLite::getInstance()->getQuestById(m_id)->reward);
				m_state = false;
			}
		});
		break;
	case 2:
	case 4:
	case 7:
	case 8:
		btn->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type){
			if (type == Widget::TouchEventType::ENDED)
			{
				auto num = Ruler::getInstance()->multiplay(PlayerData::getInstance()->getdefeatMonsterGold(), SqLite::getInstance()->getQuestById(m_id)->reward);
				PlayerData::getInstance()->addGold(&num);
				m_state = false;
			}
		});
		break;
	case 3:
		btn->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type){
			if (type == Widget::TouchEventType::ENDED)
			{
				ArtifactData::getInstance()->addArtiStone(SqLite::getInstance()->getQuestById(m_id)->reward);
				m_state = false;
			}
		});	
	}
	taskChange(this);
}

void TaskItem::taskChange(Ref* ref)
{
	auto head = (ImageView*)m_rootNode->getChildByName("head");
	auto name = (Text*)m_rootNode->getChildByName("name");
	auto info = (Text*)m_rootNode->getChildByName("info");
	auto gold = (TextBMFont*)m_rootNode->getChildByName("gold");
	auto img = (ImageView*)m_rootNode->getChildByName("img");

	//head->loadTexture("");
	name->setString(SqLite::getInstance()->getQuestById(m_id)->MissionName);
	info->setString(SqLite::getInstance()->getQuestById(m_id)->MissionDis);
	switch (m_id)
	{
	case 0:
	case 1:
	case 5:
	case 6:
	{
		gold->setString(StringUtils::format("%d", SqLite::getInstance()->getQuestById(m_id)->reward).c_str());
		img->loadTexture("dim.png");
	}
		break;
	case 2:
	case 4:
	case 7:
	case 8:
	{
		auto num = Ruler::getInstance()->multiplay(PlayerData::getInstance()->getdefeatMonsterGold(), SqLite::getInstance()->getQuestById(m_id)->reward);
		gold->setString(Ruler::getInstance()->showNum(num));
		img->loadTexture("gold.png");
	}
		break;
	case 3:
		gold->setString(StringUtils::format("%d", SqLite::getInstance()->getQuestById(m_id)->reward).c_str());
		img->loadTexture("stone.png");
	}
	stateChange();
	auto btn = (Button*)m_rootNode->getChildByName("btn");
	btn->setEnabled(m_state);
}

void TaskItem::stateChange()
{
	auto time = TimeTool::getInstance()->getcurrTime();
	auto year = time->tm_year;
	auto day = time->tm_yday;
	if (!(HelloWorld::getTime()->tm_year == year && HelloWorld::getTime()->tm_yday == day))
	{
		m_state = true;
		m_skillCount = 0;
		m_levelUpCount = PlayerData::getInstance()->getPlayerLevel();
	}
	switch (m_id)
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		if (AchieveData::getInstance()->getNumByID(8) == 800)
		{
			m_state = true;
		}
		break;
	case 5:
	{
		auto hour = time->tm_hour + 1;
		log("%d", hour);
		if (hour >= 9 && hour <= 12)
		{
			m_state = true;
		}
	}
	break;
	case 6:
	{	
		auto hour = time->tm_hour + 1;
		log("%d",hour);
		if (hour >= 18 && hour <= 21)
		{
			m_state = true;
		}
	}		
		break;
	case 7:
		m_levelUpCount -= AchieveData::getInstance()->getNumByID(10);
		if (m_levelUpCount >= 20)
		{
			m_state = true;
		}
		break;
	case 8:
	{
		for (size_t i = 12; i < 18; i++)
		{
			m_skillCount += AchieveData::getInstance()->getNumByID(i);
		}
		if (m_skillCount >= 10)
		{
			m_state = true;
		}
	}	
		break;
	}
}
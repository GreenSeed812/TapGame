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
#include "SaveData/MissionData.h"
#include "AppDelegate.h"
USING_NS_CC;
using namespace cocostudio;
using namespace ui;

bool TaskItem::init()
{
	if (!Layer::init())
	{
		return false;
	}
	m_state = false;
	m_clicked = true;
	m_strings = FileUtils::getInstance()->getValueMapFromFile("fonts/taskState.xml");
	m_rootNode = CSLoader::createNode("TaskItem.csb");
	this->setContentSize(m_rootNode->getContentSize());
	this->addChild(m_rootNode);
	return true;
}

void TaskItem::initTaskItem(int id)
{
	m_id = id;
	auto btn = (Button*)m_rootNode->getChildByName("btn");
	if (AppDelegate::getPhoneType())
	{
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
					m_clicked = false;
					MissionData::getInstance()->setMissionTimesById(m_id, -100000000);
					PlayerData::getInstance()->saveUserData();
					taskChange(this);
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
					m_clicked = false;
					MissionData::getInstance()->setMissionTimesById(m_id, -100000000);
					PlayerData::getInstance()->saveUserData();
					taskChange(this);
				}
			});
			break;
		case 3:
			btn->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type){
				if (type == Widget::TouchEventType::ENDED)
				{
					ArtifactData::getInstance()->addArtiStone(SqLite::getInstance()->getQuestById(m_id)->reward);
					m_state = false;
					m_clicked = false;
					MissionData::getInstance()->setMissionTimesById(m_id, -100000000);
					PlayerData::getInstance()->saveUserData();
					taskChange(this);
				}
			});
		}
	}
	else
	{
		switch (m_id)
		{
		case 0:
		case 1:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:	
			btn->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type){
				if (type == Widget::TouchEventType::ENDED)
				{
					ShopData::getInstance()->addShopGold(SqLite::getInstance()->getQuestById(m_id)->reward);
					m_state = false;
					m_clicked = false;
					MissionData::getInstance()->setMissionTimesById(m_id, -100000000);
					PlayerData::getInstance()->saveUserData();
					taskChange(this);
				}
			});
			break;
		case 2:
			btn->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type){
				if (type == Widget::TouchEventType::ENDED)
				{
					ArtifactData::getInstance()->addArtiStone(SqLite::getInstance()->getQuestById(m_id)->reward);
					m_state = false;
					m_clicked = false;
					MissionData::getInstance()->setMissionTimesById(m_id, -100000000);
					PlayerData::getInstance()->saveUserData();
					taskChange(this);
				}
			});
		}
	}
	taskChange(this);
}

void TaskItem::taskChange(Ref* ref)
{
	auto name = (Text*)m_rootNode->getChildByName("name");
	auto info = (Text*)m_rootNode->getChildByName("info");
	auto text = (Text*)m_rootNode->getChildByName("submit");
	auto gold = (TextBMFont*)m_rootNode->getChildByName("gold");
	auto img = (ImageView*)m_rootNode->getChildByName("img");

	name->setString(SqLite::getInstance()->getQuestById(m_id)->MissionName);
	info->setString(SqLite::getInstance()->getQuestById(m_id)->MissionDis);
	if (AppDelegate::getPhoneType())
	{
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
	}
	else
	{
		switch (m_id)
		{
		case 0:
		case 1:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		{
			gold->setString(StringUtils::format("%d", SqLite::getInstance()->getQuestById(m_id)->reward).c_str());
			img->loadTexture("dim.png");
		}
		break;
		case 2:
			gold->setString(StringUtils::format("%d", SqLite::getInstance()->getQuestById(m_id)->reward).c_str());
			img->loadTexture("stone.png");
		}
	}

	stateChange();
	auto btn = (Button*)m_rootNode->getChildByName("btn");
	if (m_state)
	{
		btn->setEnabled(true);
		text->setString(m_strings["click"].asString());
	}
	else
	{
		btn->setEnabled(false);
		text->setString(m_strings["no"].asString());
	}
	if (!m_clicked)
	{
		text->setString(m_strings["clicked"].asString());
	}
}

void TaskItem::stateChange()
{
	auto timeNow = *(TimeTool::getInstance()->getcurrTime());
	auto year = timeNow.tm_year;
	auto day = timeNow.tm_yday;
	auto signTime = *(TimeTool::getInstance()->calTime(PlayerData::getInstance()->getSignTime()));
	auto num = signTime.tm_yday - day;
	if (signTime.tm_year == year && num > 0)
	{
		m_state = false;
		m_clicked = true;
		MissionData::getInstance()->reset();
	}

	if (MissionData::getInstance()->getMissionTimesById(m_id) < 0)
	{
		m_state = false;
		m_clicked = false;
	}
	
	if (AppDelegate::getPhoneType())
	{
		switch (m_id)
		{
		case 0:
			if (MissionData::getInstance()->getMissionTimesById(0) != 0)
			{
				if (m_clicked)
				{
					m_state = true;
				}
			}
			break;
		case 1:
			if (MissionData::getInstance()->getMissionTimesById(1) != 0)
			{
				if (m_clicked)
				{
					m_state = true;
				}
			}
			break;
		case 2:
			if (MissionData::getInstance()->getMissionTimesById(2) >= 6)
			{
				if (m_clicked)
				{
					m_state = true;
				}
			}
			break;
		case 3:
			if (MissionData::getInstance()->getMissionTimesById(3) >= 2)
			{
				if (m_clicked)
				{
					m_state = true;
				}
			}
			break;
		case 4:
			if (MissionData::getInstance()->getMissionTimesById(4) >= 800)
			{
				if (m_clicked)
				{
					m_state = true;
				}
			}
			break;
		case 5:
		{
			auto timeNow = TimeTool::getInstance()->getcurrTime();
			auto hour = timeNow->tm_hour;
			if (hour >= 9 && hour <= 12)
			{
				if (m_clicked)
				{
					m_state = true;
				}
			}
		}
		break;
		case 6:
		{
			auto timeNow = TimeTool::getInstance()->getcurrTime();
			auto hour = timeNow->tm_hour;
			if (hour >= 18 && hour <= 21)
			{
				if (m_clicked)
				{
					m_state = true;
				}
			}
		}
		break;
		case 7:
			if (MissionData::getInstance()->getMissionTimesById(7) >= 20)
			{
				if (m_clicked)
				{
					m_state = true;
				}
			}
			break;
		case 8:
		{
			if (AppDelegate::getPhoneType())
			{
				if (MissionData::getInstance()->getMissionTimesById(8) >= 10)
				{
					if (m_clicked)
					{
						m_state = true;
					}
				}
			}
		}
		break;
		}
	}
	else
	{
		switch (m_id)
		{
		case 0:
			log("%d",MissionData::getInstance()->getMissionTimesById(0));
			if (MissionData::getInstance()->getMissionTimesById(0) >= 100)
			{
				if (m_clicked)
				{
					m_state = true;
				}
			}
			break;
		case 1:
			if (MissionData::getInstance()->getMissionTimesById(1) >= 2)
			{
				if (m_clicked)
				{
					m_state = true;
				}
			}
			break;
		case 2:
			if (MissionData::getInstance()->getMissionTimesById(2) >= 2)
			{
				if (m_clicked)
				{
					m_state = true;
				}
			}
			break;
		case 3:
			if (MissionData::getInstance()->getMissionTimesById(3) >= 800)
			{
				if (m_clicked)
				{
					m_state = true;
				}
			}
			break;
		case 4:
		{
			auto timeNow = TimeTool::getInstance()->getcurrTime();
			auto hour = timeNow->tm_hour;
			if (hour >= 9 && hour <= 12)
			{
				if (m_clicked)
				{
					m_state = true;
				}
			}
		}
		break;
		case 5:
		{
			auto timeNow = TimeTool::getInstance()->getcurrTime();
			auto hour = timeNow->tm_hour;
			if (hour >= 18 && hour <= 21)
			{
				if (m_clicked)
				{
					m_state = true;
				}
			}
		}
		break;
		case 6:
			if (MissionData::getInstance()->getMissionTimesById(7) >= 20)
			{
				if (m_clicked)
				{
					m_state = true;
				}
			}
			break;
		case 7:
		{
			if (MissionData::getInstance()->getMissionTimesById(8) >= 10)
			{
				if (m_clicked)
				{
					m_state = true;
				}
			}
		}
		break;
		}
	}
}
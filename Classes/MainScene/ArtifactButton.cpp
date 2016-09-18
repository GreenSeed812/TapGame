#include "MainScene/ArtifactButton.h"
#include "MainScene/ArReset.h"
#include "ui/CocosGUI.h"
#include <cocostudio/CocoStudio.h> 
#include "SaveData/ArtifactData.h"
#include "Tool/SqLite.h"
using namespace ui;


Node* ArtifactButton::g_lv = nullptr;
Node * ArtifactButton::g_node = nullptr;

bool ArtifactButton::init()
{
	if (!Layer::init())
	{
		return false;
	}
	m_levelUp = false;
	m_StoneNum = 0;
	m_node = CSLoader::createNode("artifactNode.csb");
	m_layer = (Layer*)m_node->getChildByName("Layer");
	this->setContentSize(m_node->getContentSize());
	this->addChild(m_node);

	return true;
}

void ArtifactButton::initArtifactLayer(int id,bool check)
{
	CCNotificationCenter::getInstance()->addObserver(this, callfuncO_selector(ArtifactButton::arChange), "ArChange", nullptr);
	ArtifactData::getInstance()->subArtiStone(ArtifactData::getInstance()->getNeededArStone());
	m_lhs = ArtifactData::getInstance()->getArtiStone();
	if (check)
	{
		m_id = id;
	}
	else
	{
		m_id = ArtifactData::getInstance()->addArNum();
	}
	m_level = ArtifactData::getInstance()->getLevel(m_id);
	if (m_level < ArtifactData::getInstance()->getMaxLevel(m_id))
	{
		m_levelUp = true;
	}
	else
	{
		m_levelUp = false;
	}

	//»ñÈ¡¿Ø¼þ
	auto head = (Button*)m_layer->getChildByName("arHead");
	auto name = (Text*)m_layer->getChildByName("discribe")->getChildByName("name");
	auto level = (Text*)m_layer->getChildByName("discribe")->getChildByName("lv");
	auto effect = (Text*)m_layer->getChildByName("discribe")->getChildByName("effect");
	auto dps = (Text*)m_layer->getChildByName("discribe")->getChildByName("dps");
	auto LevelUp = (Button*)m_layer->getChildByName("up");
	auto arStone = (TextBMFont*)LevelUp->getChildByName("linghunshi");

	head->loadTextureNormal(StringUtils::format("ui/downUi/artifact/%d.png", m_id));
	head->loadTexturePressed(StringUtils::format("ui/downUi/artifact/%d.png", m_id));
	name->setString(SqLite::getInstance()->getArtifactSkillByID(m_id).ar.NAME);
	level->setString(StringUtils::format("Lv%d",ArtifactData::getInstance()->getLevel(m_id)).c_str());
	auto effid = SqLite::getInstance()->getArtifactSkillByID(m_id).ar.effid;
	auto effData = SqLite::getInstance()->getArtifactSkillByID(m_id).ar.effData;
	{
		auto effDataUp = SqLite::getInstance()->getArtifactSkillByID(m_id).ar.effDataUp;	
		effData += effDataUp*m_level;
	}
	effect->setString(SqLite::getInstance()->getSkillEffDis(effid) + StringUtils::format("+%.1f%%", effData * 100).c_str());
	auto dpsData = SqLite::getInstance()->getArtifactSkillByID(m_id).ar.initAllDps;
	{
		auto dpsUp = SqLite::getInstance()->getArtifactSkillByID(m_id).ar.AllDpsUp;
		dpsData += dpsUp*(m_level-1);
	}
	dps->setString(StringUtils::format("%.1f%%", dpsData * 100).c_str());
	arStone->setString(StringUtils::format("%d", ArtifactData::getInstance()->getLevel(m_id)*2).c_str());

	LevelUp->addTouchEventListener([this](Ref* Sender, Widget::TouchEventType event)
	{
		if (event == Widget::TouchEventType::ENDED)
		{
			ArtifactData::getInstance()->arLevelUp(m_id);
			cocos2d::CCNotificationCenter::getInstance()->postNotification("ArChange");
		}
		
	});
	head->addTouchEventListener([this](Ref* Sender, Widget::TouchEventType event)
	{
		if (event == Widget::TouchEventType::ENDED)
		{
			auto arReset = ArReset::create();
			arReset->setListView(g_lv);
			arReset->setWidget(m_widget);
			arReset->setBtn(this);
			arReset->setStoneNum(m_StoneNum);
			arReset->initArResetLayer(m_id);
			g_node->addChild(arReset);
		}
	});
	cocos2d::CCNotificationCenter::getInstance()->postNotification("ArChange");
}

void ArtifactButton::arChange(Ref*)
{
	if (m_node != nullptr)
	{
		if (m_layer)
		{
			auto bt = (Button*)m_layer->getChildByName("up");
			if (m_levelUp)
			{
				auto judge = m_lhs - ArtifactData::getInstance()->getNeededArStone();

				if (judge >= 0)
				{
					m_StoneNum += ArtifactData::getInstance()->getNeededArStone();
					bt->setEnabled(true);
					m_layer->setColor(Color3B(255, 255, 255));
				}
				else
				{
					bt->setEnabled(false);
				}
			}
			else
			{
				bt->setEnabled(false);
			}
		}
		
	}
}


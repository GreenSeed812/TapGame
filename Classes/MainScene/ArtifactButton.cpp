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
	node = CSLoader::createNode("artifactNode.csb");
	m_layer = (Layer*)node->getChildByName("Layer");
	this->setContentSize(node->getContentSize());
	this->addChild(node);

	return true;
}

void ArtifactButton::initArtifactLayer()
{
	CCNotificationCenter::getInstance()->addObserver(this, callfuncO_selector(ArtifactButton::arChange), "ArChange", nullptr);
	ArtifactData::getInstance()->subArtiStone(ArtifactData::getInstance()->getNeededArStone());
	m_lhs = ArtifactData::getInstance()->getArtiStone();
	m_id = ArtifactData::getInstance()->addArNum();
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
	auto head = (Sprite*)m_layer->getChildByName("head");
	auto name = (Text*)m_layer->getChildByName("discribe")->getChildByName("name");
	auto level = (Text*)m_layer->getChildByName("discribe")->getChildByName("lv");
	auto effect = (Text*)m_layer->getChildByName("discribe")->getChildByName("effect");
	auto dps = (Text*)m_layer->getChildByName("discribe")->getChildByName("dps");
	auto LevelUp = (Button*)m_layer->getChildByName("up");
	auto arStone = (TextBMFont*)LevelUp->getChildByName("linghunshi");

	head->setTexture(StringUtils::format("ui/downUi/artifact/%d.png", m_id));
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
			arChange(this);
		}
		
	});
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(ArtifactButton::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(ArtifactButton::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
	arChange(this);
}

void ArtifactButton::arChange(Ref*)
{
	if (node != nullptr)
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

bool ArtifactButton::onTouchBegan(Touch * touch, Event* event)
{
	return true;
}
void ArtifactButton::onTouchEnded(Touch * touch, Event * event)
{
	if (node != nullptr)
	{
		auto pos = this->convertTouchToNodeSpace(touch);
		auto head = (Sprite*)m_layer->getChildByName("head");
		if (head->getBoundingBox().containsPoint(pos))
		{
			auto arReset = ArReset::create();
			arReset->setNode(g_lv, node->getTag());
			arReset->setStoneNum(m_StoneNum);
			arReset->initArResetLayer(m_id);
			g_node->addChild(arReset);

		}
	}
}
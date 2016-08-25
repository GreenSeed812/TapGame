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

	node = CSLoader::createNode("artifactNode.csb");
	m_layer = (Layer*)node->getChildByName("Layer");
	this->setContentSize(node->getContentSize());
	this->addChild(node);

	return true;
}

void ArtifactButton::initArtifactLayer()
{
	CCNotificationCenter::getInstance()->addObserver(this, callfuncO_selector(ArtifactButton::arChange), "ArChange", nullptr);
	
	m_lhs = ArtifactData::getInstance()->getArtiStone();
	m_id = ArtifactData::getInstance()->addArNum();
	//获取控件
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
		auto level = ArtifactData::getInstance()->getLevel(m_id);
		effData += effDataUp*level;
	}
	effect->setString(SqLite::getInstance()->getSkillEffDis(effid)+StringUtils::format("+%.1f%%",effData*100).c_str());
	//dps->setString(StringUtils::format(""));//未设置，所有攻击力
	arStone->setString(StringUtils::format("%d",ArtifactData::getInstance()->getArtiStone()).c_str());

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
	auto bt = (Button*)m_layer->getChildByName("up");
	if (true)//判断是否到达最大等级，未实现
	{
		auto judge = m_lhs - ArtifactData::getInstance()->getNeededArStone();

		if (judge >= 0)
		{
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

bool ArtifactButton::onTouchBegan(Touch * touch, Event* event)
{
	return true;
}
void ArtifactButton::onTouchEnded(Touch * touch, Event * event)
{
	auto pos = this->convertTouchToNodeSpace(touch);
	auto head = (Sprite*)m_layer->getChildByName("head");
	if (head->getBoundingBox().containsPoint(pos))
	{
		auto arReset = ArReset::create();
		arReset->initArResetLayer(m_id);
		g_node->addChild(arReset);
	}
}
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
	m_id = cocos2d::random(0, 28);
	ArtifactData::getInstance()->addArNum(m_id);
	//»ñÈ¡¿Ø¼þ
	auto head = (Sprite*)m_layer->getChildByName("head");
	auto name = (Text*)m_layer->getChildByName("discribe")->getChildByName("name");
	auto level = (Text*)m_layer->getChildByName("discribe")->getChildByName("lv");
	auto effect = (Text*)m_layer->getChildByName("discribe")->getChildByName("effect");
	auto dps = (Text*)m_layer->getChildByName("discribe")->getChildByName("dps");
	auto LevelUp = (Button*)m_layer->getChildByName("up");
	auto arStone = (TextBMFont*)LevelUp->getChildByName("linghunshi");

	head->setTexture(StringUtils::format("ui/downUi/artifact/%d.png", m_id+1));
	name->setString("");
	level->setString("");
	effect->setString("");
	dps->setString("");
	arStone->setString("");

	LevelUp->addTouchEventListener([this](Ref* Sender, Widget::TouchEventType event)
	{
		if (event == Widget::TouchEventType::ENDED)
		{

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
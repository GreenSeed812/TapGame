#include "MainScene/ServantButton.h"
#include "ui/CocosGUI.h"
#include <cocostudio/CocoStudio.h> 
#include "SaveData/PlayerData.h"
#include "SaveData/ArtifactData.h"
#include "Tool/SqLite.h"
#include "ServantInfo.h"
using namespace ui;

Node* ServantButton::g_lv = nullptr;
Node * ServantButton::g_node = nullptr;

bool ServantButton::init()
{
	if (!Layer::init())
	{
		return false;
	}

    node = CSLoader::createNode("servantNode.csb");
	m_layer = (Layer*)node->getChildByName("Layer");
	this->setContentSize(node->getContentSize());	
	this->addChild(node);

	return true;
}

void ServantButton::initServantLayer(int id)
{
	CCNotificationCenter::getInstance()->addObserver(this, callfuncO_selector(ServantButton::coinChange), "CoinChange", nullptr);
	
	m_id = id;
	m_state = false;
	m_clickState = false;
	m_skillcount = PlayerData::getInstance()->getServantSkillNum(m_id);

	for (size_t i = 0; i <= m_skillcount; i++)
	{
		Sprite* skillSprite = (Sprite*)m_layer->getChildByName("discribe")->getChildByName(StringUtils::format("skill%d",i + 1));
		skillSprite->setVisible(true);
	}

	auto bt = (Button*)m_layer->getChildByName("up");
	auto up10 = (Button*)m_layer->getChildByName("up10");
	auto up100 = (Button*)m_layer->getChildByName("up100");
	auto dps = (TextBMFont*)m_layer->getChildByName("up")->getChildByName("dps");
	auto gold = (TextBMFont*)m_layer->getChildByName("up")->getChildByName("gold");
	auto head = (Button*)m_layer->getChildByName("serHead");
	auto name = (Text*)m_layer->getChildByName("discribe")->getChildByName("name");

	up10->setVisible(false);
	up100->setVisible(false);
	dps->setString(Ruler::getInstance()->showNum(PlayerData::getInstance()->getservantLevelUpDps(m_id)));
	gold->setString(Ruler::getInstance()->showNum(PlayerData::getInstance()->getservantLevelUpGold(m_id)));
	head->loadTextureNormal(StringUtils::format("ui/downUi/servant/head/%d.png",id+1));
	head->loadTexturePressed(StringUtils::format("ui/downUi/servant/head/%d.png", id + 1));
	name->setString(SqLite::getInstance()->getServantNameByID(m_id));

	for (int skillNum = 1; skillNum < 8; skillNum++)
	{
		Sprite* skillSprite = (Sprite*)m_layer->getChildByName("discribe")->getChildByName(StringUtils::format("skill%d", skillNum));
		skillSprite->setTexture(StringUtils::format("ui/downUi/servant/skill/%d/%d.png", id + 1, skillNum));
		skillSprite->setVisible(false);
	}

	bt->addTouchEventListener([this](Ref* Sender, Widget::TouchEventType Event){
		if (Event == Widget::TouchEventType::ENDED)
		{
			if (m_state)
			{			
				unLockSkill();
			}
			else
			{
				oneUp();			
			}	
			upLevel();
			cocos2d::CCNotificationCenter::getInstance()->postNotification("CoinChange");
		}
	});

	up10->addTouchEventListener([this](Ref* Sender, Widget::TouchEventType Event){
		if (Event == Widget::TouchEventType::ENDED)
		{
			for (int i = 0; i < 10; i++)
			{
				oneUp();
			}
			upLevel();
			cocos2d::CCNotificationCenter::getInstance()->postNotification("CoinChange");
		}
	});

	up100->addTouchEventListener([this](Ref* Sender, Widget::TouchEventType Event){
		if (Event == Widget::TouchEventType::ENDED)
		{
			for (int i = 0; i < 100; i++)
			{
				oneUp();
			}
			upLevel();
			cocos2d::CCNotificationCenter::getInstance()->postNotification("CoinChange");
		}
	});

	head->addTouchEventListener([this](Ref* Sender, Widget::TouchEventType Event){
		if (Event == Widget::TouchEventType::ENDED)
		{
			auto serInfo = ServantInfo::create();
			serInfo->initServantInfo(m_id);
			g_node->addChild(serInfo);
		}
	});

	coinChange(this);
}


void ServantButton::coinChange(Ref*)
{
	Button* bt = (Button*)m_layer->getChildByName("up");
	Text* text = (Text*)m_layer->getChildByName("up")->getChildByName("up");
	auto gold = (TextBMFont*)m_layer->getChildByName("up")->getChildByName("gold");
	auto * dps = (TextBMFont*)m_layer->getChildByName("up")->getChildByName("dps");
	auto up10Dps = (TextBMFont*)m_layer->getChildByName("up10")->getChildByName("dps");
	auto up100Dps = (TextBMFont*)m_layer->getChildByName("up100")->getChildByName("dps");
	auto * textlv = (Text*)m_layer->getChildByName("discribe")->getChildByName("lv");
	
	gold->setString(Ruler::getInstance()->showNum(PlayerData::getInstance()->getservantLevelUpGold(m_id)));
	dps->setString(Ruler::getInstance()->showNum(PlayerData::getInstance()->getservantLevelUpDps(m_id)));
	up10Dps->setString(Ruler::getInstance()->showNum(PlayerData::getInstance()->getServantDps(m_id)));
	up100Dps->setString(Ruler::getInstance()->showNum(PlayerData::getInstance()->getServantDps(m_id)));
	textlv->setString(StringUtils::format("lv%d", PlayerData::getInstance()->getServantLevel(m_id)));

	auto golds = PlayerData::getInstance()->getGold();
	auto judge = Ruler::getInstance()->subNum(PlayerData::getInstance()->getservantLevelUpGold(m_id),*golds);

	if (Ruler::getInstance()->Zero(judge))
	{
		bt->setEnabled(true);
	}
	else
	{
		bt->setEnabled(false);
	}
	lockState();
}

void ServantButton::oneUp()
{
	if (PlayerData::getInstance()->getServantLevel(m_id) == 0)
	{
		auto newNode = ServantButton::create();
		auto frame = Widget::create();
		ListView* lv = (ListView*)g_lv;
		PlayerData::getInstance()->addServantNum();
		newNode->initServantLayer(PlayerData::getInstance()->getServantNum());
		frame->setContentSize(newNode->getContentSize());
		frame->addChild(newNode);
		lv->pushBackCustomItem(frame);
		lv->jumpToBottom();
	}

	PlayerData::getInstance()->servantLevelUp(m_id);
}

void ServantButton::upLevel()
{
	auto up10 = (Button*)m_layer->getChildByName("up10");
	auto up100 = (Button*)m_layer->getChildByName("up100");

	auto gold = PlayerData::getInstance()->getGold();
	auto judge10 = Ruler::getInstance()->subNum(PlayerData::getInstance()->getservantLevelUp10Gold(m_id),*gold);
	auto judge100 = Ruler::getInstance()->subNum(PlayerData::getInstance()->getservantLevelUp100Gold(m_id),*gold);

	if (Ruler::getInstance()->Zero(judge10))
	{
		up10->setVisible(true);
	}
	if (Ruler::getInstance()->Zero(judge100))
	{
		up100->setVisible(true);
	}

	auto action = Sequence::create(DelayTime::create(5), CallFuncN::create(CC_CALLBACK_1(ServantButton::callbackSer, this)), nullptr);
	up10->runAction(action);
	up100->runAction(action);
}

void ServantButton::callbackSer(Node * node)
{
	auto up10 = (Button*)m_layer->getChildByName("up10");
	auto up100 = (Button*)m_layer->getChildByName("up100");
	if (up10->isVisible())
	{
		up10->setVisible(false);
	}
	if (up100->isVisible())
	{
		up100->setVisible(false);
	}
}

void ServantButton::lockState()
{
	Button* bt = (Button*)m_layer->getChildByName("up");
	Text* text = (Text*)m_layer->getChildByName("up")->getChildByName("up");
	auto * dps = (TextBMFont*)m_layer->getChildByName("up")->getChildByName("dps");
	auto level = PlayerData::getInstance()->getServantLevel(m_id);

	auto goldText = (TextBMFont*)m_layer->getChildByName("up")->getChildByName("gold");
	auto strings = FileUtils::getInstance()->getValueMapFromFile("fonts/skillState.xml");
	if (level >= SqLite::getInstance()->m_servantUnlock.at(PlayerData::getInstance()->getServantSkillNum(m_id)))
	{
		auto gold = PlayerData::getInstance()->getServantUnlockGold(m_id, PlayerData::getInstance()->getServantSkillNum(m_id) + 1);
		auto judge = Ruler::getInstance()->Zero(Ruler::getInstance()->subNum(gold, *PlayerData::getInstance()->getGold()));
		if (judge)
		{
			m_state = true;
			text->setString(strings["unLock"].asString());
			goldText->setString(Ruler::getInstance()->showNum(gold));
			bt->loadTextureNormal("ui/downUi/servant/anniu2.png");
			bt->loadTexturePressed("ui/downUi/servant/anniu2.png");
		}
		else
		{
			goldText->setString(Ruler::getInstance()->showNum(gold));
			bt->setEnabled(false);
		}
	}
}

void ServantButton::unLockSkill()
{
	auto bt = (Button*)m_layer->getChildByName("up");
	auto text = (Text*)m_layer->getChildByName("up")->getChildByName("up");
	auto strings = FileUtils::getInstance()->getValueMapFromFile("fonts/skillState.xml");
	Sprite* skillSprite = (Sprite*)m_layer->getChildByName("discribe")->getChildByName(StringUtils::format("skill%d", PlayerData::getInstance()->getServantSkillNum(m_id) + 1));

	text->setString(strings["upLevel"].asString());
	bt->loadTextureNormal("ui/downUi/servant/anniu1.png");
	bt->loadTexturePressed("ui/downUi/servant/anniu1.png");
	PlayerData::getInstance()->unlockSernantSkill(m_id, PlayerData::getInstance()->getServantSkillNum(m_id));

	skillSprite->setVisible(true);
	m_state = false;
	m_clickState = false;
}
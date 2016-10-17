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
	m_count = 0;
	m_state = false;
	m_clickState = false;

	auto bt = (Button*)m_layer->getChildByName("up");
	auto up10 = (Button*)m_layer->getChildByName("up10");
	auto up100 = (Button*)m_layer->getChildByName("up100");
	auto dps = (TextBMFont*)m_layer->getChildByName("up")->getChildByName("dps");
	auto gold = (TextBMFont*)m_layer->getChildByName("up")->getChildByName("gold");
	auto head = (Button*)m_layer->getChildByName("serHead");
	auto name = (Text*)m_layer->getChildByName("discribe")->getChildByName("name");
	auto dps1 = (TextBMFont*)m_layer->getChildByName("discribe")->getChildByName("dps");

	up10->setVisible(false);
	up100->setVisible(false);
	dps->setString(Ruler::getInstance()->showNum(PlayerData::getInstance()->getservantLevelUpDps(m_id)));
	gold->setString(Ruler::getInstance()->showNum(PlayerData::getInstance()->getservantLevelUpGold(m_id)));
	head->loadTextureNormal(StringUtils::format("ui/downUi/servant/head/%d.png",id+1));
	head->loadTexturePressed(StringUtils::format("ui/downUi/servant/head/%d.png", id + 1));
	name->setString(SqLite::getInstance()->getServantNameByID(m_id));
	dps1->setString(Ruler::getInstance()->showNum(PlayerData::getInstance()->getServantDps(m_id)));

	for (int skillNum = 1; skillNum < 8; skillNum++)
	{
		Sprite* skillSprite = (Sprite*)m_layer->getChildByName("discribe")->getChildByName(StringUtils::format("skill%d", skillNum));
		skillSprite->setTexture(StringUtils::format("ui/downUi/servant/skill/%d/%d.png", id + 1, skillNum).c_str());
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
				upLevel();
			}		
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

	auto skillNum = PlayerData::getInstance()->getServantSkillNum(m_id);
	if (skillNum >= 7)
	{
		skillNum = 7;
	}
	for (size_t i = 0; i < skillNum; i++)
	{
		auto skillSprite = (Sprite*)m_layer->getChildByName("discribe")->getChildByName(StringUtils::format("skill%d", i + 1));
		skillSprite->setVisible(true);
	}

	coinChange(this);
}


void ServantButton::coinChange(Ref*)
{
	Button* bt = (Button*)m_layer->getChildByName("up");
	Text* text = (Text*)m_layer->getChildByName("up")->getChildByName("up");
	auto gold = (TextBMFont*)m_layer->getChildByName("up")->getChildByName("gold");
	auto dps = (TextBMFont*)m_layer->getChildByName("up")->getChildByName("dps");
	auto up10Dps = (TextBMFont*)m_layer->getChildByName("up10")->getChildByName("dps");
	auto up100Dps = (TextBMFont*)m_layer->getChildByName("up100")->getChildByName("dps");
	auto textlv = (Text*)m_layer->getChildByName("discribe")->getChildByName("lv");
	auto dps1 = (TextBMFont*)m_layer->getChildByName("discribe")->getChildByName("dps");
	auto up10 = (Button*)m_layer->getChildByName("up10");
	auto up100 = (Button*)m_layer->getChildByName("up100");

	gold->setString(Ruler::getInstance()->showNum(PlayerData::getInstance()->getservantLevelUpGold(m_id)));
	dps->setString(StringUtils::format("+%s",Ruler::getInstance()->showNum(PlayerData::getInstance()->getservantLevelUpDps(m_id)).c_str()).c_str());
	up10Dps->setString(Ruler::getInstance()->showNum(PlayerData::getInstance()->getservantLevelUp10Dps(m_id)));
	up100Dps->setString(Ruler::getInstance()->showNum(PlayerData::getInstance()->getservantLevelUp100Dps(m_id)));
	textlv->setString(StringUtils::format("lv%d", PlayerData::getInstance()->getServantLevel(m_id)));
	dps1->setString(Ruler::getInstance()->showNum(PlayerData::getInstance()->getServantDps(m_id)));

	auto golds = PlayerData::getInstance()->getGold();
	auto judge = Ruler::getInstance()->subNum(PlayerData::getInstance()->getservantLevelUpGold(m_id),*golds);

	if (Ruler::getInstance()->Zero(judge))
	{
		bt->setEnabled(true);
	}
	else
	{
		bt->setEnabled(false);
		up10->setVisible(false);
		up100->setVisible(false);
	}
	lockState();
}

void ServantButton::oneUp()
{
	if (PlayerData::getInstance()->getServantLevel(m_id) == 0)
	{
		if (m_id < 32)
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
			newNode->node->getChildByName("Layer")->getChildByName("headbg")->setColor(Color3B(96, 96, 96));
			newNode->node->getChildByName("Layer")->getChildByName("discribe")->setColor(Color3B(96, 96, 96));
			this->node->getChildByName("Layer")->getChildByName("headbg")->setColor(Color3B(255, 255, 255));
			this->node->getChildByName("Layer")->getChildByName("discribe")->setColor(Color3B(255, 255, 255));
		}
	}
	PlayerData::getInstance()->servantLevelUp(m_id);
}

void ServantButton::upLevel()
{
	auto up10 = (Button*)m_layer->getChildByName("up10");
	auto up100 = (Button*)m_layer->getChildByName("up100");
	auto gold = PlayerData::getInstance()->getGold();
	auto judge = Ruler::getInstance()->subNum(PlayerData::getInstance()->getservantLevelUpGold(m_id), *gold);
	auto judge10 = Ruler::getInstance()->subNum(PlayerData::getInstance()->getservantLevelUp10Gold(m_id),*gold);
	auto judge100 = Ruler::getInstance()->subNum(PlayerData::getInstance()->getservantLevelUp100Gold(m_id), *gold);
	auto action = Sequence::create(DelayTime::create(4), CallFuncN::create(CC_CALLBACK_1(ServantButton::callbackSer, this)), nullptr);
	if (Ruler::getInstance()->Zero(judge))
	{
		if (Ruler::getInstance()->Zero(judge10))
		{
			up10->runAction(Show::create());
			up10->runAction(action);
			if (Ruler::getInstance()->Zero(judge100))
			{
				up100->setVisible(Show::create());
				up100->runAction(action);
			}
			else
			{
				up100->setVisible(false);
				up100->stopAction(action);
			}
		}
		else
		{
			up10->setVisible(false);
			up100->setVisible(false);
			up10->stopAction(action);
			up100->stopAction(action);
		}
	}
	else
	{
		up10->setVisible(false);
		up100->setVisible(false);
		up10->stopAction(action);
		up100->stopAction(action);
	}
	m_count++;
}

void ServantButton::callbackSer(Node * node)
{
	m_count--;
	auto up10 = (Button*)m_layer->getChildByName("up10");
	auto up100 = (Button*)m_layer->getChildByName("up100");
	if (m_count <= 0)
	{
		if (up10->isVisible())
		{
			up10->runAction(Hide::create());
		}
		if (up100->isVisible())
		{
			up100->runAction(Hide::create());
		}
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
	auto skillNum = PlayerData::getInstance()->getServantSkillNum(m_id);
	if (skillNum >= 7)
	{
		skillNum = 6;
	}
	if (level >= SqLite::getInstance()->m_servantUnlock.at(skillNum) && PlayerData::getInstance()->getServantSkillNum(m_id)<7)
	{
		auto gold = PlayerData::getInstance()->getServantUnlockGold(m_id, PlayerData::getInstance()->getServantSkillNum(m_id));
		auto judge = Ruler::getInstance()->Zero(Ruler::getInstance()->subNum(gold, *PlayerData::getInstance()->getGold()));
		if (judge)
		{
			m_state = true;
			text->setString(strings["unLock"].asString());
			goldText->setString(Ruler::getInstance()->showNum(gold));
			bt->loadTextureNormal("ui/downUi/servant/anniu2.png");
			bt->loadTexturePressed("ui/downUi/servant/anniu2.png");
			bt->setEnabled(true);
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
	auto skillNum = PlayerData::getInstance()->getServantSkillNum(m_id);
	Sprite* skillSprite = (Sprite*)m_layer->getChildByName("discribe")->getChildByName(StringUtils::format("skill%d",skillNum+1 ));

	text->setString(strings["upLevel"].asString());
	bt->loadTextureNormal("ui/downUi/servant/anniu1.png");
	bt->loadTexturePressed("ui/downUi/servant/anniu1.png");
	PlayerData::getInstance()->unlockSernantSkill(m_id, PlayerData::getInstance()->getServantSkillNum(m_id));

	skillSprite->setVisible(true);
	m_state = false;
	m_clickState = false;
}
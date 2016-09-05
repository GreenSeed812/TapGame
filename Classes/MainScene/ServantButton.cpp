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

	auto bt = (Button*)m_layer->getChildByName("up");
	auto up10 = (Button*)m_layer->getChildByName("up10");
	auto up100 = (Button*)m_layer->getChildByName("up100");
	auto dps = (TextBMFont*)m_layer->getChildByName("up")->getChildByName("dps");
	auto gold = (TextBMFont*)m_layer->getChildByName("up")->getChildByName("gold");
	auto head = (Sprite*)m_layer->getChildByName("serHead");
	auto name = (Text*)m_layer->getChildByName("discribe")->getChildByName("name");

	up10->setVisible(false);
	up100->setVisible(false);
	dps->setString(Ruler::getInstance()->showNum(PlayerData::getInstance()->getservantLevelUpDps(m_id)));
	gold->setString(Ruler::getInstance()->showNum(PlayerData::getInstance()->getservantLevelUpGold(m_id)));
	head->setTexture(StringUtils::format("ui/downUi/servant/head/%d.png",id+1));
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
			oneUp();
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

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(ServantButton::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(ServantButton::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

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
}

bool ServantButton::onTouchBegan(Touch * touch, Event* event)
{
	return true;
}
void ServantButton::onTouchEnded(Touch * touch, Event * event)
{
	auto pos = this->convertTouchToNodeSpace(touch);
	auto head = (Sprite*)m_layer->getChildByName("serHead");
	if (head->getBoundingBox().containsPoint(pos))
	{
		auto serInfo = ServantInfo::create();
		serInfo->initServantInfo(m_id);
		g_node->addChild(serInfo);
	}
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

	/*auto skillSprite = (Sprite*)m_layer->getChildByName("discribe")->getChildByName(StringUtils::format("skill%d", m_skillCount + 1));
	skillSprite->setVisible(true);
	auto goldNum = Ruler::getInstance()->multiplay(m_gold, 5);
	PlayerData::getInstance()->subGold(&goldNum);
	PlayerData::getInstance()->unlockSernantSkill(m_id, m_skillCount);*/

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
		up100->setVisible(false);
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

void ServantButton::unLockSkill()
{
	Button* bt = (Button*)m_layer->getChildByName("up");
	Text* text = (Text*)m_layer->getChildByName("up")->getChildByName("up");
	Sprite* skillSprite = (Sprite*)m_layer->getChildByName("discribe")->getChildByName(StringUtils::format("skill%d", m_skillcount + 1));
	bt->loadTextureNormal("ui/downUi/servant/anniu1.png");
	bt->loadTexturePressed("ui/downUi/servant/anniu1.png");
	text->setString(m_skills.at(m_skillcount)->getText());
}
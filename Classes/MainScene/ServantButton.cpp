#include "MainScene/ServantButton.h"
#include "ui/CocosGUI.h"
#include <cocostudio/CocoStudio.h> 
#include "SaveData/PlayerData.h"
#include "Tool/SqLite.h"
using namespace ui;
Node* ServantButton::g_lv = nullptr;
bool ServantButton::init()
{
	if (!Layer::init())
	{
		return false;
	}
	m_unlock = false;
	m_lock = true;
	m_locked = true;
	m_skillCount = 0;
	m_lockCount = 0;
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
	m_baseDps = SqLite::getInstance()->getServantDpsByID(m_id);
	m_gold = SqLite::getInstance()->getServantGoldByID(m_id);
	Button* bt = (Button*)m_layer->getChildByName("up");
	TextBMFont* dps = (TextBMFont*)m_layer->getChildByName("up")->getChildByName("dps");
	TextBMFont* gold = (TextBMFont*)m_layer->getChildByName("up")->getChildByName("gold");
	dps->setString(Ruler::getInstance()->showNum(m_baseDps));
	gold->setString(Ruler::getInstance()->showNum(m_gold));
	Sprite *head = (Sprite*)m_layer->getChildByName("head");
	head->setTexture(StringUtils::format("ui/downUi/servant/head/%d.png",id+1));
	for (int skillNum = 1; skillNum < 8; skillNum++)
	{
		Sprite* skillSprite = (Sprite*)m_layer->getChildByName("discribe")->getChildByName(StringUtils::format("skill%d", skillNum));
		skillSprite->setTexture(StringUtils::format("ui/downUi/servant/skill/%d/%d.png", id + 1, skillNum));
		skillSprite->setVisible(false);
	}
	Text* name = (Text*)m_layer->getChildByName("discribe")->getChildByName("name");
	name->setString(SqLite::getInstance()->getServantNameByID(m_id));
	bt->addTouchEventListener([this](Ref* Sender, Widget::TouchEventType Event){
		if (Event == Widget::TouchEventType::ENDED)
		{
			if (!m_unlock)
			{
				if (PlayerData::getInstance()->getServantLevel(m_id) == 0)
				{
					auto newNode = ServantButton::create();
					PlayerData::getInstance()->addServantNum();
					newNode->initServantLayer(PlayerData::getInstance()->getServantNum());
					auto frame = Widget::create();
					frame->setContentSize(newNode->getContentSize());
					frame->addChild(newNode);
					ListView* lv = (ListView*)g_lv;
					lv->pushBackCustomItem(frame);
				}

				PlayerData::getInstance()->servantLevelUp(m_id);
				PlayerData::getInstance()->subGold(&m_gold);

				auto i = PlayerData::getInstance()->getServantLevel(m_id);
				auto pow1 = pow(PlayerData::getInstance()->getServantLevel(m_id) + 1, 0.7);
				auto pow2 = pow(PlayerData::getInstance()->getServantLevel(m_id) + 1, 6);
				auto mul = 1 + 1 / pow1 - 1 / pow2;

				PlayerData::getInstance()->setServantBaseDps(m_baseDps, m_id);
				m_baseDps = Ruler::getInstance()->multiplay(m_baseDps, mul);
				mul = 1 + 1 / (pow(PlayerData::getInstance()->getServantLevel(m_id) + 1, 0.45) - 1 / pow(PlayerData::getInstance()->getServantLevel(m_id) + 1, 6.13));			
				m_gold = Ruler::getInstance()->multiplay(m_gold, mul);
				TextBMFont* gold = (TextBMFont*)m_layer->getChildByName("up")->getChildByName("gold");
				gold->setString(Ruler::getInstance()->showNum(m_gold));
				TextBMFont* dps = (TextBMFont*)m_layer->getChildByName("up")->getChildByName("dps");			
				dps->setString(Ruler::getInstance()->showNum(m_baseDps));
				Text* textlv = (Text*)m_layer->getChildByName("discribe")->getChildByName("lv");
				textlv->setString(StringUtils::format("lv%d", PlayerData::getInstance()->getServantLevel(m_id)));
				for (auto level : SqLite::getInstance()->m_servantUnlock)
				{
					if (PlayerData::getInstance()->getServantLevel(m_id) == level)
					{
						m_unlock = true;
						m_lock = false;
						m_lockCount++;
						Button* bt = (Button*)m_layer->getChildByName("up");
						bt->loadTextureNormal("ui/downUi/servant/anniu2.png");
						bt->loadTexturePressed("ui/downUi/servant/anniu2.png");
						Text* text = (Text*)m_layer->getChildByName("up")->getChildByName("up");
						text->setString(StringUtils::format("%s", "解锁").c_str());
						gold->setString(Ruler::getInstance()->showNum(Ruler::getInstance()->multiplay(m_gold, 5)));
					}
				}
			}
			else
			{
				//技能解锁
				Sprite* skillSprite = (Sprite*)m_layer->getChildByName("discribe")->getChildByName(StringUtils::format("skill%d", m_skillCount + 1));
				skillSprite->setVisible(true);
				PlayerData::getInstance()->subGold(&Ruler::getInstance()->multiplay(m_gold, 5));
				PlayerData::getInstance()->unlockSernantSkill(m_id, m_skillCount);
				m_skillCount++;
				m_unlock = false;
				m_lock = true;
			}

			coinChange(this);
		}
	});
	coinChange(this);
}


void ServantButton::coinChange(Ref*)
{
	Button* bt = (Button*)m_layer->getChildByName("up");
	MyNum judge;

	if (!m_lock)
	{	
		judge = Ruler::getInstance()->subNum(Ruler::getInstance()->multiplay(m_gold, 5), *PlayerData::getInstance()->getGold());
	}
	else
	{
		TextBMFont* gold = (TextBMFont*)m_layer->getChildByName("up")->getChildByName("gold");
		gold->setString(Ruler::getInstance()->showNum(m_gold));
		judge = Ruler::getInstance()->subNum(m_gold, *PlayerData::getInstance()->getGold());
		bt->loadTextureNormal("ui/downUi/servant/anniu1.png");
		bt->loadTexturePressed("ui/downUi/servant/anniu1.png");
		Text* text = (Text*)m_layer->getChildByName("up")->getChildByName("up");
		//text->setString(StringUtils::);
	}

	if (Ruler::getInstance()->Zero(judge))
	{
		bt->setEnabled(true);
		m_layer->setColor(Color3B(255, 255, 255));
	}
	else
	{
		bt->setEnabled(false);
	}
}

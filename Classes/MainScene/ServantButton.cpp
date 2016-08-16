#include "MainScene/ServantButton.h"
#include "ui/CocosGUI.h"
#include <cocostudio\CocoStudio.h> 
#include "SaveData\PlayerData.h"
#include "Tool\SqLite.h"
using namespace ui;
Node* ServantButton::g_lv = nullptr;
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
	m_baseDps = SqLite::getInstance()->getServantDpsByID(m_id);
	m_gold = SqLite::getInstance()->getServantGoldByID(m_id);
	Button* bt = (Button*)m_layer->getChildByName("up");
	Text* dps = (Text*)m_layer->getChildByName("up")->getChildByName("dps");
	Text* gold = (Text*)m_layer->getChildByName("up")->getChildByName("gold");
	dps->setString(Ruler::getInstance()->showNum(&m_baseDps));
	gold->setString(Ruler::getInstance()->showNum(&m_gold));
	bt->addTouchEventListener([&](Ref* Sender, Widget::TouchEventType Event){
		if (Event == Widget::TouchEventType::ENDED)
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
			auto pow1 = pow(PlayerData::getInstance()->getServantLevel(m_id)+1, 0.7);
			auto pow2 = pow(PlayerData::getInstance()->getServantLevel(m_id)+1, 6);
			auto mul = 1 + 1 / pow1 - 1 / pow2;
			PlayerData::getInstance()->setServantBaseDps(m_baseDps, m_id);
			m_baseDps = Ruler::getInstance()->multiplay(&m_baseDps, mul);			
			mul = 1 + 1 / (pow(PlayerData::getInstance()->getServantLevel(m_id)+1, 0.45) - 1 / pow(PlayerData::getInstance()->getServantLevel(m_id)+1, 6.13));
			m_gold = Ruler::getInstance()->multiplay(&m_gold, mul);
			Text* dps = (Text*)m_layer->getChildByName("up")->getChildByName("dps");
			Text* gold = (Text*)m_layer->getChildByName("up")->getChildByName("gold");
			dps->setString(Ruler::getInstance()->showNum(&m_baseDps));
			gold->setString(Ruler::getInstance()->showNum(&m_gold));
			Text* textlv = (Text*)m_layer->getChildByName("discribe")->getChildByName("lv");
			textlv->setString(StringUtils::format("lv%d",PlayerData::getInstance()->getServantLevel(m_id)));
			coinChange(this);
		}
	});
	coinChange(this);
}
void ServantButton::update(float dt)
{
	

}
void ServantButton::coinChange(Ref*)
{
	Button* bt = (Button*)m_layer->getChildByName("up");
	auto judge = Ruler::getInstance()->subNum(&m_gold, PlayerData::getInstance()->getGold());
	if (Ruler::getInstance()->Zero(&judge))
	{
		bt->setEnabled(true);
		m_layer->setColor(ccc3(255, 255, 255));
	}
	else
	{
		bt->setEnabled(false);
	}
}
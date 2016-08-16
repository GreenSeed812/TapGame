#include"MainScene/PlayerButton.h"
#include "ui/CocosGUI.h"
#include <cocostudio\CocoStudio.h> 
#include "SaveData/PlayerData.h"
#include "Tool\SqLite.h"
#include "Tool/Rule.h"
using namespace ui;
bool PlayerButton::init()
{
	if (!Layer::init())
	{
		return false;
	}
	playerLayer = CSLoader::createNode("downUiButtonLayer.csb");
	this->setContentSize(playerLayer->getContentSize());
	this->addChild(playerLayer);
	return true;
}
void PlayerButton::initPlayerButton(BUTTONTYPE type)
{

	CCNotificationCenter::getInstance()->addObserver(this, callfuncO_selector(PlayerButton::coinChange), "CoinChange", nullptr);

	

	m_type = type;
	if (type == PLAYER)
	{
		Button* bt = (Button*)playerLayer->getChildByName("Layer")->getChildByName("up");
	    Sprite* sp = (Sprite*)playerLayer->getChildByName("Layer")->getChildByName("head");
		sp->setTexture("ui/downUi/hero/heroHead0.png");
		lblv = Label::create();
		lblv->setScale(4); 
		lblv->setPosition(Vec2(450,100));
		this->addChild(lblv);
		lbdps = Label::create();
		lbdps->setPosition(Vec2(450, 50));
		lbdps->setScale(4);
		this->addChild(lbdps);
		m_upGold = SqLite::getInstance()->getGold();
		bt->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
			if (type == Widget::TouchEventType::ENDED)
			{
				PlayerData::getInstance()->heroLevelUp();
				lbdps->setString(Ruler::getInstance()->showNum(&PlayerData::getInstance()->getDps()));
				lblv->setString(StringUtils::format("lv%d", PlayerData::getInstance()->getPlayerLevel()));
				PlayerData::getInstance()->subGold(&m_upGold);
				double playerLevel = PlayerData::getInstance()->getPlayerLevel();
				auto mul = 1 / pow(playerLevel, 0.55) - 1 / pow(playerLevel, 1.03) + 1;
				m_upGold = Ruler::getInstance()->multiplayUp(&m_upGold, mul) ;
				coinChange(this);
			}
		});
	}
	else if (type == SKILL1)
	{
		Button* bt = (Button*)playerLayer->getChildByName("Layer")->getChildByName("up");
		Sprite* sp = (Sprite*)playerLayer->getChildByName("Layer")->getChildByName("head");
		sp->setTexture("ui/downUi/hero/heroHead1.png");
		m_upGold = SqLite::getInstance()->getGoldByID(1);
		
		bt->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
			if (type == Widget::TouchEventType::ENDED)
			{
				m_upGold = Ruler::getInstance()->multiplay(&m_upGold, 50);
				PlayerData::getInstance()->skillLevelUp(1);

			}
		});
	}
	else if (type == SKILL2)
	{
		Button* bt = (Button*)playerLayer->getChildByName("Layer")->getChildByName("up");
		Sprite* sp = (Sprite*)playerLayer->getChildByName("Layer")->getChildByName("head");
		sp->setTexture("ui/downUi/hero/heroHead2.png");
		m_upGold = SqLite::getInstance()->getGoldByID(2);
		bt->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
			if (type == Widget::TouchEventType::ENDED)
			{
				m_upGold = Ruler::getInstance()->multiplay(&m_upGold, 50);
				PlayerData::getInstance()->skillLevelUp(2);
			}
		});
	}
	else if (type == SKILL3)
	{
		Button* bt = (Button*)playerLayer->getChildByName("Layer")->getChildByName("up");
		Sprite* sp = (Sprite*)playerLayer->getChildByName("Layer")->getChildByName("head");
		sp->setTexture("ui/downUi/hero/heroHead3.png");
		m_upGold = SqLite::getInstance()->getGoldByID(3);
		bt->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
			if (type == Widget::TouchEventType::ENDED)
			{
				m_upGold = Ruler::getInstance()->multiplay(&m_upGold, 50);
				PlayerData::getInstance()->skillLevelUp(3);
			}
		});
	}
	else if (type == SKILL4)
	{
		Button* bt = (Button*)playerLayer->getChildByName("Layer")->getChildByName("up");
		Sprite* sp = (Sprite*)playerLayer->getChildByName("Layer")->getChildByName("head");
		sp->setTexture("ui/downUi/hero/heroHead4.png");
		m_upGold = SqLite::getInstance()->getGoldByID(4);
		bt->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
			if (type == Widget::TouchEventType::ENDED)
			{
				m_upGold = Ruler::getInstance()->multiplay(&m_upGold, 50);
				PlayerData::getInstance()->skillLevelUp(4);
			}
		});
	}
	else if (type == SKILL5)
	{
		Button* bt = (Button*)playerLayer->getChildByName("Layer")->getChildByName("up");
		Sprite* sp = (Sprite*)playerLayer->getChildByName("Layer")->getChildByName("head");
		sp->setTexture("ui/downUi/hero/heroHead5.png");
		m_upGold = SqLite::getInstance()->getGoldByID(5);
		bt->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
			if (type == Widget::TouchEventType::ENDED)
			{
				m_upGold = Ruler::getInstance()->multiplay(&m_upGold, 50);
				PlayerData::getInstance()->skillLevelUp(5);
			}
		});
	}
	else if (type == SKILL6)
	{
		Button* bt = (Button*)playerLayer->getChildByName("Layer")->getChildByName("up");
		Sprite* sp = (Sprite*)playerLayer->getChildByName("Layer")->getChildByName("head");
		sp->setTexture("ui/downUi/hero/heroHead6.png");
		m_upGold = SqLite::getInstance()->getGoldByID(6);
		bt->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
			if (type == Widget::TouchEventType::ENDED)
			{
				m_upGold = Ruler::getInstance()->multiplay(&m_upGold, 50);
				PlayerData::getInstance()->skillLevelUp(6);
			}
		});
	}
	else if (type == RELIFE)
	{
		Button* bt = (Button*)playerLayer->getChildByName("Layer")->getChildByName("up");
		Sprite* sp = (Sprite*)playerLayer->getChildByName("Layer")->getChildByName("head");
		sp->setTexture("ui/downUi/hero/heroHead7.png");
		bt->setEnabled("false");
		bt->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
			if (type == Widget::TouchEventType::ENDED)
			{

			}
		});
	}
	coinChange(this);
}
void PlayerButton::update(float dt)
{
	
}

void PlayerButton::coinChange(Ref* pSender)
{
	Text* lb = (Text*)playerLayer->getChildByName("Layer")->getChildByName("up")->getChildByName("needGold");
	
	Text* text = (Text*)playerLayer->getChildByName("Layer")->getChildByName("discribe")->getChildByName("text");
	Text* textD = (Text*)playerLayer->getChildByName("Layer")->getChildByName("discribe")->getChildByName("textD");
	Button* bt = (Button*)playerLayer->getChildByName("Layer")->getChildByName("up");
	auto judge = Ruler::getInstance()->subNum(&m_upGold, PlayerData::getInstance()->getGold());
	if (Ruler::getInstance()->Zero(&judge))
	{

		bt->setEnabled(true);
	}
	else
	{
		bt->setEnabled(false);
	}
	if (m_type == PLAYER)
	{
		text->setString(StringUtils::format("lv%d", PlayerData::getInstance()->getPlayerLevel()));

	}
	else if (m_type == SKILL1)
	{
		text->setString(StringUtils::format("lv%d", PlayerData::getInstance()->getSkillLevel(m_type - 1)));
		auto eff = SqLite::getInstance()->getEff(m_type - 1) + SqLite::getInstance()->getEffPer(m_type - 1) * PlayerData::getInstance()->getSkillLevel(m_type - 1);
		textD->setString(StringUtils::format(SqLite::getInstance()->getSkillDis(m_type - 1).c_str(), eff));
	}
	else if (m_type == SKILL2)
	{
		text->setString(StringUtils::format("lv%d", PlayerData::getInstance()->getSkillLevel(m_type - 1)));
		auto eff = SqLite::getInstance()->getEff(m_type - 1) + SqLite::getInstance()->getEffPer(m_type - 1) * PlayerData::getInstance()->getSkillLevel(m_type - 1);
		textD->setString(StringUtils::format(SqLite::getInstance()->getSkillDis(m_type - 1).c_str(), eff));
	}
	else if (m_type == SKILL3)
	{
		text->setString(StringUtils::format("lv%d", PlayerData::getInstance()->getSkillLevel(m_type - 1)));
		auto eff = SqLite::getInstance()->getEff(m_type - 1) + SqLite::getInstance()->getEffPer(m_type - 1) * PlayerData::getInstance()->getSkillLevel(m_type - 1);
		textD->setString(StringUtils::format(SqLite::getInstance()->getSkillDis(m_type - 1).c_str(), eff));
	}
	else if (m_type == SKILL4)
	{
		text->setString(StringUtils::format("lv%d", PlayerData::getInstance()->getSkillLevel(m_type - 1)));
		auto eff = SqLite::getInstance()->getEff(m_type - 1) + SqLite::getInstance()->getEffPer(m_type - 1) * PlayerData::getInstance()->getSkillLevel(m_type - 1);
		textD->setString(StringUtils::format(SqLite::getInstance()->getSkillDis(m_type - 1).c_str(), eff));
	}
	else if (m_type == SKILL5)
	{
		text->setString(StringUtils::format("lv%d", PlayerData::getInstance()->getSkillLevel(m_type - 1)));
		auto eff = SqLite::getInstance()->getEff(m_type - 1) + SqLite::getInstance()->getEffPer(m_type - 1) * PlayerData::getInstance()->getSkillLevel(m_type - 1);
		textD->setString(StringUtils::format(SqLite::getInstance()->getSkillDis(m_type - 1).c_str(), eff));
	}
	else if (m_type == SKILL6)
	{
		text->setString(StringUtils::format("lv%d", PlayerData::getInstance()->getSkillLevel(m_type - 1)));
		auto eff = SqLite::getInstance()->getEff(m_type - 1) + SqLite::getInstance()->getEffPer(m_type - 1) * PlayerData::getInstance()->getSkillLevel(m_type - 1);
		textD->setString(StringUtils::format(SqLite::getInstance()->getSkillDis(m_type - 1).c_str(), eff));
	}
	else if (m_type == RELIFE)
	{
		auto eff = SqLite::getInstance()->getEff(m_type - 1) + SqLite::getInstance()->getEffPer(m_type - 1) * PlayerData::getInstance()->getSkillLevel(m_type - 1);
		textD->setString(StringUtils::format(SqLite::getInstance()->getSkillDis(m_type - 1).c_str(), eff));
		if (PlayerData::getInstance()->getPlayerLevel() == 600)
		{
			bt->setEnabled(true);
		}
	}
	lb->setString(Ruler::getInstance()->showNum(&m_upGold));
}
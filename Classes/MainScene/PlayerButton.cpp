#include"MainScene/PlayerButton.h"
#include "ui/CocosGUI.h"
#include <cocostudio/CocoStudio.h> 
#include "SaveData/PlayerData.h"
#include "Tool/SqLite.h"
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
		
		
		m_upGold = SqLite::getInstance()->getGold();
		bt->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type){
			if (type == Widget::TouchEventType::ENDED)
			{
				PlayerData::getInstance()->heroLevelUp();
				PlayerData::getInstance()->subGold(&m_upGold);
				double playerLevel = PlayerData::getInstance()->getPlayerLevel();
				auto mul = 1 / pow(playerLevel, 0.55) - 1 / pow(playerLevel, 1.03) + 1;
				m_upGold = Ruler::getInstance()->multiplayUp(m_upGold, mul) ;
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
		
		bt->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type){
			if (type == Widget::TouchEventType::ENDED)
			{
				
				PlayerData::getInstance()->skillLevelUp(1);
				PlayerData::getInstance()->subGold(&m_upGold);
				m_upGold = Ruler::getInstance()->multiplay(m_upGold, 50);
				coinChange(this);
				
			}
		});
	}
	else if (type == SKILL2)
	{
		Button* bt = (Button*)playerLayer->getChildByName("Layer")->getChildByName("up");
		Sprite* sp = (Sprite*)playerLayer->getChildByName("Layer")->getChildByName("head");

		sp->setTexture("ui/downUi/hero/heroHead2.png");
		m_upGold = SqLite::getInstance()->getGoldByID(2);
		bt->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type){
			if (type == Widget::TouchEventType::ENDED)
			{
				PlayerData::getInstance()->subGold(&m_upGold);
				m_upGold = Ruler::getInstance()->multiplay(m_upGold, 50);
				PlayerData::getInstance()->skillLevelUp(2);
				coinChange(this);
			}
		});
	}
	else if (type == SKILL3)
	{
		Button* bt = (Button*)playerLayer->getChildByName("Layer")->getChildByName("up");
		Sprite* sp = (Sprite*)playerLayer->getChildByName("Layer")->getChildByName("head");

		sp->setTexture("ui/downUi/hero/heroHead3.png");
		m_upGold = SqLite::getInstance()->getGoldByID(3);
		bt->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type){
			if (type == Widget::TouchEventType::ENDED)
			{
				PlayerData::getInstance()->subGold(&m_upGold);
				m_upGold = Ruler::getInstance()->multiplay(m_upGold, 50);
				PlayerData::getInstance()->skillLevelUp(3);
				coinChange(this);
			}
		});
	}
	else if (type == SKILL4)
	{
		Button* bt = (Button*)playerLayer->getChildByName("Layer")->getChildByName("up");
		Sprite* sp = (Sprite*)playerLayer->getChildByName("Layer")->getChildByName("head");

		sp->setTexture("ui/downUi/hero/heroHead4.png");
		m_upGold = SqLite::getInstance()->getGoldByID(4);
		bt->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type){
			if (type == Widget::TouchEventType::ENDED)
			{
				PlayerData::getInstance()->subGold(&m_upGold);
				m_upGold = Ruler::getInstance()->multiplay(m_upGold, 50);
				PlayerData::getInstance()->skillLevelUp(4);
				coinChange(this);
			}
		});
	}
	else if (type == SKILL5)
	{
		Button* bt = (Button*)playerLayer->getChildByName("Layer")->getChildByName("up");
		Sprite* sp = (Sprite*)playerLayer->getChildByName("Layer")->getChildByName("head");

		sp->setTexture("ui/downUi/hero/heroHead5.png");
		m_upGold = SqLite::getInstance()->getGoldByID(5);
		bt->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type){
			if (type == Widget::TouchEventType::ENDED)
			{
				PlayerData::getInstance()->subGold(&m_upGold);
				m_upGold = Ruler::getInstance()->multiplay(m_upGold, 50);
				PlayerData::getInstance()->skillLevelUp(5);
				coinChange(this);
			}
		});
	}
	else if (type == SKILL6)
	{
		Button* bt = (Button*)playerLayer->getChildByName("Layer")->getChildByName("up");
		Sprite* sp = (Sprite*)playerLayer->getChildByName("Layer")->getChildByName("head");

		sp->setTexture("ui/downUi/hero/heroHead6.png");
		m_upGold = SqLite::getInstance()->getGoldByID(6);
		bt->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type){
			if (type == Widget::TouchEventType::ENDED)
			{
				PlayerData::getInstance()->subGold(&m_upGold);
				m_upGold = Ruler::getInstance()->multiplay(m_upGold, 50);
				PlayerData::getInstance()->skillLevelUp(6);
				coinChange(this);
			}
		});
	}
	else if (type == RELIFE)
	{
		Button* bt = (Button*)playerLayer->getChildByName("Layer")->getChildByName("up");
		Sprite* sp = (Sprite*)playerLayer->getChildByName("Layer")->getChildByName("head");

		sp->setTexture("ui/downUi/hero/heroHead7.png");
		bt->setEnabled("false");
		bt->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type){
			if (type == Widget::TouchEventType::ENDED)
			{

			}
		});
	}
	coinChange(this);
}

void PlayerButton::coinChange(Ref* pSender)
{
	TextBMFont* lb = (TextBMFont*)playerLayer->getChildByName("Layer")->getChildByName("up")->getChildByName("needGold");
	Text * textN = (Text *)playerLayer->getChildByName("Layer")->getChildByName("discribe")->getChildByName("textN");
	Text* text = (Text*)playerLayer->getChildByName("Layer")->getChildByName("discribe")->getChildByName("text");
	Text* textD = (Text*)playerLayer->getChildByName("Layer")->getChildByName("discribe")->getChildByName("textD");
	Button* bt = (Button*)playerLayer->getChildByName("Layer")->getChildByName("up");
	auto judge = Ruler::getInstance()->subNum(m_upGold, *PlayerData::getInstance()->getGold());
	if (Ruler::getInstance()->Zero(judge))
	{

		bt->setEnabled(true);
	}
	else
	{
		bt->setEnabled(false);
	}
	if (m_type == PLAYER)
	{
		textN->setString("Player");
		text->setString(StringUtils::format("lv%d", PlayerData::getInstance()->getPlayerLevel()));
		textD->setString(StringUtils::format("%d",PlayerData::getInstance()->getPlayerLevel()));
		
	}
	else if (m_type == SKILL1)
	{
		textN->setString(StringUtils::format("%s",SqLite::getInstance()->getSkillNameByID(0).c_str()));
		text->setString(StringUtils::format("lv%d", PlayerData::getInstance()->getSkillLevel(m_type - 1)));
		auto eff = SqLite::getInstance()->getEff(m_type - 1) + SqLite::getInstance()->getEffPer(m_type - 1) * PlayerData::getInstance()->getSkillLevel(m_type - 1);
		textD->setString(StringUtils::format(SqLite::getInstance()->getSkillDis(m_type - 1).c_str(), eff));
		if (PlayerData::getInstance()->getPlayerLevel() < 50)
		{
			bt->setEnabled(false);
		}
	}
	else if (m_type == SKILL2)
	{
		textN->setString(StringUtils::format("%s", SqLite::getInstance()->getSkillNameByID(1).c_str()));
		text->setString(StringUtils::format("lv%d", PlayerData::getInstance()->getSkillLevel(m_type - 1)));
		auto eff = SqLite::getInstance()->getEff(m_type - 1) + SqLite::getInstance()->getEffPer(m_type - 1) * PlayerData::getInstance()->getSkillLevel(m_type - 1);
		textD->setString(StringUtils::format(SqLite::getInstance()->getSkillDis(m_type - 1).c_str(), eff));

		if (PlayerData::getInstance()->getPlayerLevel() < 100)
		{
			bt->setEnabled(false);
		}
	}
	else if (m_type == SKILL3)
	{
		textN->setString(StringUtils::format("%s", SqLite::getInstance()->getSkillNameByID(2).c_str()));
		text->setString(StringUtils::format("lv%d", PlayerData::getInstance()->getSkillLevel(m_type - 1)));
		float eff = SqLite::getInstance()->getEff(m_type - 1) + SqLite::getInstance()->getEffPer(m_type - 1) * PlayerData::getInstance()->getSkillLevel(m_type - 1);
		int _eff = eff * 100;
		textD->setString(StringUtils::format(SqLite::getInstance()->getSkillDis(m_type - 1).c_str(), _eff));
		if (PlayerData::getInstance()->getPlayerLevel() < 200)
		{
			bt->setEnabled(false);
		}
	}
	else if (m_type == SKILL4)
	{
		textN->setString(StringUtils::format("%s", SqLite::getInstance()->getSkillNameByID(3).c_str()));
		text->setString(StringUtils::format("lv%d", PlayerData::getInstance()->getSkillLevel(m_type - 1)));
		auto eff = SqLite::getInstance()->getEff(m_type - 1) + SqLite::getInstance()->getEffPer(m_type - 1) * PlayerData::getInstance()->getSkillLevel(m_type - 1);
		
		textD->setString(StringUtils::format(SqLite::getInstance()->getSkillDis(m_type - 1).c_str(), eff));
		if (PlayerData::getInstance()->getPlayerLevel() < 300)
		{
			bt->setEnabled(false);
		}
	}
	else if (m_type == SKILL5)
	{
		textN->setString(StringUtils::format("%s", SqLite::getInstance()->getSkillNameByID(4).c_str()));
		text->setString(StringUtils::format("lv%d", PlayerData::getInstance()->getSkillLevel(m_type - 1)));
		float eff = SqLite::getInstance()->getEff(m_type - 1) + SqLite::getInstance()->getEffPer(m_type - 1) * PlayerData::getInstance()->getSkillLevel(m_type - 1);
		int _eff = eff * 100;
		textD->setString(StringUtils::format(SqLite::getInstance()->getSkillDis(m_type - 1).c_str(), _eff));
		if (PlayerData::getInstance()->getPlayerLevel() < 400)
		{
			bt->setEnabled(false);
		}
	}
	else if (m_type == SKILL6)
	{
		textN->setString(StringUtils::format("%s", SqLite::getInstance()->getSkillNameByID(5).c_str()));
		text->setString(StringUtils::format("lv%d", PlayerData::getInstance()->getSkillLevel(m_type - 1)));
		float eff = SqLite::getInstance()->getEff(m_type - 1) + SqLite::getInstance()->getEffPer(m_type - 1) * PlayerData::getInstance()->getSkillLevel(m_type - 1);
		int _eff = eff * 100;
		textD->setString(StringUtils::format(SqLite::getInstance()->getSkillDis(m_type - 1).c_str(), _eff));
		if (PlayerData::getInstance()->getPlayerLevel() < 500)
		{
			bt->setEnabled(false);
		}
	}
	else if (m_type == RELIFE)
	{
		textN->setString(StringUtils::format("%s", SqLite::getInstance()->getSkillNameByID(6).c_str()));
		auto eff = SqLite::getInstance()->getEff(m_type - 1) + SqLite::getInstance()->getEffPer(m_type - 1) * PlayerData::getInstance()->getSkillLevel(m_type - 1);
		textD->setString(StringUtils::format(SqLite::getInstance()->getSkillDis(m_type - 1).c_str(), eff));
		if (PlayerData::getInstance()->getPlayerLevel() < 600)
		{
			bt->setEnabled(false);
		}
	}
	lb->setString(Ruler::getInstance()->showNum(m_upGold));
}
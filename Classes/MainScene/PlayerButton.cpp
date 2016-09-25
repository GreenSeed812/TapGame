#include"MainScene/PlayerButton.h"
#include"MainScene/PlayerInfo.h"
#include"Relife.h"
#include "ui/CocosGUI.h"
#include <cocostudio/CocoStudio.h> 
#include "SaveData/PlayerData.h"
#include "Tool/SqLite.h"
#include "Tool/Rule.h"
#include "SaveData/AchieveData.h"
using namespace ui;
Node * PlayerButton::g_skillLayer = nullptr;
Node * PlayerButton::g_node = nullptr;
bool PlayerButton::init()
{
	if (!Layer::init())
	{
		return false;
	}
	m_count = 0;
	playerLayer = CSLoader::createNode("zhujiaotiao.csb");
	this->setContentSize(playerLayer->getContentSize());
	this->addChild(playerLayer);
	return true;
}
void PlayerButton::initPlayerButton(BUTTONTYPE type)
{

	CCNotificationCenter::getInstance()->addObserver(this, callfuncO_selector(PlayerButton::coinChange), "CoinChange", nullptr);

	Button* bt = (Button*)playerLayer->getChildByName("Layer")->getChildByName("up");
	Button* up10 = (Button*)playerLayer->getChildByName("Layer")->getChildByName("up10");
	Button* up100 = (Button*)playerLayer->getChildByName("Layer")->getChildByName("up100");
	auto head = (Button*)playerLayer->getChildByName("Layer")->getChildByName("playerHead");
	
	head->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			auto playerInfo = PlayerInfo::create();
			playerInfo->initPlayerInfo();
			g_node->addChild(playerInfo);
		}
	});

	up10->setVisible(false);
	up100->setVisible(false);

	m_type = type;
	if (type == PLAYER)
	{	
		m_upGold = PlayerData::getInstance()->getPlayerlvupGold();

		bt->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type){
			if (type == Widget::TouchEventType::ENDED)
			{
				upLevelCount();
				PlayerData::getInstance()->heroLevelUp();
				cocos2d::CCNotificationCenter::getInstance()->postNotification("TapDpsChange");
				cocos2d::CCNotificationCenter::getInstance()->postNotification("CoinChange");
				double playerLevel = PlayerData::getInstance()->getPlayerLevel();
				auto mul = 1 / pow(playerLevel, 0.55) - 1 / pow(playerLevel, 1.03) + 1;
				m_upGold = Ruler::getInstance()->multiplayUp(m_upGold, mul) ;
				coinChange(this);
			}
		});
		up10->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED)
			{
				for (size_t i = 0; i < 10; i++)
				{
					PlayerData::getInstance()->heroLevelUp();
					double playerLevel = PlayerData::getInstance()->getPlayerLevel();
					auto mul = 1 / pow(playerLevel, 0.55) - 1 / pow(playerLevel, 1.03) + 1;
					m_upGold = Ruler::getInstance()->multiplayUp(m_upGold, mul);
				}	
				cocos2d::CCNotificationCenter::getInstance()->postNotification("TapDpsChange");
				cocos2d::CCNotificationCenter::getInstance()->postNotification("CoinChange");
				upLevelCount();
			}
		});
		up100->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED)
			{
				for (size_t i = 0; i < 100; i++)
				{
					PlayerData::getInstance()->heroLevelUp();
					double playerLevel = PlayerData::getInstance()->getPlayerLevel();
					auto mul = 1 / pow(playerLevel, 0.55) - 1 / pow(playerLevel, 1.03) + 1;
					m_upGold = Ruler::getInstance()->multiplayUp(m_upGold, mul);
				}
				cocos2d::CCNotificationCenter::getInstance()->postNotification("TapDpsChange");
				cocos2d::CCNotificationCenter::getInstance()->postNotification("CoinChange");
				upLevelCount();
			}
		});
	}
	else if (type == SKILL1)
	{

		head->loadTextureNormal("ui/downUi/hero/heroHead1.png");
		head->loadTexturePressed("ui/downUi/hero/heroHead1.png");
		m_upGold = SqLite::getInstance()->getGoldByID(1);
		
		bt->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type){
			if (type == Widget::TouchEventType::ENDED)
			{		
				PlayerData::getInstance()->skillLevelUp(1);
				PlayerData::getInstance()->subGold(&m_upGold);
				m_upGold = Ruler::getInstance()->multiplay(m_upGold, 50);
				Button* button = (Button*)g_skillLayer->getChildByName("SkillButton1");
				button->runAction(Show::create());
				coinChange(this);			
			}
		});
	}
	else if (type == SKILL2)
	{

		head->loadTextureNormal("ui/downUi/hero/heroHead2.png");
		head->loadTexturePressed("ui/downUi/hero/heroHead2.png");
		m_upGold = SqLite::getInstance()->getGoldByID(2);
		bt->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type){
			if (type == Widget::TouchEventType::ENDED)
			{
				PlayerData::getInstance()->subGold(&m_upGold);
				m_upGold = Ruler::getInstance()->multiplay(m_upGold, 50);
				PlayerData::getInstance()->skillLevelUp(2);
				Button* button = (Button*)g_skillLayer->getChildByName("SkillButton2");
				button->runAction(Show::create());
				coinChange(this);
			}
		});
	}
	else if (type == SKILL3)
	{

		head->loadTextureNormal("ui/downUi/hero/heroHead3.png");
		head->loadTexturePressed("ui/downUi/hero/heroHead3.png");
		m_upGold = SqLite::getInstance()->getGoldByID(3);
		bt->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type){
			if (type == Widget::TouchEventType::ENDED)
			{
				PlayerData::getInstance()->subGold(&m_upGold);
				m_upGold = Ruler::getInstance()->multiplay(m_upGold, 50);
				PlayerData::getInstance()->skillLevelUp(3);
				Button* button = (Button*)g_skillLayer->getChildByName("SkillButton3");
				button->runAction(Show::create());
				coinChange(this);
			}
		});
	}
	else if (type == SKILL4)
	{

		head->loadTextureNormal("ui/downUi/hero/heroHead4.png");
		head->loadTexturePressed("ui/downUi/hero/heroHead4.png");
		m_upGold = SqLite::getInstance()->getGoldByID(4);
		bt->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type){
			if (type == Widget::TouchEventType::ENDED)
			{
				PlayerData::getInstance()->subGold(&m_upGold);
				m_upGold = Ruler::getInstance()->multiplay(m_upGold, 50);
				PlayerData::getInstance()->skillLevelUp(4);
				Button* button = (Button*)g_skillLayer->getChildByName("SkillButton4");
				button->runAction(Show::create());
				coinChange(this);
			}
		});
	}
	else if (type == SKILL5)
	{

		head->loadTextureNormal("ui/downUi/hero/heroHead5.png");
		head->loadTexturePressed("ui/downUi/hero/heroHead5.png");
		m_upGold = SqLite::getInstance()->getGoldByID(5);
		bt->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type){
			if (type == Widget::TouchEventType::ENDED)
			{
				PlayerData::getInstance()->subGold(&m_upGold);
				m_upGold = Ruler::getInstance()->multiplay(m_upGold, 50);
				PlayerData::getInstance()->skillLevelUp(5);
				Button* button = (Button*)g_skillLayer->getChildByName("SkillButton5");
				button->runAction(Show::create());
				coinChange(this);
			}
		});
	}
	else if (type == SKILL6)
	{

		head->loadTextureNormal("ui/downUi/hero/heroHead6.png");
		head->loadTexturePressed("ui/downUi/hero/heroHead6.png");
		m_upGold = SqLite::getInstance()->getGoldByID(6);
		bt->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type){
			if (type == Widget::TouchEventType::ENDED)
			{
				PlayerData::getInstance()->subGold(&m_upGold);
				m_upGold = Ruler::getInstance()->multiplay(m_upGold, 50);
				PlayerData::getInstance()->skillLevelUp(6);
				Button* button = (Button*)g_skillLayer->getChildByName("SkillButton6");
				button->runAction(Show::create());
				coinChange(this);
			}
		});
	}
	else if (type == RELIFE)
	{

		head->loadTextureNormal("ui/downUi/hero/heroHead7.png");
		head->loadTexturePressed("ui/downUi/hero/heroHead7.png");
		bt->setEnabled("false");
		bt->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type){
			if (type == Widget::TouchEventType::ENDED)
			{
				auto relife = Relife::create();
				relife->initRelife();
				g_node->addChild(relife);
				
			}
		});
	}
	cocos2d::CCNotificationCenter::getInstance()->postNotification("CoinChange");
}

void PlayerButton::coinChange(Ref* pSender)
{
	TextBMFont* lb = (TextBMFont*)playerLayer->getChildByName("Layer")->getChildByName("up")->getChildByName("needGold");
	Text * textN = (Text *)playerLayer->getChildByName("Layer")->getChildByName("discribe")->getChildByName("textN");
	Text* text = (Text*)playerLayer->getChildByName("Layer")->getChildByName("discribe")->getChildByName("text");
	Text* textD = (Text*)playerLayer->getChildByName("Layer")->getChildByName("discribe")->getChildByName("textD");
	Text * textDps = (Text*)playerLayer->getChildByName("Layer")->getChildByName("discribe")->getChildByName("Text_19");
	Button* bt = (Button*)playerLayer->getChildByName("Layer")->getChildByName("up");
	Button* up10 = (Button*)playerLayer->getChildByName("Layer")->getChildByName("up10");
	Button* up100 = (Button*)playerLayer->getChildByName("Layer")->getChildByName("up100");
	auto dps = (TextBMFont*)bt->getChildByName("dps");
	auto up10Dps = (TextBMFont*)up10->getChildByName("dps");
	auto up100Dps = (TextBMFont*)up100->getChildByName("dps");
	
	auto judge = Ruler::getInstance()->subNum(m_upGold, *PlayerData::getInstance()->getGold());
	textDps->setVisible(false);
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
		textDps->setVisible(true);
		dps->setString(Ruler::getInstance()->showNum(PlayerData::getInstance()->getPlayerlvupDps()));
		up10Dps->setString(Ruler::getInstance()->showNum(PlayerData::getInstance()->getPlayerlvup10Dps()));
		up100Dps->setString(Ruler::getInstance()->showNum(PlayerData::getInstance()->getPlayerlvup100Dps()));
		textN->setString(PlayerData::getInstance()->getName());
		text->setString(StringUtils::format("lv%d", PlayerData::getInstance()->getPlayerLevel()));
		textD->setString(Ruler::getInstance()->showNum(PlayerData::getInstance()->getTapDpsNoExp()));
	}
	else if (m_type == SKILL1)
	{
		dps->setString(StringUtils::format("+%.0lf", SqLite::getInstance()->getEffPer(0)).c_str());
		textN->setString(StringUtils::format("%s",SqLite::getInstance()->getSkillNameByID(0).c_str()));
		text->setString(StringUtils::format("lv%d", PlayerData::getInstance()->getSkillLevel(m_type - 1)));
		auto eff = SqLite::getInstance()->getEff(m_type - 1) + SqLite::getInstance()->getEffPer(m_type - 1) * PlayerData::getInstance()->getSkillLevel(m_type - 1);
		textD->setString(StringUtils::format(SqLite::getInstance()->getSkillDis(m_type - 1).c_str(), eff));		
		auto x = (playerLayer->getChildByName("Layer")->getChildByName("discribe")->getContentSize().width) / 2;
		auto y = textD->getPositionY();
		textD->setPosition(Vec2(x, y));
		textD->setFontSize(30);
		if (PlayerData::getInstance()->getPlayerLevel() < 50)
		{
			bt->setEnabled(false);
		}
	}
	else if (m_type == SKILL2)
	{
		dps->setString(StringUtils::format("+%.0lf", SqLite::getInstance()->getEffPer(1)).c_str());
		textN->setString(StringUtils::format("%s", SqLite::getInstance()->getSkillNameByID(1).c_str()));
		text->setString(StringUtils::format("lv%d", PlayerData::getInstance()->getSkillLevel(m_type - 1)));
		auto eff = SqLite::getInstance()->getEff(m_type - 1) + SqLite::getInstance()->getEffPer(m_type - 1) * PlayerData::getInstance()->getSkillLevel(m_type - 1);
		textD->setString(StringUtils::format(SqLite::getInstance()->getSkillDis(m_type - 1).c_str(), eff));
		auto x = (playerLayer->getChildByName("Layer")->getChildByName("discribe")->getContentSize().width) / 2;
		auto y = textD->getPositionY();
		textD->setPosition(Vec2(x, y));
		textD->setFontSize(30);
		if (PlayerData::getInstance()->getPlayerLevel() < 100)
		{
			bt->setEnabled(false);
		}
	}
	else if (m_type == SKILL3)
	{
		dps->setString(StringUtils::format("+%.1lf%%", SqLite::getInstance()->getEffPer(2)).c_str());
		textN->setString(StringUtils::format("%s", SqLite::getInstance()->getSkillNameByID(2).c_str()));
		text->setString(StringUtils::format("lv%d", PlayerData::getInstance()->getSkillLevel(m_type - 1)));
		float eff = SqLite::getInstance()->getEff(m_type - 1) + SqLite::getInstance()->getEffPer(m_type - 1) * PlayerData::getInstance()->getSkillLevel(m_type - 1);
		int _eff = eff;
		textD->setString(StringUtils::format(SqLite::getInstance()->getSkillDis(m_type - 1).c_str(), _eff));
		auto x = (playerLayer->getChildByName("Layer")->getChildByName("discribe")->getContentSize().width) / 2;
		auto y = textD->getPositionY();
		textD->setPosition(Vec2(x, y));
		textD->setFontSize(30);
		if (PlayerData::getInstance()->getPlayerLevel() < 200)
		{
			bt->setEnabled(false);
		}
	}
	else if (m_type == SKILL4)
	{
		dps->setString(StringUtils::format("+%.0lf", SqLite::getInstance()->getEffPer(3)).c_str());
		textN->setString(StringUtils::format("%s", SqLite::getInstance()->getSkillNameByID(3).c_str()));
		text->setString(StringUtils::format("lv%d", PlayerData::getInstance()->getSkillLevel(m_type - 1)));
		auto eff = SqLite::getInstance()->getEff(m_type - 1) + SqLite::getInstance()->getEffPer(m_type - 1) * PlayerData::getInstance()->getSkillLevel(m_type - 1);
		
		textD->setString(StringUtils::format(SqLite::getInstance()->getSkillDis(m_type - 1).c_str(), eff));
		auto x = (playerLayer->getChildByName("Layer")->getChildByName("discribe")->getContentSize().width) / 2;
		auto y = textD->getPositionY();
		textD->setPosition(Vec2(x, y));
		textD->setFontSize(30);
		if (PlayerData::getInstance()->getPlayerLevel() < 300)
		{
			bt->setEnabled(false);
		}
	}
	else if (m_type == SKILL5)
	{
		dps->setString(StringUtils::format("+%.1lf", SqLite::getInstance()->getEffPer(4)).c_str());
		textN->setString(StringUtils::format("%s", SqLite::getInstance()->getSkillNameByID(4).c_str()));
		text->setString(StringUtils::format("lv%d", PlayerData::getInstance()->getSkillLevel(m_type - 1)));
		float eff = SqLite::getInstance()->getEff(m_type - 1) + SqLite::getInstance()->getEffPer(m_type - 1) * PlayerData::getInstance()->getSkillLevel(m_type - 1);
		int _eff = eff * 100;
		textD->setString(StringUtils::format(SqLite::getInstance()->getSkillDis(m_type - 1).c_str(), _eff));
		auto x = (playerLayer->getChildByName("Layer")->getChildByName("discribe")->getContentSize().width) / 2;
		auto y = textD->getPositionY();
		textD->setPosition(Vec2(x, y));
		textD->setFontSize(30);
		if (PlayerData::getInstance()->getPlayerLevel() < 400)
		{
			bt->setEnabled(false);
		}
	}
	else if (m_type == SKILL6)
	{
		dps->setString(StringUtils::format("+%.1lf%%", SqLite::getInstance()->getEffPer(5)).c_str());
		textN->setString(StringUtils::format("%s", SqLite::getInstance()->getSkillNameByID(5).c_str()));
		text->setString(StringUtils::format("lv%d", PlayerData::getInstance()->getSkillLevel(m_type - 1)));
		float eff = SqLite::getInstance()->getEff(m_type - 1) + SqLite::getInstance()->getEffPer(m_type - 1) * PlayerData::getInstance()->getSkillLevel(m_type - 1);
		int _eff = eff * 100;
		textD->setString(StringUtils::format(SqLite::getInstance()->getSkillDis(m_type - 1).c_str(), _eff));
		auto x = (playerLayer->getChildByName("Layer")->getChildByName("discribe")->getContentSize().width) / 2;
		auto y = textD->getPositionY();
		textD->setPosition(Vec2(x, y));
		textD->setFontSize(30);
		if (PlayerData::getInstance()->getPlayerLevel() < 500)
		{
			bt->setEnabled(false);
		}
	}
	else if (m_type == RELIFE)
	{
		dps->setString(StringUtils::format("+%.1lf%%", SqLite::getInstance()->getEffPer(6)).c_str());
		textN->setString(StringUtils::format("%s", SqLite::getInstance()->getSkillNameByID(6).c_str()));
		auto eff = SqLite::getInstance()->getEff(m_type - 1) + SqLite::getInstance()->getEffPer(m_type - 1) * PlayerData::getInstance()->getSkillLevel(m_type - 1);
		textD->setString(StringUtils::format(SqLite::getInstance()->getSkillDis(m_type - 1).c_str(), eff));
		auto x = (playerLayer->getChildByName("Layer")->getChildByName("discribe")->getContentSize().width) / 2;
		auto y = textD->getPositionY();
		textD->setPosition(Vec2(x, y));
		textD->setFontSize(30);
		if (PlayerData::getInstance()->getPlayerLevel() < 600)
		{
			bt->setEnabled(false);
		}
	}
	lb->setString(Ruler::getInstance()->showNum(m_upGold));
}

void PlayerButton::upLevelCount()
{
	Button* up10 = (Button*)playerLayer->getChildByName("Layer")->getChildByName("up10");
	Button* up100 = (Button*)playerLayer->getChildByName("Layer")->getChildByName("up100");

	MyNum upGold;
	MyNum judge10;
	MyNum judge100;

	auto levelNow = PlayerData::getInstance()->getPlayerLevel();
	for (size_t i = levelNow; i < (levelNow + 100); i++)
	{
		if (i == levelNow + 10)
		{
			upGold = PlayerData::getInstance()->getPlayerlvup10Gold();
			judge10 = Ruler::getInstance()->subNum(upGold, *PlayerData::getInstance()->getGold());
			if (Ruler::getInstance()->Zero(judge10))
			{
				up10->setVisible(true);
				m_upGold10 = upGold;
			}
			else
			{
				up10->setVisible(false);
			}
		}
	}
	upGold = PlayerData::getInstance()->getPlayerlvup100Gold();
	judge100 = Ruler::getInstance()->subNum(upGold, *PlayerData::getInstance()->getGold());
	if (Ruler::getInstance()->Zero(judge100))
	{
		up100->setVisible(true);
		m_upGold100 = upGold;
	}
	else
	{
		up100->setVisible(false);
	}
	m_count++;
	auto action = Sequence::create(DelayTime::create(4), CallFuncN::create(CC_CALLBACK_1(PlayerButton::callback, this)), nullptr);
	if (up10->isVisible())
	{
		up10->runAction(action);
		if (up100->isVisible())
		{
			up100->runAction(action);
		}
	}	
}

void PlayerButton::callback(Node * node)
{
	m_count--;
	Button* up10 = (Button*)playerLayer->getChildByName("Layer")->getChildByName("up10");
	Button* up100 = (Button*)playerLayer->getChildByName("Layer")->getChildByName("up100");
	if (m_count <= 0)
	{
		if (up10->isVisible())
		{
			up10->setVisible(false);
			if (up100->isVisible())
			{
				up100->setVisible(false);
			}
		}
	}
}
#include "HelloWorldScene.h"

#include "Tool/Rule.h"
#include "Tool/SqLite.h"
#include <cocostudio/CocoStudio.h>
#include "cocos-ext.h"
#include "MainScene/ClickLayer.h"
#include "SaveData/PlayerData.h"
#include "SaveData/ArtifactData.h"
#include "SaveData/ShopData.h"
#include "Tool/Rule.h"
#include "Tool/TimeTool.h"
#include "MainScene/PlayerButton.h"
#include "MainScene/ServantButton.h"
#include "MainScene/ArtifactButton.h"
#include "SaveData/State.h"
#include "SaveData/MonsterState.h"
#include "SaveData/LeaveGold.h"
#include "Ui/settingLayer.h"
#include "Ui/AchieveLayer.h"
#include "Ui/MissionLayer.h"
#include "Ui/ExChange.h"
#include "Ui/SignLayer.h"
#include "SkillCD.h"
#include "Animation.h"
#include "Ui/ItemLayer.h"
#include "SaveData/MissionData.h"
using namespace cocostudio;

USING_NS_CC;
USING_NS_CC_EXT;

using namespace ui;

bool HelloWorld::m_bg = true;
bool HelloWorld::m_sou = true;
bool HelloWorld::m_coutChange = false;
int HelloWorld::m_dayCount = 0;
int HelloWorld::m_signCount = 0;
tm* HelloWorld::m_time = TimeTool::getInstance()->getcurrTime();

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{

	if ( !Layer::init() )
    {
        return false;
    }

	auto leaveGold = new LeaveGold();
	BgMusic::getInstance()->playBg(true);
	m_hitlogic = true;
	m_heroLayer = nullptr;
	m_servantLayer = nullptr;
    m_artifactLayer = nullptr;
	m_shopLayer = nullptr;
	m_arCount = 0;
	m_exchangeCount = 5;
	m_dayCount = 0;
    rootNode = CSLoader::createNode("MainScene.csb");
	if (!mapInit())
	{
		return false;
	}
	addChild(rootNode);
	Slider * hpSlider = (Slider*)rootNode->getChildByName("UiNode")->getChildByName("HpSlider");
	hpSlider->setTouchEnabled(false);
	TextBMFont* textLast = (TextBMFont*)rootNode->getChildByName("UiNode")->getChildByName("Map")->getChildByName("level");
	textLast->setString(StringUtils::format("%d", 1 + PlayerData::getInstance()->getLevel() - 1));
	TextBMFont* textNow = (TextBMFont*)rootNode->getChildByName("UiNode")->getChildByName("Map")->getChildByName("level_1");
	textNow->setString(StringUtils::format("%d", 1 + PlayerData::getInstance()->getLevel()));
	TextBMFont* textNext = (TextBMFont*)rootNode->getChildByName("UiNode")->getChildByName("Map")->getChildByName("level_0");
	textNext->setString(StringUtils::format("%d", 1 + PlayerData::getInstance()->getLevel() + 1));
	
	auto leaveBtn = (Button*)rootNode->getChildByName("leave");
	if (leaveGold->getGolds().number != 0)
	{
		leaveBtn->setVisible(true);
	}
	leaveBtn->addTouchEventListener([this, leaveGold,leaveBtn](Ref* sender, Widget::TouchEventType type){
		if (type == Widget::TouchEventType::ENDED)
		{
			PlayerData::getInstance()->addGold(&(leaveGold->getGolds()));
			delete leaveGold;
			leaveBtn->setVisible(false);
		}
	});

	clickLayer = ClickLayer::create();
	clickLayer->setZOrder(-1);
	rootNode->addChild(clickLayer);
	uiInit();
	uiCallBack();
	createMonster();
	CCNotificationCenter::getInstance()->addObserver(this, callfuncO_selector(HelloWorld::coinChange), "CoinChange", nullptr);
	CCNotificationCenter::getInstance()->addObserver(this, callfuncO_selector(HelloWorld::ArChange), "ArtiChange", nullptr);
	CCNotificationCenter::getInstance()->addObserver(this, callfuncO_selector(HelloWorld::itemChange), "itemChange", nullptr);
	CCNotificationCenter::getInstance()->addObserver(this, callfuncO_selector(HelloWorld::playerChange), "playerChange", nullptr);
	showTime = false;
	Slider* timeSlider = (Slider*)rootNode->getChildByName("UiNode")->getChildByName("timeSlider");
	timeNow = PlayerData::getInstance()->getMaxTime();

	scheduleUpdate();
	attackeffection();
	coinChange(this);
	PlayerButton::getSkillLayer(rootNode->getChildByName("UiNode")->getChildByName("SkillLayer"));
	PlayerButton::getRootNode(rootNode);
	ServantButton::getRootNode(rootNode);
	TextBMFont* waveNum = (TextBMFont*)rootNode->getChildByName("UiNode")->getChildByName("Wave_Button")->getChildByName("WaveNum");
	waveNum->setString(StringUtils::format("%d/%d", PlayerData::getInstance()->getWaveNow(), PlayerData::getInstance()->getMaxWave() - 1));
	bossBt = nullptr;
	m_gamelogic = true;
    return true;
}
void HelloWorld::coinChange(Ref *ref)
{
	
	TextBMFont* gold = (TextBMFont*)rootNode->getChildByName("goldNum");
	gold->setString(Ruler::getInstance()->showNum(*PlayerData::getInstance()->getGold()));
	if (m_heroLayer)
	{
		TextBMFont* gold = (TextBMFont*)m_heroLayer->getChildByName("message")->getChildByName("gold");
		gold->setString(Ruler::getInstance()->showNum(*PlayerData::getInstance()->getGold()));
	}
	if (m_servantLayer)
	{
		TextBMFont* gold = (TextBMFont*)m_servantLayer->getChildByName("message")->getChildByName("gold");
		gold->setString(Ruler::getInstance()->showNum(*PlayerData::getInstance()->getGold()));
	}

	if (m_coutChange)
	{
		m_exchangeCount--;
		m_coutChange = false;
	}
	ExChange::setCount(m_exchangeCount);

	//PlayerData::getInstance()->saveUserData();

}

void HelloWorld::ArChange(Ref* ref)
{
	//if (ref)
	//{
		TextBMFont* dps = (TextBMFont*)m_artifactLayer->getChildByName("message")->getChildByName("Dps");
		auto dpsAll = ArtifactData::getInstance()->getAllDpsMul();
		dps->setString(StringUtils::format("+%.1f%%", dpsAll * 100).c_str());
		if (m_artifactLayer)
		{
			auto btn = (Button*)m_artifactLayer->getChildByName("getArtifact");
			auto arStoneNum = ArtifactData::getInstance()->getArtiStone();
			auto needStoneNum = ArtifactData::getInstance()->getNeededArStone();
			TextBMFont* arStone = (TextBMFont*)m_artifactLayer->getChildByName("message")->getChildByName("Resource");
			arStone->setString(StringUtils::format("%d", arStoneNum).c_str());
			TextBMFont* subStone = (TextBMFont*)btn->getChildByName("SubAr");
			subStone->setString(StringUtils::format("%d", needStoneNum).c_str());
			if ((arStoneNum - needStoneNum) >= 0)
			{
				btn->setEnabled(true);
			}
			else
			{
				btn->setEnabled(false);
			}
		}
	//}
}

void HelloWorld::itemChange(Ref* ref)
{
	if (m_shopLayer)
	{
		auto money = (TextBMFont*)m_shopLayer->getChildByName("message")->getChildByName("money");
		money->setString(StringUtils::format("%d", ShopData::getInstance()->getShopGold()).c_str());	
	}
}

void HelloWorld::playerChange(Ref* ref)
{
	if (m_heroLayer)
	{
		TextBMFont* dps = (TextBMFont*)m_heroLayer->getChildByName("message")->getChildByName("Dps");
		dps->setString(Ruler::getInstance()->showNum(PlayerData::getInstance()->getTapDpsNoExp()));
	}
}

void HelloWorld::callBackFunc(Armature * armature, MovementEventType type, const std::string& action)
{
	static bool dead;
	if (type == MovementEventType::LOOP_COMPLETE || type == MovementEventType::COMPLETE)
	{
		if (action == "Start")
		{	
			armature->getAnimation()->play("Wait");
			clickLayer->setTouchEnabled(true);
			MyState::getInstance()->setTaped(false);
			m_hitlogic = true;
		}
		
		if (action == "Leave")
		{		
			armature->removeFromParent();
			createMonster();
		}
		if (action == "Hurt")
		armature->getAnimation()->play("Wait");
	}
	if (action == "Hurt")
	{
		Slider* hpSlider = (Slider*)rootNode->getChildByName("HpSlider");
	//	killBoss();
	}
	return;
}
void HelloWorld::createMonster()
{
	auto r = random(0, 4);
	auto monster = SqLite::getInstance()->getMonsterByID(PlayerData::getInstance()->getRandNpc(r));
	ArmatureDataManager::getInstance()->addArmatureFileInfo(monster->png, monster->plist, monster->exportJson);//读取动画相关文件
	armature = Armature::create(monster->name);
	armature->setName("MonsterArmature");
	armature->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(HelloWorld::callBackFunc));
	Node* monsterNode = (Node*)rootNode->getChildByName("MonsterNode");
	armature->getAnimation()->play("Start");
	Slider * hpSlider = (Slider*)rootNode->getChildByName("UiNode")->getChildByName("HpSlider");

	auto hpNum = PlayerData::getInstance()->getHpByID(PlayerData::getInstance()->getLevel());
	auto hpS = hpNum.number;
	hpS *= 1000000;
	hpSlider->setMaxPercent(hpS);
	hpSlider->setPercent(hpS);

	TextBMFont* tbm = (TextBMFont*)rootNode->getChildByName("UiNode")->getChildByName("HpSlider")->getChildByName("hpNow");
	tbm->setString(Ruler::getInstance()->showNum(PlayerData::getInstance()->getHpByID(PlayerData::getInstance()->getLevel())));
	PlayerData::getInstance()->setHpNow(PlayerData::getInstance()->getHpByID(PlayerData::getInstance()->getLevel()));
	monsterNode->addChild(armature);

	Slider* timeSlider = (Slider*)rootNode->getChildByName("UiNode")->getChildByName("timeSlider");
	armature->setScale(1.5f);
	if (PlayerData::getInstance()->getWaveNow() == PlayerData::getInstance()->getMaxWave())
	{
		
		PlayerData::getInstance()->resetTime();
		armature->setScale(2.0f);
		timeNow = PlayerData::getInstance()->getMaxTime() * 1000;
		timeSlider->runAction(Show::create());
		timeSlider->setMaxPercent(PlayerData::getInstance()->getMaxTime()*1000);
		timeSlider->setPercent(timeNow * 1000);
		MonsterState::getInstance()->setMonsterState(BOSS);
		rootNode->getChildByName("dragon")->runAction(Show::create());
		rootNode->getChildByName("grayDragon")->runAction(Hide::create());
	}
	else if (PlayerData::getInstance()->getWaveNow() <= 1)
	{
		if (PlayerData::getInstance()->getWaveNow() == 0)
		{
			Node* bossButtonNode = (Node*)rootNode->getChildByName("UiNode")->getChildByName("Wave_Button")->getChildByName("escapeBoss");
			TextBMFont* waveNum = (TextBMFont*)rootNode->getChildByName("UiNode")->getChildByName("Wave_Button")->getChildByName("WaveNum");
			waveNum->runAction(Hide::create());
			if (!bossButtonNode->getChildByName("bt"))
			{
				bossBt = bossButton::create();
				bossButtonNode->addChild(bossBt);
				bossBt->setName("bt");
				bossBt->onTouchEnded(nullptr, nullptr);

			}
		}
		PlayerData::getInstance()->randRareMonster();
		timeSlider->runAction(Hide::create());
		rootNode->getChildByName("dragon")->runAction(Hide::create());
		if (MonsterState::getInstance()->getTypeNow() == MONSTER_TYPE::RARE)
		{
			rootNode->getChildByName("grayDragon")->runAction(Show::create());
		}
		else
		{
			rootNode->getChildByName("grayDragon")->runAction(Hide::create());
		}
	}
	else
	{
		PlayerData::getInstance()->randRareMonster();
		if (MonsterState::getInstance()->getTypeNow() == MONSTER_TYPE::RARE)
		{
			rootNode->getChildByName("grayDragon")->runAction(Show::create());
		}
		else
		{
			rootNode->getChildByName("grayDragon")->runAction(Hide::create());
		}
	}
	
}
void HelloWorld::update(float dt)
{
	if (m_gamelogic == true)
	{
		if (PlayerData::getInstance()->getRelife())
		{
			relife();
		}
		if (m_hitlogic == true)
		{
			auto heroDps = PlayerData::getInstance()->getHeroDps();
			auto dps = Ruler::getInstance()->multiplay(heroDps, dt);
			TextBMFont* kdps = (TextBMFont*)rootNode->getChildByName("UiNode")->getChildByName("SkillLayer")->getChildByName("KeepDps")->getChildByName("KeepDps");
			kdps->setString(Ruler::getInstance()->showNum(heroDps));
			TextBMFont* tdps = (TextBMFont*)rootNode->getChildByName("UiNode")->getChildByName("SkillLayer")->getChildByName("TapDps")->getChildByName("heroDps");
			tdps->setString(Ruler::getInstance()->showNum(PlayerData::getInstance()->getDps()).c_str());
			auto tpDps = Ruler::getInstance()->addNum(heroDps, PlayerData::getInstance()->getDps());
			TextBMFont* tpdps = (TextBMFont*)rootNode->getChildByName("UiNode")->getChildByName("SkillLayer")->getChildByName("TotalDps")->getChildByName("TotalDps");
			tpdps->setString(Ruler::getInstance()->showNum(tpDps));
			skillEff(dt);
			shopItemEff(dt);
			static float t_now = 0;
			t_now += dt;
			if (t_now > 1 / 10.0f && MyState::getInstance()->getTaped())
			{
				num = PlayerData::getInstance()->getTapDps();
				PlayerData::getInstance()->subHp(num);
				Node* monsterNode = rootNode->getChildByName("MonsterNode");
				Armature* armature = (Armature*)monsterNode->getChildByName("MonsterArmature");
				normalAtk();
				if (PlayerData::getInstance()->getSkillopen(5))
				{
					auto num1 = Ruler::getInstance()->multiplay(PlayerData::getInstance()->getdefeatMonsterGold(), PlayerData::getInstance()->getSkillEFF(5) * (1 + ArtifactData::getInstance()->getskilleffUp(6)));
					PlayerData::getInstance()->addGold(&num1);
				}
				if (ShopData::getInstance()->getItemBeUsedById(1))
				{
					auto num1 = Ruler::getInstance()->multiplay(PlayerData::getInstance()->getdefeatMonsterGold(), 0.3);
					PlayerData::getInstance()->addGold(&num1);
				}
				armature->getAnimation()->play("Hurt", -1, 0);
				t_now = 0;
				MyState::getInstance()->setTaped(false);
			}

			if (m_heroLayer)
			{
				TextBMFont* dps = (TextBMFont*)m_heroLayer->getChildByName("message")->getChildByName("Dps");
				dps->setString(Ruler::getInstance()->showNum(PlayerData::getInstance()->getTapDpsNoExp()));
			}
			if (m_servantLayer)
			{
				TextBMFont* dps = (TextBMFont*)m_servantLayer->getChildByName("message")->getChildByName("Dps");
				dps->setString(Ruler::getInstance()->showNum(heroDps));
			}
			if (PlayerData::getInstance()->getWaveNow() == PlayerData::getInstance()->getMaxWave())
			{
				Slider* timeSlider = (Slider*)rootNode->getChildByName("UiNode")->getChildByName("timeSlider");

				timeNow -= dt * 1000;
				if (timeNow <= 0)
				{
					PlayerData::getInstance()->setWave(0);
					MyState::getInstance()->setBossButtonDown(true);
					timeNow = PlayerData::getInstance()->getMaxTime();
					Node* bossButtonNode = (Node*)rootNode->getChildByName("UiNode")->getChildByName("Wave_Button")->getChildByName("escapeBoss");
					if (!bossButtonNode->getChildByName("bt"))
					{
						bossBt = bossButton::create();
						bossButtonNode->addChild(bossBt);
						bossBt->setName("bt");

					}
					bossBt->onTouchEnded(nullptr, nullptr);
				}
				else
				{
					timeSlider->setPercent(timeNow);
					Text* timeNum = (Text*)timeSlider->getChildByName("Time");
					timeNum->setString(StringUtils::format("%.2f", (float)timeNow / 1000));

				}
				showTime = true;

			}

			Slider* slider = (Slider*)rootNode->getChildByName("UiNode")->getChildByName("HpSlider");
			auto subNow = Ruler::getInstance()->subNum(PlayerData::getInstance()->getHpNow(), dps);
			PlayerData::getInstance()->setHpNow(subNow);

			if (PlayerData::getInstance()->getHpByID(PlayerData::getInstance()->getLevel()).Mathbit == PlayerData::getInstance()->getHpNow().Mathbit)
				slider->setPercent(PlayerData::getInstance()->getHpNow().number * 1000000);
			else if (PlayerData::getInstance()->getHpByID(PlayerData::getInstance()->getLevel()).Mathbit - PlayerData::getInstance()->getHpNow().Mathbit == 1)
				slider->setPercent(PlayerData::getInstance()->getHpNow().number * 1000);
			else if (PlayerData::getInstance()->getHpByID(PlayerData::getInstance()->getLevel()).Mathbit - PlayerData::getInstance()->getHpNow().Mathbit == 2)
				slider->setPercent(PlayerData::getInstance()->getHpNow().number);
			else if (PlayerData::getInstance()->getHpByID(PlayerData::getInstance()->getLevel()).Mathbit - PlayerData::getInstance()->getHpNow().Mathbit > 3)
				slider->setPercent(0);

			TextBMFont* tbm = (TextBMFont*)rootNode->getChildByName("UiNode")->getChildByName("HpSlider")->getChildByName("hpNow");
			tbm->setString(Ruler::getInstance()->showNum(PlayerData::getInstance()->getHpNow()));
			auto hpnow = PlayerData::getInstance()->getHpNow();
			killBoss();
		}
		else
		{
			skillKpCDUpdate(dt);
			shopItemCDUpDate(dt);
		}
	}
	

	//PlayerData::getInstance()->saveUserData();
	//runAni();

 }
void HelloWorld::uiInit()
{

	Slider* timeSlider = (Slider*)rootNode->getChildByName("UiNode")->getChildByName("timeSlider");
	timeSlider->runAction(Hide::create());
	
}
void HelloWorld::uiCallBack()
{
	Button* playerButton = (Button*)rootNode->getChildByName("UiNode")->getChildByName("OptionLayer")->getChildByName("playerButton");
	Button* servantButton = (Button*)rootNode->getChildByName("UiNode")->getChildByName("OptionLayer")->getChildByName("servantButton");
	Button* artifactButton = (Button*)rootNode->getChildByName("UiNode")->getChildByName("OptionLayer")->getChildByName("artifactButton");
	Button* itemButton = (Button*)rootNode->getChildByName("UiNode")->getChildByName("OptionLayer")->getChildByName("itemButton");
	Button* settingButton = (Button*)rootNode->getChildByName("UiNode")->getChildByName("Setting");
	Button* achieveButton = (Button*)rootNode->getChildByName("UiNode")->getChildByName("achiveButton");
	Button* missonButton = (Button*)rootNode->getChildByName("UiNode")->getChildByName("Mission");
	Button* signButton = (Button*)rootNode->getChildByName("UiNode")->getChildByName("SignButton");
	
	playerSkillCallBack();

	playerButton->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::BEGAN)
		{
			Button* bt = (Button*)sender;
		}
		if (type == Widget::TouchEventType::ENDED) {
			// 注意node的生命周期的问题
			Button* bt = (Button*)sender;
			auto opLayer = rootNode->getChildByName("UiNode")->getChildByName("OptionLayer");
			for (auto child : opLayer->getChildren())
			{
				Button* _child = (Button*)child;
				_child->setEnabled(true);
			}
			bt->setEnabled(false);
			if (initDownLayer(m_heroLayer))
			{
				Sprite* disc = (Sprite*)m_heroLayer->getChildByName("message")->getChildByName("discribe");
				auto sprite = Sprite::create("ui/downUi/hero/dianjishanghai.png");
				auto pos = disc->getPosition();
				sprite->setPosition(disc->getPosition());
				m_heroLayer->getChildByName("message")->addChild(sprite);
				disc->removeFromParent();
				TextBMFont* dps = (TextBMFont*)m_heroLayer->getChildByName("message")->getChildByName("Dps");
				dps->setString(Ruler::getInstance()->showNum(PlayerData::getInstance()->getTapDpsNoExp()));
				auto buyBtn = (TextBMFont*)m_heroLayer->getChildByName("message")->getChildByName("buy");
				buyBtn->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type){
					if (type == Widget::TouchEventType::ENDED)
					{
						auto exc = ExChange::create();
						exc->initExchange();
						exc->setNode(rootNode);
						rootNode->addChild(exc);
					}
				});
				TextBMFont* gold = (TextBMFont*)m_heroLayer->getChildByName("message")->getChildByName("gold");
				gold->setString(Ruler::getInstance()->showNum(*PlayerData::getInstance()->getGold()));
				for (int i = 0; i < 8; i++)
				{
					PlayerButton* bt = PlayerButton::create();
					bt->initPlayerButton((BUTTONTYPE)i);
					auto widget = Widget::create();
					widget->setContentSize(bt->getContentSize());
					widget->addChild(bt);
					ListView* lv = (ListView*)m_heroLayer->getChildByName("ListView");
					lv->pushBackCustomItem(widget);
				}
			}
			else
			{
			
			}	
			playerChange(this);
		}
	});
	servantButton->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::BEGAN)
		{
			
			Button* bt = (Button*)sender;
		}
		if (type == Widget::TouchEventType::ENDED)
		{
			// 注意node的生命周期的问题  
			Button* bt = (Button*)sender;
			auto opLayer = rootNode->getChildByName("UiNode")->getChildByName("OptionLayer");
			for (auto child : opLayer->getChildren())
			{
				Button* _child = (Button*)child;
				_child->setEnabled(true);
			}
			bt->setEnabled(false);
			if (initDownLayer(m_servantLayer))
			{
				ListView* lv = (ListView*)m_servantLayer->getChildByName("ListView");
				ServantButton::getListView(lv);
				TextBMFont* dps = (TextBMFont*)m_servantLayer->getChildByName("message")->getChildByName("Dps");
				dps->setString(Ruler::getInstance()->showNum(PlayerData::getInstance()->getHeroDps()));
				TextBMFont* gold = (TextBMFont*)m_servantLayer->getChildByName("message")->getChildByName("gold");
				gold->setString(Ruler::getInstance()->showNum(*PlayerData::getInstance()->getGold()));
				auto buyBtn = (TextBMFont*)m_servantLayer->getChildByName("message")->getChildByName("buy");
				buyBtn->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type){
					if (type == Widget::TouchEventType::ENDED)
					{
						auto exc = ExChange::create();
						exc->initExchange();
						exc->setNode(rootNode);
						rootNode->addChild(exc);
					}
				});
				initSer();
			}
		}
	});
	artifactButton->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::BEGAN)
		{
			Button* bt = (Button*)sender;
		}
		if (type == Widget::TouchEventType::ENDED) {
			// 注意node的生命周期的问题  
			Button* bt = (Button*)sender;
			auto opLayer = rootNode->getChildByName("UiNode")->getChildByName("OptionLayer");
			for (auto child : opLayer->getChildren())
			{
				Button* _child = (Button*)child;
				_child->setEnabled(true);
			}
			bt->setEnabled(false);
			if (initDownLayerAr(m_artifactLayer))
			{
				initAr();
			}	
			ArChange(this);
		}
	});
	itemButton->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::BEGAN)
		{
			Button* bt = (Button*)sender;
		}
		if (type == Widget::TouchEventType::ENDED) {
			// 注意node的生命周期的问题  
			Button* bt = (Button*)sender;
			auto opLayer = rootNode->getChildByName("UiNode")->getChildByName("OptionLayer");
			for (auto child : opLayer->getChildren())
			{
				
				Button* _child = (Button*)child;
				_child->setEnabled(true);
			}
			bt->setEnabled(false);
			if (initDownLayerSh(m_shopLayer))
			{
				auto lv = (ListView*)m_shopLayer->getChildByName("ListView");
				for (size_t i = 0; i < 13; i++)
				{
					/*if (i != 4 && i != 7 && i != 8)
					{*/
						auto widget = Widget::create();
						auto item = ItemLayer::create();
						item->initItemLayer(i);
						auto size = item->getContentSize();
						widget->setContentSize(size);
						widget->addChild(item);
						lv->pushBackCustomItem(widget);
						cocos2d::CCNotificationCenter::getInstance()->postNotification("itemChange");
					//}
				}
			}
			itemChange(this);
		}
	});
	settingButton->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::BEGAN)
		{
			Button* bt = (Button*)sender;
		}
		if (type == Widget::TouchEventType::ENDED) {
			// 注意node的生命周期的问题  
			Button* bt = (Button*)sender;
			settingLayer::setOff_On(m_bg, m_sou);
			auto layer = settingLayer::create();
			layer->setNode(rootNode);
			rootNode->addChild(layer);
		}
	});
	achieveButton->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::BEGAN)
		{
			Button* bt = (Button*)sender;
		}
		if (type == Widget::TouchEventType::ENDED) {
			// 注意node的生命周期的问题  
			Button* bt = (Button*)sender;
			auto layer = AchieveLayer::create();
			this->addChild(layer);
		}
	});
	missonButton->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::BEGAN)
		{
			Button* bt = (Button*)sender;
		}
		if (type == Widget::TouchEventType::ENDED) {
			// 注意node的生命周期的问题  
			Button* bt = (Button*)sender;
			auto layer = MissionLayer::create();
			this->addChild(layer);
		}
	});
	signButton->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::BEGAN)
		{
			Button* bt = (Button*)sender;
		}
		if (type == Widget::TouchEventType::ENDED) {
			// 注意node的生命周期的问题  
			Button* bt = (Button*)sender;
			auto layer = SignLayer::create();
			this->addChild(layer);
		}
	});
}
void HelloWorld::killBoss()
{
	TextBMFont* waveNum = (TextBMFont*)rootNode->getChildByName("UiNode")->getChildByName("Wave_Button")->getChildByName("WaveNum");
	Sprite* escapeBoss = (Sprite*)rootNode->getChildByName("UiNode")->getChildByName("Wave_Button")->getChildByName("escapeBoss");
	if (MyState::getInstance()->getBossButtonDown())
	{
		m_hitlogic = false;
		clickLayer->setTouchEnabled(false);
		armature->getAnimation()->play("Leave");
		
		MyState::getInstance()->setBossButtonDown(false);
	}
	if (Ruler::getInstance()->Zero(PlayerData::getInstance()->getHpNow()))
	{
		m_hitlogic = false;
		PlayerData::getInstance()->defeatMonsterGold();
		if (PlayerData::getInstance()->getWaveNow() < PlayerData::getInstance()->getMaxWave() - 1 && PlayerData::getInstance()->getWaveNow() != 0)
		{
			PlayerData::getInstance()->waveUp();
			
			waveNum->setString(StringUtils::format("%d/%d", PlayerData::getInstance()->getWaveNow(),PlayerData::getInstance()->getMaxWave() - 1));
		}
		else if (PlayerData::getInstance()->getWaveNow() == PlayerData::getInstance()->getMaxWave()-1)
		{
			
			waveNum->runAction(Hide::create());
			escapeBoss->runAction(Show::create());
			PlayerData::getInstance()->waveUp();
			Node* bossButtonNode = (Node*)rootNode->getChildByName("UiNode")->getChildByName("Wave_Button")->getChildByName("escapeBoss");
			if (!bossButtonNode->getChildByName("bt"))
			{
				bossBt = bossButton::create();
				bossButtonNode->addChild(bossBt);
				bossBt->setName("bt");			
			}
				
		}
		else if (PlayerData::getInstance()->getWaveNow() == 0)
		{

		}
		else
		{
			PlayerData::getInstance()->resetWave();
			PlayerData::getInstance()->levelUp();
			mapChange();
			TextBMFont* textLast = (TextBMFont*)rootNode->getChildByName("UiNode")->getChildByName("Map")->getChildByName("level");
			textLast->setString(StringUtils::format("%d", 1 + PlayerData::getInstance()->getLevel()-1));
			TextBMFont* textNow = (TextBMFont*)rootNode->getChildByName("UiNode")->getChildByName("Map")->getChildByName("level_1");
			textNow->setString(StringUtils::format("%d", 1 + PlayerData::getInstance()->getLevel()));
			TextBMFont* textNext = (TextBMFont*)rootNode->getChildByName("UiNode")->getChildByName("Map")->getChildByName("level_0");
			textNext->setString(StringUtils::format("%d", 1 + PlayerData::getInstance()->getLevel()+1));
			Node* bossButtonNode = (Node*)rootNode->getChildByName("UiNode")->getChildByName("Wave_Button")->getChildByName("escapeBoss");
			bossButtonNode->removeChildByName("bt");
			waveNum->setString(StringUtils::format("%d/%d", PlayerData::getInstance()->getWaveNow(), PlayerData::getInstance()->getMaxWave() - 1));
			waveNum->runAction(Show::create());
		}
		auto hpnow = PlayerData::getInstance()->getHpNow();
		armature->getAnimation()->play("Leave");
	}
	
}
void HelloWorld::mapChange()
{
	if (PlayerData::getInstance()->getLevel() % 5 == 0)
	{
		auto waveN = PlayerData::getInstance()->getWaveNow();
		m_gamelogic = false;
		auto effect = Sprite::create();
		/*effect->setZOrder(100);*/
		auto animate = MyAnimation::getInstance()->getAnimate();
		effect->setScale(3.6);
		effect->setAnchorPoint(Vec2(0, 0));
		auto seq = Sequence::create(animate, CallFuncN::create(CC_CALLBACK_1(HelloWorld::bgChange, this)), CallFuncN::create(CC_CALLBACK_1(HelloWorld::deleteSprite, this)),CallFuncN::create(CC_CALLBACK_1(HelloWorld::gameContinue,this)), NULL);
		this->addChild(effect);
		effect->runAction(seq);
	}
	if ((PlayerData::getInstance()->getLevel() + 1) % 5 == 0)
	{
		auto mapNum = (PlayerData::getInstance()->getLevel() + 1) / 5;
		auto map = SqLite::getInstance()->getMapDataByID(mapNum % 10);
		Sprite* spr = (Sprite*)rootNode->getChildByName("UiNode")->getChildByName("Map")->getChildByName("MapOtherR");
		spr->setTexture(StringUtils::format("map/icon/%s", map->mapIcon.c_str()));
		Sprite* mapL = (Sprite*)rootNode->getChildByName("UiNode")->getChildByName("Map")->getChildByName("MapOtherL");
		mapL->runAction(Show::create());
	}
	if ((PlayerData::getInstance()->getLevel() - 1) % 5 == 0)
	{
		auto mapNum = (PlayerData::getInstance()->getLevel() - 1) / 5;
		auto map = SqLite::getInstance()->getMapDataByID(mapNum % 10); 
		Sprite* mapL = (Sprite*)rootNode->getChildByName("UiNode")->getChildByName("Map")->getChildByName("MapOtherL");
		mapL->setTexture(StringUtils::format("map/icon/%s", map->mapIcon.c_str()));
		mapL->runAction(Show::create());
	}
}
void HelloWorld::bgChange(Node* node)
{
	auto waveN = PlayerData::getInstance()->getWaveNow();
	auto mapNum = PlayerData::getInstance()->getLevel() / 5;
	auto map = SqLite::getInstance()->getMapDataByID(mapNum % 10);
	Sprite* spr = (Sprite*)rootNode->getChildByName("mainBG");
	spr->setTexture(StringUtils::format("map/bg/%s", map->bg.c_str()));
	Sprite* mapNow = (Sprite*)rootNode->getChildByName("UiNode")->getChildByName("Map")->getChildByName("MapNow");
	mapNow->setTexture(StringUtils::format("map/icon/%s", map->mapIcon.c_str()));
	Sprite* mapL = (Sprite*)rootNode->getChildByName("UiNode")->getChildByName("Map")->getChildByName("MapOtherL");
	mapL->runAction(Show::create());
	
}
bool HelloWorld::initDownLayer(Node* &downLayer)
{
	bool ret = false;
	if (!downLayer)
	{
		if (rootNode->getChildByName("downLayerNow"))
			rootNode->removeChildByName("downLayerNow");
 		downLayer = CSLoader::createNode("downLayer.csb");
		downLayer->retain();
		downLayer->setName("downLayerNow"); 
		Button* escButton = (Button*)downLayer->getChildByName("message")->getChildByName("escButton");
		escButton->addTouchEventListener([downLayer,this](Ref* sender, Widget::TouchEventType type) {
			if (type == Widget::TouchEventType::ENDED) {
				// 注意node的生命周期的问题  
				auto opLayer = rootNode->getChildByName("UiNode")->getChildByName("OptionLayer");
				for (auto child : opLayer->getChildren())
				{
					Button* _child = (Button*)child;
					_child->setEnabled(true);
				}
				downLayer->removeFromParent();
			}
		});
		ret = true;
	}
	else
	{
		rootNode->removeChildByName("downLayerNow");
	}
	

	rootNode->addChild(downLayer);
	return ret;
}

bool HelloWorld::initDownLayerAr(Node* &downLayer)
{
	bool ret = false;
	if (!downLayer)
	{
		if (rootNode->getChildByName("downLayerNow"))
			rootNode->removeChildByName("downLayerNow");
		downLayer = CSLoader::createNode("downLayerAr.csb");
		downLayer->retain();
		downLayer->setName("downLayerNow");
		Button* escButton = (Button*)downLayer->getChildByName("message")->getChildByName("escButton");
		escButton->addTouchEventListener([downLayer,this](Ref* sender, Widget::TouchEventType type) {
			if (type == Widget::TouchEventType::ENDED) {
				// 注意node的生命周期的问题
				auto opLayer = rootNode->getChildByName("UiNode")->getChildByName("OptionLayer");
				for (auto child : opLayer->getChildren())
				{
					Button* _child = (Button*)child;
					_child->setEnabled(true);
				}
				downLayer->removeFromParent();
				
			}
		});
		ret = true;
		auto btn = (Button*)downLayer->getChildByName("getArtifact");
		btn->addTouchEventListener([downLayer, this](Ref* sender, Widget::TouchEventType type) {
			if (type == Widget::TouchEventType::ENDED) {
				ListView* lv = (ListView*)m_artifactLayer->getChildByName("ListView");
				ArtifactButton::setRootNode(m_artifactLayer);
				auto button = ArtifactButton::create();
				button->setTag(m_arCount);
				button->initArtifactLayer(0,false);
				auto widget = Widget::create();
				widget->setName("arWidget");
				auto size = button->getContentSize();
				widget->setContentSize(size);
				widget->addChild(button);
				button->setWidget(widget);
				lv->pushBackCustomItem(widget);
				lv->jumpToBottom();
				ArtifactButton::setListView(lv);
				ArChange(this);
			}
		});
	}
	else
	{
		rootNode->removeChildByName("downLayerNow");
	}

	rootNode->addChild(downLayer);
	return ret;
}

bool HelloWorld::initDownLayerSh(Node* &downLayer)
{
	bool ret = false;
	if (!downLayer)
	{
		if (rootNode->getChildByName("downLayerNow"))
			rootNode->removeChildByName("downLayerNow");
		downLayer = CSLoader::createNode("downLayerSh.csb");
		downLayer->retain();
		downLayer->setName("downLayerNow");
		Button* escButton = (Button*)downLayer->getChildByName("message")->getChildByName("escButton");
		escButton->addTouchEventListener([downLayer, this](Ref* sender, Widget::TouchEventType type) {
			if (type == Widget::TouchEventType::ENDED)
			{
				// 注意node的生命周期的问题
				auto opLayer = rootNode->getChildByName("UiNode")->getChildByName("OptionLayer");
				for (auto child : opLayer->getChildren())
				{
					Button* _child = (Button*)child;
					_child->setEnabled(true);
				}
				downLayer->removeFromParent();
			}
		});
		ret = true;
	}
	else
	{
		rootNode->removeChildByName("downLayerNow");
	}
	rootNode->addChild(downLayer);
	return ret;
}

void HelloWorld::playerSkillCallBack()
{
	Node* node = rootNode->getChildByName("UiNode")->getChildByName("SkillLayer");
	for (int i = 1; i < 7; i++)
	{
		m_skill[i - 1] = (Button*)node->getChildByName(StringUtils::format("SkillButton%d", i));
		m_skill[i - 1]->addTouchEventListener([this, i](Ref* sender, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED)
			{
				MissionData::getInstance()->addMissionTimesById(8);
				auto skillKpCD = SkillCD::create();
				skillKpCD->initkpImage(i);
				skillKpCD->setPosition(m_skill[i - 1]->getContentSize() / 2);
				auto skillCD = SkillCD::create();
				skillCD->initImage(i);

				skillCD->setPosition(m_skill[i - 1]->getContentSize() / 2);

				m_skill[i - 1]->addChild(skillCD);
				m_skill[i - 1]->addChild(skillKpCD, 1);
				skillKpCD->setName("SkillKpCD");

				skillCD->setName("SkillCD");

				m_skill[i - 1]->setEnabled(false);
				PlayerData::getInstance()->openSkill(i - 1);
				AchieveData::getInstance()->skillUsed(i-1);
			}
		});
	}
}

void HelloWorld::skillCDUpdate(float dt)
{
	for (int i = 0; i < 6; i++)
	{
		if (m_skill[i]->getChildByName("SkillCD"))
		{
			if (!PlayerData::getInstance()->getSkillopen(i))
			{
				SkillCD *cd = (SkillCD*)m_skill[i]->getChildByName("SkillCD");
				cd->setPercentNow(dt);

				if (cd->getkpTime() <= 0)
				{
					cd->removeFromParent();
					m_skill[i]->setEnabled(true);


				}
			}
			

		}
			
	}
}
void HelloWorld::skillKpCDUpdate(float dt)
{
	for (int i = 0; i < 6; i++)
	{
		if (m_skill[i]->getChildByName("SkillKpCD"))
		{
			if(PlayerData::getInstance()->getSkillopen(i))
			{
				SkillCD *cd = (SkillCD*)m_skill[i]->getChildByName("SkillKpCD");
				cd->setPercentNow(dt);

				PlayerData::getInstance()->openSkill(i);
				if (cd->getkpTime() <= 0)
				{
					cd->removeFromParent();
					PlayerData::getInstance()->closeSkill(i);

					if (i == 2)
					{
						PlayerData::getInstance()->setSkillexploreProb(0);
					}
					if (i == 4)
					{
						PlayerData::getInstance()->setSkillTap(0);
					}

				}
			}
			

		}

	}
}

void HelloWorld::skillEff(float dt)
{
	if (m_hitlogic)
	{
		static float t_now = 0;
		t_now += dt;
		if (PlayerData::getInstance()->getSkillopen(0))
		{


			PlayerData::getInstance()->subHp(Ruler::getInstance()->multiplay(PlayerData::getInstance()->getTapDps(), PlayerData::getInstance()->getSkillEFF(0) * (1 + ArtifactData::getInstance()->getskilleffUp(1))));
			
		}
		if (MyState::getInstance()->getKTap() && PlayerData::getInstance()->getSkillopen(1))
		{
		
			if (t_now > 1 / 7.0f)
			{
				Node* monsterNode = rootNode->getChildByName("MonsterNode");
				Armature* armature = (Armature*)monsterNode->getChildByName("MonsterArmature");
				num = PlayerData::getInstance()->getTapDps();
				PlayerData::getInstance()->subHp(num);
				normalAtk();
				armature->getAnimation()->play("Hurt", -1, 0);
				t_now = 0;
				if (PlayerData::getInstance()->getSkillopen(5))
				{
					auto num1 = Ruler::getInstance()->multiplay(PlayerData::getInstance()->getdefeatMonsterGold(), PlayerData::getInstance()->getSkillEFF(5) * (1 + ArtifactData::getInstance()->getskilleffUp(6)));
					PlayerData::getInstance()->addGold(&num1);
				}
				if (ShopData::getInstance()->getItemBeUsedById(1))
				{
					auto num2 = Ruler::getInstance()->multiplay(PlayerData::getInstance()->getdefeatMonsterGold(), 0.3);
					PlayerData::getInstance()->addGold(&num2);
				}
			}
		}
		if (PlayerData::getInstance()->getSkillopen(2))
		{
			PlayerData::getInstance()->setSkillexploreProb(PlayerData::getInstance()->getSkillEFF(2) *(1 + ArtifactData::getInstance()->getskilleffUp(3)));
		
		
		}
		if (PlayerData::getInstance()->getSkillopen(3))
		{
			auto mul = PlayerData::getInstance()->getSkillEFF(2) * (1 + ArtifactData::getInstance()->getskilleffUp(4));
			auto num = PlayerData::getInstance()->getTapDpsNoExp();
			num = Ruler::getInstance()->multiplay(num, dt * mul);
			PlayerData::getInstance()->subHp(num);

		}
		if (PlayerData::getInstance()->getSkillopen(4))
		{
			PlayerData::getInstance()->setSkillTap(PlayerData::getInstance()->getSkillEFF(4) *(1 + ArtifactData::getInstance()->getskilleffUp(5)));

		}
		
	}
	skillCDUpdate(dt);
	skillKpCDUpdate(dt);
	
}

void HelloWorld::normalAtk()
{
	
	Slider* slider = (Slider*)rootNode->getChildByName("UiNode")->getChildByName("HpSlider");

	if (PlayerData::getInstance()->getHpByID(PlayerData::getInstance()->getLevel()).Mathbit == PlayerData::getInstance()->getHpNow().Mathbit)
		slider->setPercent(PlayerData::getInstance()->getHpNow().number * 1000000);
	else if (PlayerData::getInstance()->getHpByID(PlayerData::getInstance()->getLevel()).Mathbit - PlayerData::getInstance()->getHpNow().Mathbit == 1)
		slider->setPercent(PlayerData::getInstance()->getHpNow().number * 1000);
	else if (PlayerData::getInstance()->getHpByID(PlayerData::getInstance()->getLevel()).Mathbit - PlayerData::getInstance()->getHpNow().Mathbit == 2)
		slider->setPercent(PlayerData::getInstance()->getHpNow().number);
	else if (PlayerData::getInstance()->getHpByID(PlayerData::getInstance()->getLevel()).Mathbit - PlayerData::getInstance()->getHpNow().Mathbit > 2)
		slider->setPercent(0);

	TextBMFont* tbm = (TextBMFont*)rootNode->getChildByName("UiNode")->getChildByName("HpSlider")->getChildByName("hpNow");
	tbm->setString(Ruler::getInstance()->showNum(PlayerData::getInstance()->getHpNow()));


	effectSprite = Sprite::create();
	Node* effection = (Node*)rootNode->getChildByName("normalAtk");
	effection->addChild(effectSprite);

	auto animate = Animate::create(ani);
	auto r = random(0, 360);
	auto rotate = RotateBy::create(0.0416f, Vec3(0, 0, r));
	auto spawn = Spawn::create(rotate, animate, CallFuncN::create(CC_CALLBACK_1(HelloWorld::playMusic, this)), NULL);

	auto seq = Sequence::create(spawn, CallFuncN::create(CC_CALLBACK_1(HelloWorld::deleteSprite, this)), NULL);
	
	effectSprite->runAction(seq);

	TextBMFont* text = (TextBMFont*)CSLoader::createNode("DmgNum.csb")->getChildByName("Text");
	text->retain();
	text->removeFromParent();

	Node* monsterNode = (Node*)rootNode->getChildByName("MonsterNode");
	Armature* armature = (Armature*)monsterNode->getChildByName("MonsterArmature");
	text->setPosition(Vec2(0, armature->getContentSize().height * 10 / 7));
	effection->addChild(text);
	text->release();
	text->setString(Ruler::getInstance()->showNum(num));


	auto textSeq = Sequence::create(MoveBy::create(1, Vec2(0, 300)), CallFuncN::create(CC_CALLBACK_1(HelloWorld::deleteSprite, this)), NULL);
	text->runAction(textSeq);
	AchieveData::getInstance()->tap();
}
void HelloWorld::attackeffection()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("effection/normalAttack.plist");
	ani = Animation::create();
	for (int i = 0; i < 9; i++)
	{
		ani->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("normalAttack_%d.png", i)));
	}
	ani->setDelayPerUnit(0.0416f);
	
	ani->retain();
}
void HelloWorld::deleteSprite(Node *node)
{
	node->removeFromParent();	
	
}

void HelloWorld::playMusic(Node * node)
{
	BgMusic::getInstance()->playEff();
}

void HelloWorld::initSer()
{
	ListView* lv = (ListView*)m_servantLayer->getChildByName("ListView");
	for (size_t i = 0; i <= PlayerData::getInstance()->getServantNum(); i++)
	{
		auto button = ServantButton::create();
		button->initServantLayer(i);
		auto widget = Widget::create();
		widget->setContentSize(button->getContentSize());
		widget->addChild(button);
		lv->pushBackCustomItem(widget);
	}		
}

void HelloWorld::initAr()
{	
	ListView* lv = (ListView*)m_artifactLayer->getChildByName("ListView");
	auto num = ArtifactData::getInstance()->getArNum();
	for (size_t i = 0; i < num; i++)
	{
		auto button = ArtifactButton::create();
		button->setTag(m_arCount);
		ArtifactData::getInstance()->getArtHaveByOrder(i);
		button->initArtifactLayer(ArtifactData::getInstance()->getArtHaveByOrder(i)->m_artifactID,true);
		auto widget = Widget::create();
		widget->setName("arWidget");
		auto size = button->getContentSize();
		widget->setContentSize(size);
		widget->addChild(button);
		button->setWidget(widget);
		lv->pushBackCustomItem(widget);
		lv->jumpToBottom();
		ArtifactButton::setListView(lv);
		ArtifactButton::setRootNode(m_artifactLayer);
	}
}
void HelloWorld::shopItemEff(float dt) 
{
	static float t_now;
	if (ShopData::getInstance()->getItemBeUsedById(0))
	{
		
		if (ShopData::getInstance()->getItemDataById(0)->leftTime / 1 != (ShopData::getInstance()->getItemDataById(0)->leftTime - dt) / 1)
		{
			showSiTime(0, ShopData::getInstance()->getItemDataById(0)->leftTime - dt);
		}
		ShopData::getInstance()->getItemDataById(0)->leftTime -= dt;
		if (ShopData::getInstance()->getItemDataById(0)->leftTime <= 0)
		{
			ShopData::getInstance()->stopItemById(0);
			ShopData::getInstance()->getItemDataById(0)->leftTime = 0;
		}
	}
	if(ShopData::getInstance()->getItemBeUsedById(1))
	{
		if (ShopData::getInstance()->getItemDataById(1)->leftTime / 1 != (ShopData::getInstance()->getItemDataById(1)->leftTime - dt) / 1)
		{
			showSiTime(1, ShopData::getInstance()->getItemDataById(1)->leftTime - dt);
		}
		ShopData::getInstance()->getItemDataById(1)->leftTime -= dt;
		if (ShopData::getInstance()->getItemDataById(1)->leftTime <= 0)
		{
			ShopData::getInstance()->stopItemById(1);
			ShopData::getInstance()->getItemDataById(1)->leftTime = 0;
		}
	}
	if (ShopData::getInstance()->getItemBeUsedById(2))
	{
		if (ShopData::getInstance()->getItemDataById(2)->leftTime / 1 != (ShopData::getInstance()->getItemDataById(2)->leftTime - dt) / 1)
		{
			showSiTime(2, ShopData::getInstance()->getItemDataById(2)->leftTime - dt);
		}
		ShopData::getInstance()->getItemDataById(2)->leftTime -= dt;
		if (ShopData::getInstance()->getItemDataById(2)->leftTime <= 0)
		{
			ShopData::getInstance()->stopItemById(2);
			ShopData::getInstance()->getItemDataById(2)->leftTime = 0;
		}
	}
	if (ShopData::getInstance()->getItemBeUsedById(3))
	{
		if (ShopData::getInstance()->getItemDataById(3)->leftTime / 1 != (ShopData::getInstance()->getItemDataById(3)->leftTime - dt) / 1)
		{
			showSiTime(3, ShopData::getInstance()->getItemDataById(3)->leftTime - dt);
		}
		ShopData::getInstance()->getItemDataById(3)->leftTime -= dt;
		PlayerData::getInstance()->subHp(Ruler::getInstance()->multiplay(PlayerData::getInstance()->getTapDpsNoExp(),10 * dt));
		if (ShopData::getInstance()->getItemDataById(3)->leftTime <= 0)
		{
			ShopData::getInstance()->stopItemById(3);
			ShopData::getInstance()->getItemDataById(3)->leftTime = SqLite::getInstance()->getItemByID(3)->time;
		}
	}
	if (MyState::getInstance()->getKTap() && ShopData::getInstance()->getItemBeUsedById(4))
	{
		if (ShopData::getInstance()->getItemDataById(4)->leftTime / 1 != (ShopData::getInstance()->getItemDataById(4)->leftTime - dt) / 1)
		{
			showSiTime(4, ShopData::getInstance()->getItemDataById(4)->leftTime - dt);
		}
		ShopData::getInstance()->getItemDataById(4)->leftTime -= dt;
		t_now += dt;
		if (t_now > 1 / 30.0f)
		{
			Node* monsterNode = rootNode->getChildByName("MonsterNode");
			Armature* armature = (Armature*)monsterNode->getChildByName("MonsterArmature");
			num = PlayerData::getInstance()->getTapDps();
			PlayerData::getInstance()->subHp(num);
			normalAtk();
			armature->getAnimation()->play("Hurt", -1, 0);
			t_now = 0;
			if (PlayerData::getInstance()->getSkillopen(5))
			{
				auto num1 = Ruler::getInstance()->multiplay(PlayerData::getInstance()->getdefeatMonsterGold(), PlayerData::getInstance()->getSkillEFF(5) * (1 + ArtifactData::getInstance()->getskilleffUp(6)));
				PlayerData::getInstance()->addGold(&num1);
			}
			if (ShopData::getInstance()->getItemBeUsedById(1))
			{
				auto num2 = Ruler::getInstance()->multiplay(PlayerData::getInstance()->getdefeatMonsterGold(), 0.3);
				PlayerData::getInstance()->addGold(&num2);
			}
		}
		if (ShopData::getInstance()->getItemDataById(4)->leftTime <= 0)
		{
			ShopData::getInstance()->stopItemById(4);
			ShopData::getInstance()->getItemDataById(4)->leftTime = 0;
		}
	}
	if (ShopData::getInstance()->getItemBeUsedById(5))
	{
		for (int i = 1; i < 7; i++)
		{
			if(m_skill[i - 1]->getChildByName("SkillCD"))
				m_skill[i - 1]->getChildByName("SkillCD")->removeFromParent();
			if(m_skill[i - 1]->getChildByName("SkillKpCD"))
				m_skill[i - 1]->getChildByName("SkillKpCD")->removeFromParent();
			m_skill[i - 1]->setEnabled(true);
		}
		ShopData::getInstance()->stopItemById(5);
	}
	if (ShopData::getInstance()->getItemBeUsedById(6))
	{
		ShopData::getInstance()->stopItemById(6);
	}
	if (ShopData::getInstance()->getItemBeUsedById(7))
	{
		ArtifactData::getInstance()->arStarUp();
		ShopData::getInstance()->stopItemById(7);
	}
	if (ShopData::getInstance()->getItemBeUsedById(9))
	{
		MyNum num;
		num.Mathbit = 0;
		num.number = 0;
		PlayerData::getInstance()->setHpNow(num);
		ShopData::getInstance()->stopItemById(9);
	}
	if (ShopData::getInstance()->getItemBeUsedById(10))
	{
		ShopData::getInstance()->getItemDataById(10)->leftTime -= dt;
		if (ShopData::getInstance()->getItemDataById(10)->leftTime / 1 != (ShopData::getInstance()->getItemDataById(10)->leftTime - dt) / 1)
		{
			showSiTime(10, ShopData::getInstance()->getItemDataById(10)->leftTime - dt);
		}
		if (ShopData::getInstance()->getItemDataById(10)->leftTime <= 0)
			ShopData::getInstance()->stopItemById(10);
	}
	if (ShopData::getInstance()->getItemBeUsedById(12))
	{
		ShopData::getInstance()->getItemDataById(12)->leftTime -= dt;
		if (ShopData::getInstance()->getItemDataById(12)->leftTime / 1 != (ShopData::getInstance()->getItemDataById(12)->leftTime - dt) / 1)
		{
			showSiTime(10, ShopData::getInstance()->getItemDataById(12)->leftTime - dt);
		}
		PlayerData::getInstance()->subHp(Ruler::getInstance()->multiplay(PlayerData::getInstance()->getTapDps(),10*dt));
		if (ShopData::getInstance()->getItemDataById(12)->leftTime <= 0)
		{
			ShopData::getInstance()->stopItemById(12);
			ShopData::getInstance()->getItemDataById(12)->leftTime = 0;
		}
			
	}
}
void HelloWorld::shopItemCDUpDate(float dt)
{
	for (int i = 0; i < 13; i++)
	{
		if (ShopData::getInstance()->getItemBeUsedById(i))
		{
			
			ShopData::getInstance()->getItemDataById(i)->leftTime -= dt;
			if (ShopData::getInstance()->getItemDataById(i)->leftTime / 1 != (ShopData::getInstance()->getItemDataById(i)->leftTime - dt) / 1)
			{
				showSiTime(10, ShopData::getInstance()->getItemDataById(i)->leftTime - dt);
			}
			if (ShopData::getInstance()->getItemDataById(i)->leftTime <= 0)
			{
				ShopData::getInstance()->stopItemById(i);
			}
		}
		
		
	}
	
}

void HelloWorld::dayChange()
{
	if (m_dayCount >=6)
	{
		m_signCount++;
		m_dayCount = 0;	
	}
	else
	{	
		m_dayCount++;
	}
	if (m_signCount > 1)
	{
		m_signCount = 0;
	}
}
//void HelloWorld::runAni()
//{
//
//	if (PlayerData::getInstance()->getServantNum() > 0)
//	{
//		if (!rootNode->getChildByName("Harmer"))
//		{
//			MyAnimation::getInstance()->runHarmer(true, rootNode);
//		}
//	}
//	if (PlayerData::getInstance()->getServantNum() >= 5)
//	{
//		if (!rootNode->getChildByName("aoshu"))
//		{
//			MyAnimation::getInstance()->runAoshu(true, rootNode);
//		}
//}
bool HelloWorld::mapInit()
{
	/*if (PlayerData::getInstance()->getLevel() == 0)
	{
		Sprite* mapL = (Sprite*)rootNode->getChildByName("UiNode")->getChildByName("Map")->getChildByName("MapOtherL");
		mapL->runAction(Hide::create());
		
	}*/
	if (PlayerData::getInstance()->getLevel() % 5 == 0)
	{
		auto mapNum = PlayerData::getInstance()->getLevel() / 5;
		auto map = SqLite::getInstance()->getMapDataByID(mapNum % 10);
		Sprite* bg = (Sprite*)rootNode->getChildByName("mainBG");
		bg->setTexture(StringUtils::format("map/bg/%s", map->bg.c_str()));
		Sprite* mapN = (Sprite*)rootNode->getChildByName("UiNode")->getChildByName("Map")->getChildByName("MapNow");
		mapN->setTexture(StringUtils::format("map/icon/%s", map->mapIcon.c_str()));
		Sprite* mapR = (Sprite*)rootNode->getChildByName("UiNode")->getChildByName("Map")->getChildByName("MapOtherR");
		mapR->setTexture(StringUtils::format("map/icon/%s", map->mapIcon.c_str()));
		Sprite* mapL = (Sprite*)rootNode->getChildByName("UiNode")->getChildByName("Map")->getChildByName("MapOtherL");
		if (PlayerData::getInstance()->getLevel() == 0)
		{
			mapL->runAction(Hide::create());
			TextBMFont* textLast = (TextBMFont*)rootNode->getChildByName("UiNode")->getChildByName("Map")->getChildByName("level");
			textLast->setString(StringUtils::format("%d", 1 + PlayerData::getInstance()->getLevel() - 1));
			TextBMFont* textNow = (TextBMFont*)rootNode->getChildByName("UiNode")->getChildByName("Map")->getChildByName("level_1");
			textNow->setString(StringUtils::format("%d", 1 + PlayerData::getInstance()->getLevel()));
			TextBMFont* textNext = (TextBMFont*)rootNode->getChildByName("UiNode")->getChildByName("Map")->getChildByName("level_0");
			textNext->setString(StringUtils::format("%d", 1 + PlayerData::getInstance()->getLevel() + 1));
		}
		else
		{
			auto mapNow = SqLite::getInstance()->getMapDataByID((mapNum - 1) % 10);
			mapL->setTexture(StringUtils::format("map/icon/%s", mapNow->mapIcon.c_str()));
			mapL->runAction(Show::create());
		}
		
	}
	else if ((PlayerData::getInstance()->getLevel() + 1) % 5 == 0)
	{
		auto mapNum = (PlayerData::getInstance()->getLevel() + 1) / 5;
		auto map = SqLite::getInstance()->getMapDataByID(mapNum  % 10 );
		Sprite* spr = (Sprite*)rootNode->getChildByName("UiNode")->getChildByName("Map")->getChildByName("MapOtherR");
		spr->setTexture(StringUtils::format("map/icon/%s", map->mapIcon.c_str()));
		auto mapNow = SqLite::getInstance()->getMapDataByID((mapNum-1) % 10);
		Sprite* bg = (Sprite*)rootNode->getChildByName("mainBG");
		bg->setTexture(StringUtils::format("map/bg/%s", mapNow->bg.c_str()));
		Sprite* mapL = (Sprite*)rootNode->getChildByName("UiNode")->getChildByName("Map")->getChildByName("MapOtherL");
		mapL->setTexture(StringUtils::format("map/icon/%s", mapNow->mapIcon.c_str()));
		Sprite* mapN = (Sprite*)rootNode->getChildByName("UiNode")->getChildByName("Map")->getChildByName("MapNow");
		mapN->setTexture(StringUtils::format("map/icon/%s", mapNow->mapIcon.c_str()));
		mapL->runAction(Show::create());

	}
	else
	{
		auto mapNum = (PlayerData::getInstance()->getLevel() - 1) / 5;
		auto map = SqLite::getInstance()->getMapDataByID(mapNum % 10);
		Sprite* spr = (Sprite*)rootNode->getChildByName("UiNode")->getChildByName("Map")->getChildByName("MapOtherL");
		spr->setTexture(StringUtils::format("map/icon/%s", map->mapIcon.c_str()));
		Sprite* bg = (Sprite*)rootNode->getChildByName("mainBG");
		bg->setTexture(StringUtils::format("map/bg/%s", map->bg.c_str()));
		Sprite* mapR = (Sprite*)rootNode->getChildByName("UiNode")->getChildByName("Map")->getChildByName("MapOtherR");
		mapR->setTexture(StringUtils::format("map/icon/%s", map->mapIcon.c_str()));
		Sprite* mapNow = (Sprite*)rootNode->getChildByName("UiNode")->getChildByName("Map")->getChildByName("MapNow");
		mapNow->setTexture(StringUtils::format("map/icon/%s", map->mapIcon.c_str()));
		Sprite* mapL = (Sprite*)rootNode->getChildByName("UiNode")->getChildByName("Map")->getChildByName("MapOtherL");
		mapL->runAction(Show::create());
	}
	return true;
}

void HelloWorld::gameContinue(Node*)
{
	auto waveN = PlayerData::getInstance()->getWaveNow();
	m_gamelogic = true;
}
void HelloWorld::showSiTime(int id, float dt)
{
	//显示倒计时，时间为dt
}

void HelloWorld::relife()
{
	mapInit();

	PlayerData::getInstance()->relifeEnd();
	auto scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(scene);
}

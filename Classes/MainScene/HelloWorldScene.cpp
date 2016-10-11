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
#include "Tool/CoinAnimation.h"
#include "Tool/Mask.h"
using namespace cocostudio;

USING_NS_CC;
USING_NS_CC_EXT;

using namespace ui;

bool HelloWorld::m_coutChange = false;

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
	m_kssjEffect = nullptr;
	auto leaveGold = new LeaveGold();
	BgMusic::getInstance()->playBg(PlayerData::getInstance()->getBg());
	m_hitlogic = true;
	m_heroLayer = nullptr;
	m_servantLayer = nullptr;
    m_artifactLayer = nullptr;
	m_shopLayer = nullptr;
	m_leaveText = nullptr;
	m_arCount = 0;
	m_exchangeCount = 5;
    rootNode = CSLoader::createNode("MainScene.csb");
	rootNode->setName("main");

	m_leaveText = CSLoader::createNode("LeaveGold.csb");
	rootNode->addChild(m_leaveText);
	m_leaveText->setPosition(rootNode->getContentSize() / 2);
	auto text = (Text*)m_leaveText->getChildByName("text");
	text->setVisible(false);
	auto img = (Sprite*)m_leaveText->getChildByName("img");
	img->setVisible(false);

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
			auto leveG = leaveGold->getGolds();
			PlayerData::getInstance()->addGold(&leveG);
			leaveBtn->setVisible(false);
			auto action = Sequence::create(DelayTime::create(5),CallFuncN::create(CC_CALLBACK_1(HelloWorld::leaveCallBack,this)),nullptr);
			auto text = (Text*)m_leaveText->getChildByName("text");
			auto img = (Sprite*)m_leaveText->getChildByName("img");
			img->setVisible(true);
			text->setString(Ruler::getInstance()->showNum(leveG).c_str());
			text->setVisible(true);
			text->runAction(action);	
			delete leaveGold;
		}
	});

	clickLayer = ClickLayer::create();
	clickLayer->setZOrder(-1);
	rootNode->addChild(clickLayer);
	uiInit();
	uiCallBack();
	createMonster();
	CCNotificationCenter::getInstance()->addObserver(this, callfuncO_selector(HelloWorld::coinChange), "CoinChange", nullptr);
	CCNotificationCenter::getInstance()->addObserver(this, callfuncO_selector(HelloWorld::playerChange), "playerChange", nullptr);
	showTime = false;
	Slider* timeSlider = (Slider*)rootNode->getChildByName("UiNode")->getChildByName("timeSlider");
	timeNow = PlayerData::getInstance()->getMaxTime();
	skillButtonInit();
	scheduleUpdate();
	coinChange(this);
	PlayerButton::getSkillLayer(rootNode->getChildByName("UiNode")->getChildByName("SkillLayer"));
	PlayerButton::getRootNode(rootNode);
	ServantButton::getRootNode(rootNode);
	TextBMFont* waveNum = (TextBMFont*)rootNode->getChildByName("UiNode")->getChildByName("Wave_Button")->getChildByName("WaveNum");
	waveNum->setString(StringUtils::format("%d/%d", PlayerData::getInstance()->getWaveNow(), PlayerData::getInstance()->getMaxWave() - 1));
	bossBt = nullptr;
	m_gamelogic = true;
	m_skilltimeSlider = rootNode->getChildByName("UiNode")->getChildByName("SkillLayer")->getChildByName("skill_time");
	m_skilltimeSliderShow = 0;
	m_exploreCoinNum = 0;
	//Mask::readUserdefault();
	if (Mask::step == 0)
	{
		auto mask = Mask::create();
		this->addChild(mask);
		mask->initAnimation();
	}

	 return true;
}
void HelloWorld::coinChange(Ref *ref)
{
	
	TextBMFont* gold = (TextBMFont*)rootNode->getChildByName("goldNum");
	gold->setString(Ruler::getInstance()->showNum(*PlayerData::getInstance()->getGold()));
	if (m_heroLayer)
	{
		m_heroLayer->setTag(0);
		TextBMFont* gold = (TextBMFont*)m_heroLayer->getChildByName("message")->getChildByName("gold");
		gold->setString(Ruler::getInstance()->showNum(*PlayerData::getInstance()->getGold()));
	}
	if (m_servantLayer)
	{
		m_servantLayer->setTag(1);
		TextBMFont* gold = (TextBMFont*)m_servantLayer->getChildByName("message")->getChildByName("gold");
		gold->setString(Ruler::getInstance()->showNum(*PlayerData::getInstance()->getGold()));
	}

	if (m_coutChange)
	{
		m_exchangeCount--;
		m_coutChange = false;
	}
	ExChange::setCount(m_exchangeCount);
}

void HelloWorld::ArChange(Ref* ref)
{
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
			auto armT = Armature::create("Effect_appear_dust");
			armT->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(HelloWorld::deleteArmature));
			armT->getAnimation()->playByIndex(0, -1, 0);
			armT->setPosition(0, -100);
			rootNode->getChildByName("normalAtk")->addChild(armT);
			if (MonsterState::getInstance()->getTypeNow() == MONSTER_TYPE::BOSS)
			{
				armT->setPosition(Vec2(0, -200));
				armT->setScale(2.0f);
			}
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
	}
	return;
}
void HelloWorld::createMonster()
{
	auto r = random(0, 4);
	
	Slider * hpSlider = (Slider*)rootNode->getChildByName("UiNode")->getChildByName("HpSlider");

	auto hpNum = PlayerData::getInstance()->getHpByID(PlayerData::getInstance()->getLevel());
	auto hpS = hpNum.number;
	hpS *= 1000000;
	hpSlider->setMaxPercent(hpS);
	hpSlider->setPercent(hpS);

	TextBMFont* tbm = (TextBMFont*)rootNode->getChildByName("UiNode")->getChildByName("HpSlider")->getChildByName("hpNow");
	tbm->setString(Ruler::getInstance()->showNum(PlayerData::getInstance()->getHpByID(PlayerData::getInstance()->getLevel())));
	PlayerData::getInstance()->setHpNow(PlayerData::getInstance()->getHpByID(PlayerData::getInstance()->getLevel()));
	

	Slider* timeSlider = (Slider*)rootNode->getChildByName("UiNode")->getChildByName("timeSlider");
	if (PlayerData::getInstance()->getWaveNow() == PlayerData::getInstance()->getMaxWave())
	{
		
		PlayerData::getInstance()->resetTime();
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
		else
		{
			MonsterState::getInstance()->setSaveBoss(false);
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
	MonsterData* monster;
	if (MonsterState::getInstance()->getTypeNow() == MONSTER_TYPE::BOSS)
	{
		if (!MonsterState::getInstance()->getSaveBoss())
		{
			MonsterState::getInstance()->saveBoss(SqLite::getInstance()->getMonsterByID(PlayerData::getInstance()->getRandNpc(r)));
			monster = MonsterState::getInstance()->getBoss();
		}
		else
			monster = MonsterState::getInstance()->getBoss();
	}
	else
	{
		
		monster = SqLite::getInstance()->getMonsterByID(PlayerData::getInstance()->getRandNpc(r));
	}
	ArmatureDataManager::getInstance()->addArmatureFileInfo(monster->png, monster->plist, monster->exportJson);//读取动画相关文件
	armature = Armature::create(monster->name);
	armature->setName("MonsterArmature");
	armature->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(HelloWorld::callBackFunc));
	Node* monsterNode = (Node*)rootNode->getChildByName("MonsterNode");
	armature->getAnimation()->play("Start");
	if (MonsterState::getInstance()->getTypeNow() == MONSTER_TYPE::BOSS)
	{
	
		auto armT = Armature::create("Effect_nextmap");
		armT->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(HelloWorld::deleteArmature));
		armT->getAnimation()->playByIndex(0, -1, 0);
		armT->getAnimation()->setSpeedScale(4.0f);
		//armT->setScale(0.5f);
		auto lable = Sprite::create("boss.png");
		lable->setScale(0.5);
		auto seq = Sequence::create(Hide::create(), DelayTime::create(0.25f), Show::create(), DelayTime::create(0.7f), CallFuncN::create(CC_CALLBACK_1(HelloWorld::deleteSprite, this)), NULL);
		lable->runAction(seq);
		rootNode->getChildByName("normalAtk")->addChild(armT,1);
		rootNode->getChildByName("normalAtk")->addChild(lable,2);
		armature->setScale(2.0f);
		armature->setPosition(0, -100);
	}
	else
	{
		armature->setScale(1.5f);
	}
	monsterNode->addChild(armature);
	PlayerData::getInstance()->saveUserData();
}
void HelloWorld::update(float dt)
{
	
	if (Mask::step == 1 && !Mask::existing)
	{
		auto num = MyNum();
		num.number = 1;
		num.Mathbit = 0;
		if (Ruler::getInstance()->Zero(Ruler::getInstance()->subNum(num, *PlayerData::getInstance()->getGold())))
		{
			auto mask = Mask::create();
			this->addChild(mask);
			mask->initAnimation();
		}
	}
	if (Mask::step == 2 && !Mask::existing)
	{
		if (m_heroLayer)
		{
			
			auto mask = Mask::create();
			this->addChild(mask);
			mask->initAnimation();
			
		}
	}
	if (Mask::step == 3 && !Mask::existing)
	{
		auto num = MyNum();
		num = SqLite::getInstance()->getServantGoldByID(0);
		if (Ruler::getInstance()->Zero(Ruler::getInstance()->subNum(num, *PlayerData::getInstance()->getGold())))
		{
			auto mask = Mask::create();
			this->addChild(mask);
			mask->initAnimation();
		}
	}
	if (Mask::step == 4 && !Mask::existing)
	{
		if (m_servantLayer)
		{
			auto mask = Mask::create();
			this->addChild(mask);
			mask->initAnimation();
		}
	}
	if (Mask::step == 5 && !Mask::existing)
	{
		if (PlayerData::getInstance()->getPlayerLevel() >= 50)
		{
			auto num = MyNum();
			num = SqLite::getInstance()->getSkillData().at(0)->unlockGold;
			if (Ruler::getInstance()->Zero(Ruler::getInstance()->subNum(num, *PlayerData::getInstance()->getGold())))
			{
				auto mask = Mask::create();
				this->addChild(mask);
				mask->initAnimation();
			}
		}
		
	}
	if (Mask::step == 6 && !Mask::existing)
	{
		
		if (m_heroLayer)
		{
			auto mask = Mask::create();
			this->addChild(mask);
			mask->initAnimation();
		}
	}
	saveSkillCD(dt);
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
			if (PlayerData::getInstance()->getHpNow().number <= 0)
			{
				MyNum zero;
				PlayerData::getInstance()->setHpNow(zero);
			}
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
				/*auto n = 1;
				for (int i = 0; i < 7; i++)
				{
					n = i + 1;
					if (SqLite::getInstance()->getSkillData().at(i)->needLevel < PlayerData::getInstance()->getPlayerLevel())
						continue;
					else
						break;
				}*/
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
				lv->setName("shop");
				for (size_t i = 0; i < 13; i++)
				{
					if (i == 6)
					{

					}
					else
					{
						auto widget = Widget::create();
						widget->setName(StringUtils::format("shopWidget%d", i).c_str());
						auto item = ItemLayer::create();
						item->setNode(rootNode);
						item->setName(StringUtils::format("shopItem%d", i).c_str());
						item->initItemLayer(i);
						auto size = item->getContentSize();
						widget->setContentSize(size);
						widget->addChild(item);
						widget->setTag(i);
						lv->pushBackCustomItem(widget);
						cocos2d::CCNotificationCenter::getInstance()->postNotification("itemChange");
					}	
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
		//PlayerData::getInstance()->defeatMonsterGold();
		coinAni();
		if (PlayerData::getInstance()->getWaveNow() < PlayerData::getInstance()->getMaxWave() - 1 && PlayerData::getInstance()->getWaveNow() != 0)
		{
			PlayerData::getInstance()->waveUp();

			waveNum->setString(StringUtils::format("%d/%d", PlayerData::getInstance()->getWaveNow(), PlayerData::getInstance()->getMaxWave() - 1));
		}
		else if (PlayerData::getInstance()->getWaveNow() == PlayerData::getInstance()->getMaxWave() - 1)
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
			textLast->setString(StringUtils::format("%d", 1 + PlayerData::getInstance()->getLevel() - 1));
			TextBMFont* textNow = (TextBMFont*)rootNode->getChildByName("UiNode")->getChildByName("Map")->getChildByName("level_1");
			textNow->setString(StringUtils::format("%d", 1 + PlayerData::getInstance()->getLevel()));
			TextBMFont* textNext = (TextBMFont*)rootNode->getChildByName("UiNode")->getChildByName("Map")->getChildByName("level_0");
			textNext->setString(StringUtils::format("%d", 1 + PlayerData::getInstance()->getLevel() + 1));
			Node* bossButtonNode = (Node*)rootNode->getChildByName("UiNode")->getChildByName("Wave_Button")->getChildByName("escapeBoss");
			bossButtonNode->removeChildByName("bt");
			waveNum->setString(StringUtils::format("%d/%d", PlayerData::getInstance()->getWaveNow(), PlayerData::getInstance()->getMaxWave() - 1));
			waveNum->runAction(Show::create());
		}
		auto hpnow = PlayerData::getInstance()->getHpNow();
		armature->getAnimation()->play("Leave");
	
		if (MonsterState::getInstance()->getTypeNow() == MONSTER_TYPE::RARE)
		{
			MissionData::getInstance()->addMissionTimesById(0);
			AchieveData::getInstance()->killRareMonster();
			AchieveData::getInstance()->killMonster();
		}
		if (MonsterState::getInstance()->getTypeNow() == MONSTER_TYPE::BOSS)
		{
			MissionData::getInstance()->addMissionTimesById(1);
			AchieveData::getInstance()->killBoss();
		}
		else
		{
			MissionData::getInstance()->addMissionTimesById(0);
			AchieveData::getInstance()->killMonster();
		}
		
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
		auto animate = MyAnimation::getInstance()->getAnimate_xy();
		effect->setScale(5);
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
				ArtifactData::getInstance()->subArtiStone(ArtifactData::getInstance()->getNeededArStone());
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
	CCNotificationCenter::getInstance()->addObserver(this, callfuncO_selector(HelloWorld::ArChange), "ArtiChange", nullptr);
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
	CCNotificationCenter::getInstance()->addObserver(this, callfuncO_selector(HelloWorld::itemChange), "itemChange", nullptr);
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
				if (m_shopLayer)
				{
					Button* bt = (Button*)m_shopLayer->getChildByName("shop")->getChildByTag(5)->getChildByTag(0)->getChildByTag(0)->getChildByName("bg")->getChildByName("up");
					bt->setEnabled(true);
				}
			
				if (i != 1)
				{
					m_skilltimeSlider->runAction(Show::create());
					auto skillSp = Sprite::create(StringUtils::format("skillCD/s%d.png", i));
					skillSp->setPosition(skillSp->getContentSize() / 2);
					auto seq = Sequence::create(CallFuncN::create(CC_CALLBACK_0(HelloWorld::addSktShow, this)), MoveBy::create(PlayerData::getInstance()->getKeepTime(i), Vec2(800, 0)), CallFuncN::create(CC_CALLBACK_1(HelloWorld::deleteSprite, this)), CallFuncN::create(CC_CALLBACK_0(HelloWorld::delSktShow, this)), NULL);
					m_skilltimeSlider->addChild(skillSp);
					skillSp->runAction(seq);
				}
				if (i == 2)
				{
					if (!m_kssjEffect)
					{
						m_kssjEffect = Sprite::create();
						m_kssjEffect->retain();
					}					
					m_kssjEffect->setScale(4.0f);
					m_kssjEffect->setColor(Color3B(0, 0, 0));
					auto animate = MyAnimation::getInstance()->getAnimate_kssj();
					auto kptime = PlayerData::getInstance()->getKeepTime(i);
					kptime *=(1 + ArtifactData::getInstance()->getskillTimeA(i));
					auto t1 = animate->getAnimation()->getDelayPerUnit();
					auto t2 = animate->getAnimation()->getTotalDelayUnits();
					auto num = kptime / (t1*t2);
					auto seq = Sequence::create(Repeat::create(animate, kptime / (t1*t2)), CallFuncN::create(CC_CALLBACK_1(HelloWorld::deleteSprite, this)), NULL);
					rootNode->getChildByName("normalAtk")->addChild(m_kssjEffect);
					m_kssjEffect->runAction(seq);
					MyAnimation::getInstance()->setKSSJplaying(true);
				}
				if (i == 3)
				{
					
					auto armT = Armature::create("Effect_strike_hunter");
					armT->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(HelloWorld::deleteArmature));
					armT->getAnimation()->playByIndex(0,-1,0);
					armT->setScale(2.0f);
					rootNode->getChildByName("normalAtk")->addChild(armT);

				}
				if (i == 4)
				{
					auto effect = Sprite::create();
					effect->setPosition(100, -100);
					effect->setScale(20.0f);
					auto animate = MyAnimation::getInstance()->getAnimate_bfx();
					auto kptime = PlayerData::getInstance()->getKeepTime(i);
					kptime *= (1 + ArtifactData::getInstance()->getskillTimeA(i));
					auto t1 = animate->getAnimation()->getDelayPerUnit();
					auto t2 = animate->getAnimation()->getTotalDelayUnits();
					auto num = kptime / (t1*t2);
					auto seq = Sequence::create(Repeat::create(animate, kptime / (t1*t2)), CallFuncN::create(CC_CALLBACK_1(HelloWorld::deleteSprite, this)), NULL);
					rootNode->getChildByName("normalAtk")->addChild(effect);
					effect->runAction(seq);
				}
				if (i == 5)
				{
					auto effectSx = Sprite::create();
					auto animateSx = MyAnimation::getInstance()->getAnimate_sx();
					auto seqSx = Sequence::create(animateSx, CallFuncN::create(CC_CALLBACK_1(HelloWorld::deleteSprite, this)), NULL);
					//rootNode->getChildByName("normalAtk")
					rootNode->getChildByName("normalAtk")->addChild(effectSx);
					effectSx->runAction(RepeatForever::create(seqSx));
					auto effetsxk = Sprite::create("SpecialEffect/sxSprite9.png");
					effectSx->setPosition(Vec2(0, 100));
					effetsxk->setScale(11.0f,10.5f);
					auto actionSxk = MyAnimation::getInstance()->getAction_sx();
					effetsxk->setPosition(0,100);
					auto kptime = PlayerData::getInstance()->getKeepTime(i);
					kptime *= (1 + ArtifactData::getInstance()->getskillTimeA(i));
					auto seqSxk = Sequence::create(Repeat::create(actionSxk, kptime / 2), CallFuncN::create(CC_CALLBACK_1(HelloWorld::deleteSprite, this)), NULL);
					rootNode->getChildByName("normalAtk")->addChild(effetsxk);
					effetsxk->runAction(seqSxk);

				}
				if (i == 6)
				{
					auto effect = Sprite::create();
					effect->setScale(3.5f);
					auto animate = MyAnimation::getInstance()->getAnimate_tq();
					auto seq = Sequence::create(animate, CallFuncN::create(CC_CALLBACK_1(HelloWorld::deleteSprite, this)), NULL);
					rootNode->getChildByName("normalAtk")->addChild(effect);
					effect->runAction(seq);
				}
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
			
			auto armT = Armature::create("Effect_strike_warrior");
			armT->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(HelloWorld::skilleff1));
			armT->getAnimation()->playByIndex(0, -1, 0);
			armT->setScale(3.0f);
			rootNode->getChildByName("normalAtk")->addChild(armT);
						
		}
		if ( PlayerData::getInstance()->getSkillopen(1))
		{
			
			if (MyState::getInstance()->getKTap())
			{
				if (!MyAnimation::getInstance()->getKSSJplaying())
				{
					if (m_kssjEffect->isRunning())
					{
						m_kssjEffect->runAction(Show::create());
						MyAnimation::getInstance()->setKSSJplaying(true);
					}
					
				}
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
			else
			{
				if (MyAnimation::getInstance()->getKSSJplaying())
				{
					if (m_kssjEffect->isRunning())
					{
						m_kssjEffect->runAction(Hide::create());
					}
					MyAnimation::getInstance()->setKSSJplaying(false);
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
	if (PlayerData::getInstance()->getHpNow().number < 0)
	{
		MyNum num0;
		PlayerData::getInstance()->setHpNow(num0);
	}
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


	
	Node* effection = (Node*)rootNode->getChildByName("normalAtk");
	/*effectSprite = Sprite::create();
	effection->addChild(effectSprite);*/
	auto armT = Armature::create("Effect_PK_hit1");
	armT->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(HelloWorld::deleteArmature));
	armT->getAnimation()->playByIndex(0, -1, 0);
	effection->addChild(armT);
	auto r = random(0, 360);
	/*auto rotate = RotateBy::create(0.0416f, Vec3(0, 0, r));
	auto spawn = Spawn::create(rotate, animate, NULL);*/

	//effectSprite->runAction(seq);
	//effectSprite->setScale(2.0f);
	Text* text = (Text*)CSLoader::createNode("DmgNum.csb")->getChildByName("Text");
	text->setColor(Color3B(255, 0, 0));
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
//void HelloWorld::attackeffection()
//{
//	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("effection/normalAttack.plist");
//	ani = Animation::create();
//	for (int i = 1; i < 13; i++)
//	{
//		ani->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("normalAttack_%d.png", i)));
//	}
//	ani->setDelayPerUnit(0.0416f);
//	
//	ani->retain();
//}
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
		if (!MyAnimation::getInstance()->getFNTTplaying())
		{
			m_fnttEffect = Sprite::create();
			auto animate = MyAnimation::getInstance()->getAnimate_fn();
			m_fnttEffect->setScale(2.0f);
			rootNode->getChildByName("normalAtk")->addChild(m_fnttEffect);
			m_fnttEffect->runAction(RepeatForever::create(animate));
			MyAnimation::getInstance()->setFNTTplaying(true);
		}
		ShopData::getInstance()->getItemDataById(3)->leftTime -= dt;
		PlayerData::getInstance()->subHp(Ruler::getInstance()->multiplay(PlayerData::getInstance()->getTapDpsNoExp(),10 * dt));
		if (ShopData::getInstance()->getItemDataById(3)->leftTime <= 0)
		{
			ShopData::getInstance()->stopItemById(3);
			ShopData::getInstance()->getItemDataById(3)->leftTime = 0;
			MyAnimation::getInstance()->setFNTTplaying(false);
			m_fnttEffect->removeFromParent();
		}
	}
	if (ShopData::getInstance()->getItemBeUsedById(4))
	{
		if (ShopData::getInstance()->getItemDataById(4)->leftTime / 1 != (ShopData::getInstance()->getItemDataById(4)->leftTime - dt) / 1)
		{

			showSiTime(4, ShopData::getInstance()->getItemDataById(4)->leftTime - dt);
			ShopData::getInstance()->getItemDataById(4)->leftTime -= dt;
		}
		if (MyState::getInstance()->getKTap())
		{		
			
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
			ImageView* skt = (ImageView*)rootNode->getChildByName("UiNode")->getChildByName("SkillLayer")->getChildByName("skill_time");
			skt->removeAllChildren();
			m_skilltimeSliderShow = 0;
			PlayerData::getInstance()->closeSkill(i - 1);
			for (size_t i = 0; i < 6; i++)
			{
				PlayerData::getInstance()->setSkillCD(i + 1, 0);
			}
		}
		if (m_shopLayer)
		{
			
			/*Button* bt = (Button*)m_shopLayer->getChildByName("shop")->getChildByTag(5)->getChildByTag(0)->getChildByTag(0)->getChildByName("bg")->getChildByName("up");
			bt->setEnabled(false);*/
		}
		ShopData::getInstance()->stopItemById(5);
	}
	if (ShopData::getInstance()->getItemBeUsedById(6))
	{
		ShopData::getInstance()->stopItemById(6);
	}
	if (ShopData::getInstance()->getItemBeUsedById(7))
	{
		
		ShopData::getInstance()->stopItemById(7);
	}
	if (ShopData::getInstance()->getItemBeUsedById(9))
	{	
		auto armT = Armature::create("Effect_strike_magister");
		armT->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(HelloWorld::itemEff9));
		armT->getAnimation()->playByIndex(0, -1, 0);
		armT->setScale(3.0);
		rootNode->getChildByName("normalAtk")->addChild(armT);
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
		{
			ShopData::getInstance()->stopItemById(10);
		}
	}
	if (ShopData::getInstance()->getItemBeUsedById(11))
	{
		ShopData::getInstance()->getItemDataById(11)->leftTime -= dt;
		if (ShopData::getInstance()->getItemDataById(11)->leftTime / 1 != (ShopData::getInstance()->getItemDataById(11)->leftTime - dt) / 1)
		{
			showSiTime(11, ShopData::getInstance()->getItemDataById(11)->leftTime - dt);
		}
		if (ShopData::getInstance()->getItemDataById(11)->leftTime <= 0)
		{
			ShopData::getInstance()->stopItemById(11);
		}
	}
	if (ShopData::getInstance()->getItemBeUsedById(12))
	{
		if (!MyAnimation::getInstance()->getKLGJplaying())
		{
			m_klgjEffect = Sprite::create();
			m_klgjEffect->setScale(3.0);
			m_klgjEffect->setColor(Color3B(255, 0, 0));
			auto animate = MyAnimation::getInstance()->getAnimate_kl();
			//m_klgjEffect->setAnchorPoint(Vec2(0, 0));
			//auto seq = Sequence::create(animate, CallFuncN::create(CC_CALLBACK_1(HelloWorld::bgChange, this)), CallFuncN::create(CC_CALLBACK_1(HelloWorld::deleteSprite, this)), CallFuncN::create(CC_CALLBACK_1(HelloWorld::gameContinue, this)), NULL);
			rootNode->getChildByName("normalAtk")->addChild(m_klgjEffect);
			m_klgjEffect->runAction(RepeatForever::create(animate));
			MyAnimation::getInstance()->setKLGJplaying(true);
		}
		auto tmpTime = ShopData::getInstance()->getItemDataById(12)->leftTime;
		ShopData::getInstance()->getItemDataById(12)->leftTime -= dt;
		if (ShopData::getInstance()->getItemDataById(12)->leftTime / 1 != (ShopData::getInstance()->getItemDataById(12)->leftTime - dt) / 1)
		{
			showSiTime(12, ShopData::getInstance()->getItemDataById(12)->leftTime - dt);
		}
		PlayerData::getInstance()->subHp(Ruler::getInstance()->multiplay(PlayerData::getInstance()->getTapDps(),10*dt));
		if (ShopData::getInstance()->getItemDataById(12)->leftTime <= 0)
		{
			
			ShopData::getInstance()->getItemDataById(12)->leftTime = 0;
			MyAnimation::getInstance()->setKLGJplaying(false);
			m_klgjEffect->removeFromParent();
			ShopData::getInstance()->stopItemById(12);
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
			/*if (ShopData::getInstance()->getItemDataById(i)->leftTime <= 0)
			{
				
				ShopData::getInstance()->stopItemById(i);
				
			}*/
		}
		
		
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
	if (dt < ShopData::getInstance()->getNum(id))
	{
		CCNotificationCenter::getInstance()->postNotification("itemChange");
	}
}

void HelloWorld::relife()
{
	mapInit();
	PlayerData::getInstance()->relifeEnd();
	auto sceneDel = this->getParent();
	auto scene = HelloWorld::createScene();
	scene->retain();
	Director::getInstance()->replaceScene(scene);
	if (sceneDel)
	sceneDel->release();
}
void HelloWorld::skilleff1(Armature * armature, MovementEventType type, const std::string& action)
{
	if (type == MovementEventType::LOOP_COMPLETE || type == MovementEventType::COMPLETE)
	{
		PlayerData::getInstance()->subHp(Ruler::getInstance()->multiplay(PlayerData::getInstance()->getTapDps(), PlayerData::getInstance()->getSkillEFF(0) * (1 + ArtifactData::getInstance()->getskilleffUp(1))));
		armature->removeFromParent();
		m_hitlogic = true;
	}
	
}
void HelloWorld::skilleff2(Ref*)
{
	
}
void HelloWorld::deleteArmature(Armature * armature, MovementEventType type, const std::string& action)
{
	if (type == MovementEventType::LOOP_COMPLETE || type == MovementEventType::COMPLETE)
	{
		armature->removeFromParent();
		
	}
}
void HelloWorld::itemEff9(Armature * armature, MovementEventType type, const std::string& action)
{
	if (type == MovementEventType::LOOP_COMPLETE || type == MovementEventType::COMPLETE)
	{
		MyNum num;
		num.Mathbit = 0;
		num.number = 0;
		armature->removeFromParent();
		PlayerData::getInstance()->setHpNow(num);
	}
}

void HelloWorld::skillButtonInit()
{
	for (int i = 1; i < 7; i++)
	{
		if (PlayerData::getInstance()->getSkillLevel(i)>0)
		{
			auto str = StringUtils::format("SkillButton%d", i);
			Button* skillbt = (Button*)rootNode->getChildByName("UiNode")->getChildByName("SkillLayer")->getChildByName(str);
			skillbt->runAction(Show::create());
			if (PlayerData::getInstance()->getSkillCD(i) > 0)
			{
				auto skillCD = SkillCD::create();
				skillCD->initImage(i,PlayerData::getInstance()->getSkillCD(i));

				skillCD->setPosition(m_skill[i - 1]->getContentSize() / 2);

				m_skill[i - 1]->addChild(skillCD);
				skillCD->setName("SkillCD");

				m_skill[i - 1]->setEnabled(false);
			}
		}
	}

}
void HelloWorld::saveSkillCD(float dt)
{
	static float time_0 = 0;
	time_0 += dt;
	if (time_0 >= 1)
	{
		bool save = false;
		for (int i = 0; i < 6; i++)
		{
			if (PlayerData::getInstance()->getSkillCD(i)>0)
			{
				save = true;
				break;
			}

		}
		if (save)
		{
			PlayerData::getInstance()->saveUserData();
		}
		time_0 = 0;
	}

}
void HelloWorld::coinAni()
{
	auto coinnum = random(3, 5);
	for (int i = 0; i < coinnum; i++)
	{
		Button* gold = Button::create("SpecialEffect/gold.png", "SpecialEffect/gold.png", "SpecialEffect/gold.png");
		gold->setEnabled(false);
		rootNode->getChildByName("normalAtk")->addChild(gold);
		auto knum = CoinAnimation::getInstance()->getKnum();
		auto xMove = random(-400, 400);
		auto jumpNum = random(1, 3);
		auto seq = Sequence::create(JumpBy::create(0.5, Point(xMove, -300), abs(xMove)*knum, 1), JumpBy::create(0.5, Point(xMove / 5, 0), 50, jumpNum), DelayTime::create(3), CallFuncN::create(CC_CALLBACK_1(HelloWorld::goldenUp, this,coinnum, PlayerData::getInstance()->defeatMonsterGold())), JumpTo::create(1, Point(-65, 400), 50, 1), CallFuncN::create(CC_CALLBACK_1(HelloWorld::deleteSprite, this)), CallFuncN::create(CC_CALLBACK_1(HelloWorld::delexploreCoin, this, coinnum, PlayerData::getInstance()->defeatMonsterGold())), NULL);
		gold->runAction(seq);
	}
	
	
}
void HelloWorld::delexploreCoin(Ref*,int num,MyNum Defeatgold)
{

	MyNum n;
	n.Mathbit = 0;
	n.number = num;
	auto gold = Ruler::getInstance()->devide(Defeatgold, n);
	PlayerData::getInstance()->addGold(&gold);
}

void HelloWorld::leaveCallBack(Node * node)
{
	auto text = (Text*)m_leaveText->getChildByName("text");
	text->setVisible(false);
	auto img = (Sprite*)m_leaveText->getChildByName("img");
	img->setVisible(false);
}
void HelloWorld::goldenUp(Node* node,int num,MyNum Defeatgold)
{
	auto goldNum = CSLoader::getInstance()->createNode("DmgNum.csb");
	goldNum->setColor(Color3B(254, 254, 65));
	this->addChild(goldNum);
	auto pos = 	node->getParent()->convertToWorldSpace(node->getPosition());
	pos = pos + Point(0, 20);
	MyNum n;
	n.Mathbit = 0;
	n.number = num;
	auto gold = Ruler::getInstance()->devide(Defeatgold, n);
	Text* goldNumText = (Text*)goldNum->getChildByName("Text");
	goldNumText->setString(Ruler::getInstance()->showNum(gold));
	goldNum->setPosition(pos);
	auto seq = Sequence::create(MoveBy::create(0.5, Vec2(0, 200)), CallFuncN::create(CC_CALLBACK_1(HelloWorld::deleteSprite, this)), NULL);
	goldNum->runAction(seq);
}

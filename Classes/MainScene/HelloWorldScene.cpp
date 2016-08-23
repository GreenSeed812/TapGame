#include "HelloWorldScene.h"

#include "Tool/Rule.h"
#include "Tool/SqLite.h"
#include <cocostudio/CocoStudio.h>
#include "cocos-ext.h"
#include "MainScene/ClickLayer.h"
#include "SaveData/PlayerData.h"
#include "Tool/Rule.h"
#include "MainScene/PlayerButton.h"
#include "MainScene/ServantButton.h"
#include "SaveData/State.h"
#include "Ui/settingLayer.h"
#include "Ui/AchieveLayer.h"
#include "Ui/MissionLayer.h"
#include "Ui/SignLayer.h"
#include "SkillCD.h"
using namespace cocostudio;

USING_NS_CC;
USING_NS_CC_EXT;

using namespace ui;


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
	{
		MyNum num;
		num.Mathbit = 2;
		num.number = 1;
		PlayerData::getInstance()->addGold(&num);

	}
	
	m_heroLayer = nullptr;
	m_servantLayer = nullptr;
    m_artifactLayer = nullptr;
	m_shopLayer = nullptr;
    rootNode = CSLoader::createNode("MainScene.csb");
	addChild(rootNode);
	Slider * hpSlider = (Slider*)rootNode->getChildByName("UiNode")->getChildByName("HpSlider");
	hpSlider->setTouchEnabled(false);
	
	clickLayer = ClickLayer::create();
	clickLayer->setZOrder(-1);
	rootNode->addChild(clickLayer);
	clickLayer->effectInit();
	uiInit();
	uiCallBack();
	createMonster();
	CCNotificationCenter::getInstance()->addObserver(this, callfuncO_selector(HelloWorld::coinChange), "CoinChange", nullptr);
	showTime = false;
	Slider* timeSlider = (Slider*)rootNode->getChildByName("UiNode")->getChildByName("timeSlider");
	timeSlider->setMaxPercent(PlayerData::getInstance()->getMaxTime());
	timeNow = PlayerData::getInstance()->getMaxTime();

	schedule(schedule_selector(HelloWorld::skillKpCDUpdate), 1.0f);
	coinChange(this);
	
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
}
void HelloWorld::callBackFunc(Armature * armature, MovementEventType type, const std::string& action)
{
	static bool dead;
	if (type == MovementEventType::LOOP_COMPLETE || type == MovementEventType::COMPLETE)
	{
		if (action == "Start")
		{
			
			clickLayer->setTouchEnabled(true);
			armature->getAnimation()->play("Wait");
			scheduleUpdate();
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
		killBoss();
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
		armature->setScale(2.0f);
		timeNow = PlayerData::getInstance()->getMaxTime();
		timeSlider->runAction(Show::create());
		timeSlider->setPercent(timeNow);
		rootNode->getChildByName("dragon")->runAction(Show::create());
	}
	else if (PlayerData::getInstance()->getWaveNow()<=1)
	{
		timeSlider->runAction(Hide::create());
		rootNode->getChildByName("dragon")->runAction(Hide::create());
		
	}
	
}
void HelloWorld::update(float dt)
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
	if (m_heroLayer)
	{
		TextBMFont* dps = (TextBMFont*)m_heroLayer->getChildByName("message")->getChildByName("Dps");
		dps->setString(Ruler::getInstance()->showNum(PlayerData::getInstance()->getDps()).c_str());
	}
	if (m_servantLayer)
	{
		TextBMFont* dps = (TextBMFont*)m_servantLayer->getChildByName("message")->getChildByName("Dps");
		dps->setString(Ruler::getInstance()->showNum(heroDps));
	}
	if (PlayerData::getInstance()->getWaveNow() == 11)
	{
		Slider* timeSlider = (Slider*)rootNode->getChildByName("UiNode")->getChildByName("timeSlider");
		
		timeNow -= dt * 1000;
		if (timeNow <= 0)
		{
			PlayerData::getInstance()->setWave(0);
			MyState::getInstance()->setBossButtonDown(true);
			timeNow = PlayerData::getInstance()->getMaxTime();
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
	killBoss();
	

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
	Node* node = rootNode->getChildByName("UiNode")->getChildByName("SkillLayer");
	for (int i = 1; i < 7;i++)
	{
		m_skill[i - 1] = (Button*)node->getChildByName(StringUtils::format("SkillButton%d", i));
		
		m_skill[i - 1]->addTouchEventListener([this,i](Ref* sender, Widget::TouchEventType type){
			if (type == Widget::TouchEventType::ENDED)
			{
				auto skillCD = SkillCD::create();
				skillCD->initImage(i);
				skillCD->setPosition(m_skill[i - 1]->getContentSize() / 2);
				auto skillKpCD = SkillCD::create();
				skillKpCD->initkpImage(i);
				skillKpCD->setPosition(m_skill[i - 1]->getContentSize() / 2);
				m_skill[i - 1]->addChild(skillCD);
				m_skill[i - 1]->addChild(skillKpCD,1);
				skillKpCD->setName("SkillKpCD");
				skillCD->setName("SkillCD");
				
			}
		});
	
	}
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
				dps->setString(Ruler::getInstance()->showNum(PlayerData::getInstance()->getHeroDps()));
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
				ListView* lv = (ListView*)m_heroLayer->getChildByName("ListView");
				for (auto child: lv->getChildren())
				{
					child->scheduleUpdate();
				}
			}
		
			
			
		}
	});
	servantButton->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
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
			if (initDownLayer(m_servantLayer))
			{

				ListView* lv = (ListView*)m_servantLayer->getChildByName("ListView");
				ServantButton::getListView(lv);
				TextBMFont* dps = (TextBMFont*)m_servantLayer->getChildByName("message")->getChildByName("Dps");
				dps->setString(Ruler::getInstance()->showNum(PlayerData::getInstance()->getDps()));
				TextBMFont* gold = (TextBMFont*)m_servantLayer->getChildByName("message")->getChildByName("gold");
				gold->setString(Ruler::getInstance()->showNum(*PlayerData::getInstance()->getGold()));
				auto button = ServantButton::create();
				button->initServantLayer(0);
				auto widget = Widget::create();
				widget->setContentSize(button->getContentSize());
				widget->addChild(button);
				lv->pushBackCustomItem(widget);
			}
			else
			{
				ListView* lv = (ListView*)m_servantLayer->getChildByName("ListView");
				for (auto child : lv->getChildren())
				{
					child->scheduleUpdate();
				}
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
			initDownLayerAr(m_artifactLayer);
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
			initDownLayerSh(m_shopLayer);
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
			this->addChild(layer);
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
		unscheduleUpdate();
		armature->getAnimation()->play("Leave");
		clickLayer->setTouchEnabled(false);
		MyState::getInstance()->setBossButtonDown(false);
	}
	if (Ruler::getInstance()->Zero(PlayerData::getInstance()->getHpNow()))
	{
		unscheduleUpdate();
		PlayerData::getInstance()->defeatMonsterGold();
		if (PlayerData::getInstance()->getWaveNow() < 10 && PlayerData::getInstance()->getWaveNow() != 0)
		{
			PlayerData::getInstance()->waveUp();
			
			waveNum->setString(StringUtils::format("%d/10", PlayerData::getInstance()->getWaveNow()));
		}
		else if (PlayerData::getInstance()->getWaveNow() == 10)
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
			TextBMFont* text = (TextBMFont*)rootNode->getChildByName("UiNode")->getChildByName("Map")->getChildByName("MapNow")->getChildByName("level");
			text->setString(StringUtils::format("%d", 1 + PlayerData::getInstance()->getLevel()));
			Node* bossButtonNode = (Node*)rootNode->getChildByName("UiNode")->getChildByName("Wave_Button")->getChildByName("escapeBoss");
			bossButtonNode->removeChildByName("bt");
			waveNum->setString(StringUtils::format("%d/10", PlayerData::getInstance()->getWaveNow()));
			waveNum->runAction(Show::create());
		}
		clickLayer->setTouchEnabled(false);
		armature->getAnimation()->play("Leave");
		

	}
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

void HelloWorld::playerSkillCallBack()
{
	for (int i = 1; i < 7; i++)
	{
		m_skillButton[i-1] = (Button*)rootNode->getChildByName("UiNode")->getChildByName("SkillLayer")->getChildByName("SkillButton1");
	}
	for (int i = 1; i < 7; i++)
	{
		Button* bt = (Button*)m_skillButton[i - 1];
		bt->addTouchEventListener([this,bt](Ref* sender, Widget::TouchEventType type){
			if (type == Widget::TouchEventType::ENDED)
			{
				bt->addChild(SkillCD::create());
				
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
			SkillCD *cd = (SkillCD*)m_skill[i]->getChildByName("SkillCD");
			cd->setPercentNow(100/PlayerData::getInstance()->getBanTime(i)*dt);

		}
			
	}
}
void HelloWorld::skillKpCDUpdate(float dt)
{
	for (int i = 0; i < 6; i++)
	{
		if (m_skill[i]->getChildByName("SkillKpCD"))
		{
			SkillCD *cd = (SkillCD*)m_skill[i]->getChildByName("SkillKpCD");
			cd->setPercentNow(100 / PlayerData::getInstance()->getKeepTime(i));
			if (cd->getPercentNow() <= 0)
			{

			}

		}

	}
}

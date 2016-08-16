#include "HelloWorldScene.h"
#include "ui/CocosGUI.h"
#include "Tool/Rule.h"
#include "Tool/SqLite.h"
#include <cocostudio/CocoStudio.h>
#include "cocos-ext.h"
#include "MainScene/ClickLayer.h"
#include "SaveData/PlayerData.h"
#include "Tool/Rule.h"
#include "Ui/bossButton.h"
#include "MainScene/PlayerButton.h"
#include "SaveData/State.h"
#include "MainScene\ServantButton.h"
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
		num.number = 100;
		PlayerData::getInstance()->addGold(&num);
	}
	m_heroLayer = nullptr;
	m_servantLayer = nullptr;
    m_artifactLayer = nullptr;
	m_shopLayer = nullptr;
    rootNode = CSLoader::createNode("MainScene.csb");
	addChild(rootNode);
	Slider * hpSlider = (Slider*)rootNode->getChildByName("UiNode")->getChildByName("HpSlider");
	
	
	clickLayer = ClickLayer::create();
	clickLayer->setZOrder(-1);
	rootNode->addChild(clickLayer);
	uiInit();
	uiCallBack();
	createMonster();
	schedule(SEL_SCHEDULE(&HelloWorld::calUpdate), 0);

    return true;
}
void HelloWorld::calUpdate(float dt)
{
	TextBMFont* gold = (TextBMFont*)rootNode->getChildByName("goldNum");
	gold->setString(Ruler::getInstance()->showNum(PlayerData::getInstance()->getGold()));
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
	tbm->setString(Ruler::getInstance()->showNum(&PlayerData::getInstance()->getHpByID(PlayerData::getInstance()->getLevel())));
	PlayerData::getInstance()->setHpNow(PlayerData::getInstance()->getHpByID(PlayerData::getInstance()->getLevel()));
	monsterNode->addChild(armature);
}
void HelloWorld::update(float dt)
{
	auto heroDps = PlayerData::getInstance()->getHeroDps();
	auto dps = Ruler::getInstance()->multiplay(&heroDps, dt);

	Slider* slider = (Slider*)rootNode->getChildByName("UiNode")->getChildByName("HpSlider");
	auto subNow = Ruler::getInstance()->subNum(&PlayerData::getInstance()->getHpNow(), &dps);
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
	tbm->setString(Ruler::getInstance()->showNum(&PlayerData::getInstance()->getHpNow()));
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

	playerButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::BEGAN)
		{
			Button* bt = (Button*)sender;
			bt->setScale(1.2);
		}
		if (type == Widget::TouchEventType::ENDED) {
			// 注意node的生命周期的问题
			Button* bt = (Button*)sender;
			bt->setScale(1.0);
			if (initDownLayer(m_heroLayer))
			{
				TextBMFont* dps = (TextBMFont*)m_heroLayer->getChildByName("message")->getChildByName("Dps");
				dps->setString(Ruler::getInstance()->showNum(&PlayerData::getInstance()->getHeroDps()));
				TextBMFont* gold = (TextBMFont*)m_heroLayer->getChildByName("message")->getChildByName("gold");
				gold->setString(Ruler::getInstance()->showNum(PlayerData::getInstance()->getGold()));
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
	servantButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::BEGAN)
		{
			
			Button* bt = (Button*)sender;
			bt->setScale(1.2);
		}
		if (type == Widget::TouchEventType::ENDED) {
			// 注意node的生命周期的问题  
			Button* bt = (Button*)sender;
			bt->setScale(1.0);
			if (initDownLayer(m_servantLayer))
			{

				ListView* lv = (ListView*)m_servantLayer->getChildByName("ListView");
				ServantButton::getListView(lv);
				TextBMFont* dps = (TextBMFont*)m_servantLayer->getChildByName("message")->getChildByName("Dps");
				dps->setString(Ruler::getInstance()->showNum(&PlayerData::getInstance()->getDps()));
				TextBMFont* gold = (TextBMFont*)m_servantLayer->getChildByName("message")->getChildByName("gold");
				gold->setString(Ruler::getInstance()->showNum(PlayerData::getInstance()->getGold()));
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
	artifactButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::BEGAN)
		{
			Button* bt = (Button*)sender;
			bt->setScale(1.2);
		}
		if (type == Widget::TouchEventType::ENDED) {
			// 注意node的生命周期的问题  
			Button* bt = (Button*)sender;
			bt->setScale(1.0);
			initDownLayerAr(m_artifactLayer);
		}
	});
	itemButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::BEGAN)
		{
			Button* bt = (Button*)sender;
			bt->setScale(1.2);
		}
		if (type == Widget::TouchEventType::ENDED) {
			// 注意node的生命周期的问题  
			Button* bt = (Button*)sender;
			bt->setScale(1.0);
			initDownLayer(m_shopLayer);
		}
	});
}
void HelloWorld::killBoss()
{
	TextAtlas* waveNum = (TextAtlas*)rootNode->getChildByName("UiNode")->getChildByName("Wave_Button")->getChildByName("WaveNum");
	Sprite* escapeBoss = (Sprite*)rootNode->getChildByName("UiNode")->getChildByName("Wave_Button")->getChildByName("escapeBoss");
	if (State::getInstance()->getBossButtonDown())
	{
		unscheduleUpdate();
		armature->getAnimation()->play("Leave");
		clickLayer->setTouchEnabled(false);
		State::getInstance()->setBossButtonDown(false);
	}
	if (Ruler::getInstance()->Zero(&PlayerData::getInstance()->getHpNow()))
	{
		unscheduleUpdate();
		PlayerData::getInstance()->defeatMonsterGold();
		if (PlayerData::getInstance()->getWaveNow() < 10 && PlayerData::getInstance()->getWaveNow() != 0)
		{
			PlayerData::getInstance()->waveUp();
			
			waveNum->setString(StringUtils::format("%d//10", PlayerData::getInstance()->getWaveNow()));
		}
		else if (PlayerData::getInstance()->getWaveNow() == 10)
		{
			
			waveNum->runAction(Hide::create());
			escapeBoss->runAction(Show::create());
			PlayerData::getInstance()->waveUp();
			Node* bossButtonNode = (Node*)rootNode->getChildByName("UiNode")->getChildByName("Wave_Button")->getChildByName("escapeBoss");
			if (!bossButtonNode->getChildByName("bt"))
			{
				auto bossBt = bossButton::create();
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
			waveNum->setString(StringUtils::format("%d//10", PlayerData::getInstance()->getWaveNow()));
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
		escButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
			if (type == Widget::TouchEventType::ENDED) {
				// 注意node的生命周期的问题  
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
		escButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
			if (type == Widget::TouchEventType::ENDED) {
				// 注意node的生命周期的问题  
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
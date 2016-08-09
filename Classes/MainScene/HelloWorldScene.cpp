#include "HelloWorldScene.h"
#include "ui/CocosGUI.h"
#include "Tool/Rule.h"
#include "Tool/SqLite.h"
#include <cocostudio\CocoStudio.h>
#include "cocos-ext.h"
#include "MainScene/ClickLayer.h"
#include "SaveData\PlayerData.h"
#include "Tool\Rule.h"
using namespace cocostudio;
USING_NS_CC_EXT;
USING_NS_CC;

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
	
    rootNode = CSLoader::createNode("MainScene.csb");
	addChild(rootNode);
	Slider * hpSlider = (Slider*)rootNode->getChildByName("UiNode")->getChildByName("HpSlider");
	Button * levelUpButton = (Button*)rootNode->getChildByName("TestNode")->getChildByName("heroLevelUp");
	/*hpSlider->setEnabled(false);*/
	levelUpButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			// 注意node的生命周期的问题  
			
			PlayerData::getInstance()->heroLevelUp();
			TextBMFont* text = (TextBMFont*)rootNode->getChildByName("TestNode")->getChildByName("herolevel");
			text->setString(StringUtils::format("%d", PlayerData::getInstance()->getPlayerLevel()));
			TextBMFont* text1 = (TextBMFont*)rootNode->getChildByName("TestNode")->getChildByName("heroDps");
			text1->setString(Ruler::getInstance()->showNum(&PlayerData::getInstance()->getDps()));
		}
	});
	Button * levelUpButton100 = (Button*)rootNode->getChildByName("TestNode")->getChildByName("heroLevelUP100");
	levelUpButton100->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			// 注意node的生命周期的问题  
			for (int i = 0; i < 100; i++)
			{
				PlayerData::getInstance()->heroLevelUp();
			}
			TextBMFont* text = (TextBMFont*)rootNode->getChildByName("TestNode")->getChildByName("herolevel");
			text->setString(StringUtils::format("%d",1 + PlayerData::getInstance()->getPlayerLevel()));
			TextBMFont* text1 = (TextBMFont*)rootNode->getChildByName("TestNode")->getChildByName("heroDps");
			text1->setString(Ruler::getInstance()->showNum(&PlayerData::getInstance()->getDps()));
		}
	});
	levelUpButton->setZOrder(100000000);
	levelUpButton100->setZOrder(100000000);
	clickLayer = ClickLayer::create();
	clickLayer->setZOrder(-1);
	rootNode->addChild(clickLayer);
	
	createMonster();

	
	//amature->setArmatureData();//读取动画数组
    return true;
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
		
		if (Ruler::getInstance()->Zero(&PlayerData::getInstance()->getHpNow()))
		{
			unscheduleUpdate();
			PlayerData::getInstance()->levelUp();
			TextBMFont* text = (TextBMFont*)rootNode->getChildByName("TestNode")->getChildByName("level");
			text->setString(StringUtils::format("%d", 1+PlayerData::getInstance()->getLevel()));
			clickLayer->setTouchEnabled(false);
			armature->getAnimation()->play("Leave");


		}
		else
			;
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

	auto hpS = PlayerData::getInstance()->getHpByID(PlayerData::getInstance()->getLevel() % 5)->number;
	hpS *= 1000000;
	hpSlider->setMaxPercent(hpS);
	hpSlider->setPercent(hpS);

	TextBMFont* tbm = (TextBMFont*)rootNode->getChildByName("TestNode")->getChildByName("hpNow");
	tbm->setString(Ruler::getInstance()->showNum(PlayerData::getInstance()->getHpByID(PlayerData::getInstance()->getLevel() % 5)));
	PlayerData::getInstance()->setHpNow(*PlayerData::getInstance()->getHpByID(PlayerData::getInstance()->getLevel()%5));
	monsterNode->addChild(armature);
}
void HelloWorld::update(float dt)
{
	auto heroDps = PlayerData::getInstance()->getHeroDps();
	auto dps = Ruler::getInstance()->multiplay(&heroDps, dt);

	Slider* slider = (Slider*)rootNode->getChildByName("UiNode")->getChildByName("HpSlider");
	PlayerData::getInstance()->setHpNow(*Ruler::getInstance()->subNum(&PlayerData::getInstance()->getHpNow(), dps));
	if (PlayerData::getInstance()->getHpByID(PlayerData::getInstance()->getLevel())->Mathbit == PlayerData::getInstance()->getHpNow().Mathbit)
		slider->setPercent(PlayerData::getInstance()->getHpNow().number * 1000000);
	else if (PlayerData::getInstance()->getHpByID(PlayerData::getInstance()->getLevel())->Mathbit - PlayerData::getInstance()->getHpNow().Mathbit == 1)
		slider->setPercent(PlayerData::getInstance()->getHpNow().number * 1000);
	else if (PlayerData::getInstance()->getHpByID(PlayerData::getInstance()->getLevel())->Mathbit - PlayerData::getInstance()->getHpNow().Mathbit == 2)
		slider->setPercent(PlayerData::getInstance()->getHpNow().number);
	else if (PlayerData::getInstance()->getHpByID(PlayerData::getInstance()->getLevel())->Mathbit - PlayerData::getInstance()->getHpNow().Mathbit > 3)
		slider->setPercent(0);
	
	TextBMFont* tbm = (TextBMFont*)rootNode->getChildByName("TestNode")->getChildByName("hpNow");
	tbm->setString(Ruler::getInstance()->showNum(&PlayerData::getInstance()->getHpNow()));
	if (Ruler::getInstance()->Zero(&PlayerData::getInstance()->getHpNow()))
	{
		PlayerData::getInstance()->levelUp();
		TextBMFont* text = (TextBMFont*)rootNode->getChildByName("TestNode")->getChildByName("level");
		text->setString(StringUtils::format("%d", 1 + PlayerData::getInstance()->getLevel()));
		clickLayer->setTouchEnabled(false);
		armature->getAnimation()->play("Leave");
		unscheduleUpdate();


	}

}

void HelloWorld::uiCallBack()
{
	Button* playerButton = (Button*)rootNode->getChildByName("UiNode")->getChildByName("OptionLayer")->getChildByName("playerButton");
	Button* servantButton = (Button*)rootNode->getChildByName("UiNode")->getChildByName("OptionLayer")->getChildByName("servantButton");
	Button* artifactButton = (Button*)rootNode->getChildByName("UiNode")->getChildByName("OptionLayer")->getChildByName("artifactButton");
	Button* itemButton = (Button*)rootNode->getChildByName("UiNode")->getChildByName("OptionLayer")->getChildByName("itemButton");
	playerButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			// 注意node的生命周期的问题  
			
		}
	});
}
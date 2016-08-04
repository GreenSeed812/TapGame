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
	Slider * hpSlider = (Slider*)rootNode->getChildByName("HpSlider");
	Button * levelUpButton = (Button*)rootNode->getChildByName("heroLevelUp");
	levelUpButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			// 注意node的生命周期的问题  
			
			PlayerData::getInstance()->heroLevelUp();
			TextBMFont* text = (TextBMFont*)rootNode->getChildByName("herolevel");
			text->setString(StringUtils::format("%d", PlayerData::getInstance()->getPlayerLevel()));
			TextBMFont* text1 = (TextBMFont*)rootNode->getChildByName("heroDps");
			text1->setString(Ruler::getInstance()->showNum(&PlayerData::getInstance()->getDps()));
		}
	});
	levelUpButton->setZOrder(100000000);
	clickLayer = ClickLayer::create();
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
			PlayerData::getInstance()->levelUp();
			TextBMFont* text = (TextBMFont*)rootNode->getChildByName("level");
			text->setString(StringUtils::format("%d", PlayerData::getInstance()->getLevel()));
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
	auto armature = Armature::create(monster->name);
	armature->setName("MonsterArmature");
	armature->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(HelloWorld::callBackFunc));
	Node* monsterNode = (Node*)rootNode->getChildByName("MonsterNode");
	armature->getAnimation()->play("Start");
	Slider * hpSlider = (Slider*)rootNode->getChildByName("HpSlider");
	hpSlider->setMaxPercent(PlayerData::getInstance()->getHpByID(PlayerData::getInstance()->getLevel()%4)->number * 1000000);
	hpSlider->setPercent(PlayerData::getInstance()->getHpByID(PlayerData::getInstance()->getLevel()%4)->number * 1000000);

	TextBMFont* tbm = (TextBMFont*)rootNode->getChildByName("hpNow");
	tbm->setString(Ruler::getInstance()->showNum(PlayerData::getInstance()->getHpByID(PlayerData::getInstance()->getLevel() % 4)));
	PlayerData::getInstance()->setHpNow(*PlayerData::getInstance()->getHpByID(PlayerData::getInstance()->getLevel()%4));
	monsterNode->addChild(armature);
}
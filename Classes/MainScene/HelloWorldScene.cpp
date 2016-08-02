#include "HelloWorldScene.h"
#include "ui/CocosGUI.h"
#include "Tool/Rule.h"
#include "Tool/SqLite.h"
#include <cocostudio\CocoStudio.h>
#include "cocos-ext.h"
#include "MainScene/ClickLayer.h"
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
	Armature *amature =  (Armature*)rootNode->getChildByName("MonsterNode");
	amature->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(HelloWorld::callBackFunc));
	
	auto clickLayer = ClickLayer::create();
	rootNode->addChild(clickLayer);
	SqLite::getInstance()->readMonster();
    return true;
}
void HelloWorld::callBackFunc(Armature * armature, MovementEventType type, const std::string& action)
{
	if (action == "Hurt")
	{
		static int a = 100;
		Slider* hpSlider = (Slider*)rootNode->getChildByName("HpSlider");
		armature->getAnimation()->play("Wait");
	}
	return;
}
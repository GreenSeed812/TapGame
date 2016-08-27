#include "LoadingScene.h"
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

#include "MainScene/HelloWorldScene.h"
#include "Tool\SpecManager.h"
using namespace cocostudio;

USING_NS_CC;
USING_NS_CC_EXT;

using namespace ui;
Scene* LoadingScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = LoadingScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool LoadingScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//auto bg = Sprite::create("Loading.png");
	auto rootNode = CSLoader::createNode("MainScene.csb");
	//bg->setPosition(540,960);
	this->addChild(rootNode);

	scheduleOnce(CC_SCHEDULE_SELECTOR(LoadingScene::end), 1);

	return true;
}

void LoadingScene::end(float ref)
{
	
	auto bg = Sprite::create("mainBG.jpg");
	SqLite::getInstance();
	bg->setAnchorPoint(Vec2(0, 0));
	this->addChild(bg);

	auto  sqldb = SpecManager::shared()->loadFromDB();

	{
		auto l = Label::create(StringUtils::format("abcde %d %s", SpecManager::shared()->dramaSpecs->size(), sqldb.c_str()), "", 40);
		l->setPosition(200, 200);
		this->addChild(l);
	}


	SqLite::getInstance()->getHpByID(0);
	//PlayerData::getInstance();
	//HelloWorld::createScene();
	//Director::getInstance()->replaceScene(HelloWorld::createScene());
}
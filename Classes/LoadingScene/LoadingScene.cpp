#include <cocostudio/CocoStudio.h>
#include "AppDelegate.h"
#include "cocos-ext.h"
#include "LoadingScene.h"
#include "Animation.h"
#include "ui/CocosGUI.h"
#include "Tool/Rule.h"
#include "Tool/SqLite.h"
#include "Tool/Rule.h"
#include "Tool/SpecManager.h"
#include "SaveData/PlayerData.h"
#include "SaveData/State.h"
#include "Ui/bossButton.h"
#include "MainScene/ClickLayer.h"
#include "MainScene/PlayerButton.h"
#include "MainScene/ServantButton.h"
#include "MainScene/HelloWorldScene.h"
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
	m_rootNode = CSLoader::createNode("denglu.csb");

	auto head = (ImageView*)m_rootNode->getChildByName("head");
	auto nameBg = (ImageView*)m_rootNode->getChildByName("nameBg");
	auto name = (TextField*)nameBg->getChildByName("name");
	auto btn = (Button*)m_rootNode->getChildByName("btn");
	auto img = (ImageView*)btn->getChildByName("img");
	auto load = (TextBMFont*)m_rootNode->getChildByName("loadText");

	head->setVisible(false);
	nameBg->setVisible(false);
	name->setVisible(false);
	img->setVisible(false);
	btn->setVisible(false);
	load->setVisible(true);
	this->addChild(m_rootNode);
	scheduleOnce(CC_SCHEDULE_SELECTOR(LoadingScene::end),0);
	return true;
}

void LoadingScene::initLoading()
{
	
	auto head = (ImageView*)m_rootNode->getChildByName("head");
	auto nameBg = (ImageView*)m_rootNode->getChildByName("nameBg");
	auto name = (TextField*)nameBg->getChildByName("name");
	auto btn = (Button*)m_rootNode->getChildByName("btn");
	auto img = (ImageView*)btn->getChildByName("img");
	auto load = (TextBMFont*)m_rootNode->getChildByName("loadText");

	load->setVisible(true);
	auto scene = HelloWorld::createScene();
	scene->retain();
	if (PlayerData::getInstance()->getName() == "")
	{
		
		head->setVisible(true);
		nameBg->setVisible(true);
		name->setVisible(true);
		img->setVisible(true);
		btn->setVisible(true);
		load->setVisible(false);

		name->setMaxLengthEnabled(true);
		name->setMaxLength(10);
		name->addEventListener([this, name, scene](Ref* sender, TextField::EventType type)
		{
			switch (type)
			{
			case ui::TextField::EventType::ATTACH_WITH_IME:
			{
				
			}
				break;
			case ui::TextField::EventType::DELETE_BACKWARD:
			{

			}
				break;
			case ui::TextField::EventType::DETACH_WITH_IME:
			{

			}
				break;
			case ui::TextField::EventType::INSERT_TEXT:
			{

			}
				break;
			}
		});
		
		btn->addTouchEventListener([this, name, scene](Ref* sender, Widget::TouchEventType type){
			if (type == Widget::TouchEventType::ENDED)
			{
				PlayerData::getInstance()->setName(name->getStringValue());
				Director::getInstance()->replaceScene(scene);
			}
		});
	}
	else
	{
		Director::getInstance()->replaceScene(scene);
	}
}

void LoadingScene::end(float ref)
{
	MyAnimation::getInstance();
	PlayerData::getInstance();
	SqLite::getInstance();
	initLoading();
}
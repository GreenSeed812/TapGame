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
#include "Tool/TimeTool.h"
#include "SaveData/PlayerData.h"
#include "SaveData/State.h"
#include "SaveData/DataStatics.h"
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

	//remove(cocos2d::UserDefault::getInstance()->getXMLFilePath().c_str());
	m_rootNode = CSLoader::createNode("denglu.csb");

	auto bg = (ImageView*)m_rootNode->getChildByName("bg");
	auto head = (ImageView*)m_rootNode->getChildByName("head");
	auto nameBg = (ImageView*)m_rootNode->getChildByName("nameBg");
	auto btn = (Button*)m_rootNode->getChildByName("btn");
	auto img = (ImageView*)btn->getChildByName("img");
	auto load = (TextBMFont*)m_rootNode->getChildByName("loadText");
	auto huizhong = (Sprite*)m_rootNode->getChildByName("huizhong");

	m_bgLayer = LayerColor::create(Color4B(255,255,255,255));
	bg->setVisible(false);
	head->setVisible(false);
	nameBg->setVisible(false);
	img->setVisible(false);
	btn->setVisible(false);
	load->setVisible(false);
	this->addChild(m_bgLayer);
	this->addChild(m_rootNode);
	auto action = Sequence::create(DelayTime::create(2),FadeOut::create(1),CallFuncN::create(CC_CALLBACK_1(LoadingScene::callbackLogoH, this)), nullptr);
	huizhong->runAction(action);

	return true;
}

void LoadingScene::initLoading()
{	
	auto head = (ImageView*)m_rootNode->getChildByName("head");
	auto nameBg = (ImageView*)m_rootNode->getChildByName("nameBg");
	auto btn = (Button*)m_rootNode->getChildByName("btn");
	auto img = (ImageView*)btn->getChildByName("img");
	auto load = (TextBMFont*)m_rootNode->getChildByName("loadText");
	
	if (!cocos2d::UserDefault::getInstance()->getBoolForKey("isSaved") || UserDefault::getInstance()->getStringForKey("name").compare("") == 0)
	{
		head->setVisible(true);
		nameBg->setVisible(true);
		img->setVisible(true);
		btn->setVisible(true);
		load->setVisible(false);

		auto editBoxSize = Size(nameBg->getContentSize()*0.8);
		auto name = cocos2d::extension::EditBox::create(editBoxSize, cocos2d::extension::Scale9Sprite::create("Edit.png"));
		name->setPosition(Vec2(nameBg->getContentSize().width / 2, nameBg->getContentSize().height / 2 - 13));
		name->setReturnType(cocos2d::extension::EditBox::KeyboardReturnType::DONE);
		name->setFontName("Paint Boy");
		name->setFontSize(36);
		name->setFontColor(Color3B::WHITE);
		name->setMaxLength(6);
		name->setInputFlag(cocos2d::extension::EditBox::InputFlag::SENSITIVE);
		name->setInputMode(cocos2d::extension::EditBox::InputMode::SINGLE_LINE);
		name->setDelegate(this);
		
		nameBg->addChild(name);
		auto scene = HelloWorld::createScene();
		scene->retain();
		
		btn->addTouchEventListener([this, name, scene](Ref* sender, Widget::TouchEventType type){
			if (type == Widget::TouchEventType::ENDED)
			{
				std::string str = name->getText();
				if (str.compare("") !=0)
				{
					PlayerData::getInstance()->setName(name->getText());
					UserDefault::getInstance()->setStringForKey("name", name->getText());
					Director::getInstance()->replaceScene(scene);
					DataStatics::getInstance()->setGameDay(TimeTool::getInstance()->getTime());
				}
				else
				{
					auto text = (Text*)m_rootNode->getChildByName("no");
					text->setVisible(true);
					auto action = Sequence::create(DelayTime::create(2), CallFuncN::create(CC_CALLBACK_1(LoadingScene::callback, this)), nullptr);
					text->runAction(action);
				}
			}
		});
	}
	else
	{
		auto scene = HelloWorld::createScene();
		PlayerData::getInstance()->setName(UserDefault::getInstance()->getStringForKey("name"));
		scene->retain();
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

void LoadingScene::callback(Node *node)
{
	auto text = (Text*)m_rootNode->getChildByName("no");
	text->setVisible(false);
}

void LoadingScene::callbackLogoH(Node * node)
{
	auto action = Sequence::create(DelayTime::create(2), FadeOut::create(1), CallFuncN::create(CC_CALLBACK_1(LoadingScene::callbackLogoG, this)), nullptr);
	auto greenseed = (Sprite*)m_rootNode->getChildByName("greenseed");
	greenseed->setVisible(true);
	greenseed->runAction(action);
}


void LoadingScene::callbackLogoG(Node * node)
{
	auto load = (TextBMFont*)m_rootNode->getChildByName("loadText");
	auto bg = (ImageView*)m_rootNode->getChildByName("bg");
	bg->setVisible(true);
	load->setVisible(true);
	scheduleOnce(CC_SCHEDULE_SELECTOR(LoadingScene::end), 0);
}
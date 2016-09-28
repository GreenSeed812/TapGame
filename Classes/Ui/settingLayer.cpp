#include "settingLayer.h"
#include "ui/CocosGUI.h"
#include <cocostudio/CocoStudio.h> 
#include "MainScene/HelloWorldScene.h"
#include "Tool/SqLite.h"
#include "SaveData/PlayerData.h"
#include "Ui/Statistics.h"
using namespace cocostudio;
using namespace cocos2d;
using namespace ui;

Node * settingLayer::g_node = nullptr;

bool settingLayer::init()
{
	if (!Layer::init())
	{
		return false; 
	}
	m_bgLayer = LayerColor::create(Color4B(50, 50, 50, 155));
	this->addChild(m_bgLayer);
	rootNode = CSLoader::createNode("configLayer.csb");
	this->addChild(rootNode);
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(settingLayer::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
	Button* bt = (Button*)rootNode->getChildByName("esc");
	auto musicBtn = (Button*)rootNode->getChildByName("bg")->getChildByName("music");
	auto soundBtn = (Button*)rootNode->getChildByName("bg")->getChildByName("sound");
	auto dataStatistics = (Button*)rootNode->getChildByName("bg")->getChildByName("data");
	m_sou_off_on = PlayerData::getInstance()->getSou();
	m_mus_off_on = PlayerData::getInstance()->getBg();
	if (m_mus_off_on)
	{
		((Button*)rootNode->getChildByName("bg")->getChildByName("music"))->loadTextureNormal("yinxiao.png");
		((Button*)rootNode->getChildByName("bg")->getChildByName("music"))->loadTexturePressed("yinxiao0.png");
	}
	else
	{
		((Button*)rootNode->getChildByName("bg")->getChildByName("music"))->loadTextureNormal("yinxiao0.png");
		((Button*)rootNode->getChildByName("bg")->getChildByName("music"))->loadTexturePressed("yinxiao.png");
	}

	if (m_sou_off_on)
	{
		((Button*)rootNode->getChildByName("bg")->getChildByName("sound"))->loadTextureNormal("yinyue.png");
		((Button*)rootNode->getChildByName("bg")->getChildByName("sound"))->loadTexturePressed("yinyue0.png");
	}
	else
	{
		((Button*)rootNode->getChildByName("bg")->getChildByName("sound"))->loadTextureNormal("yinyue0.png");
		((Button*)rootNode->getChildByName("bg")->getChildByName("sound"))->loadTexturePressed("yinyue.png");
	}

	bt->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type){
		if (type == Widget::TouchEventType::ENDED)
		{
			m_bgLayer->removeFromParent();
			this->removeFromParent();
		}
	});
	musicBtn->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			if (m_mus_off_on)
			{
				m_mus_off_on = false;
				((Button*)rootNode->getChildByName("bg")->getChildByName("music"))->loadTextureNormal("yinxiao0.png");
				((Button*)rootNode->getChildByName("bg")->getChildByName("music"))->loadTexturePressed("yinxiao.png");
			}
			else
			{
				m_mus_off_on = true;
				((Button*)rootNode->getChildByName("bg")->getChildByName("music"))->loadTextureNormal("yinxiao.png");
				((Button*)rootNode->getChildByName("bg")->getChildByName("music"))->loadTexturePressed("yinxiao0.png");
			}
			BgMusic::getInstance()->playBg(m_mus_off_on);
			PlayerData::getInstance()->setBg(m_mus_off_on);
		}
	});
	soundBtn->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			if (m_sou_off_on)
			{
				m_sou_off_on = false;
				((Button*)rootNode->getChildByName("bg")->getChildByName("sound"))->loadTextureNormal("yinyue0.png");
				((Button*)rootNode->getChildByName("bg")->getChildByName("sound"))->loadTexturePressed("yinyue.png");
			}
			else
			{
				m_sou_off_on = true;
				((Button*)rootNode->getChildByName("bg")->getChildByName("sound"))->loadTextureNormal("yinyue.png");
				((Button*)rootNode->getChildByName("bg")->getChildByName("sound"))->loadTexturePressed("yinyue0.png");
			}
			BgMusic::getInstance()->setState(m_sou_off_on);
			PlayerData::getInstance()->setSou(m_sou_off_on);
		}
	});

	dataStatistics->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			auto statistics = Statistics::create();
			statistics->initStatistics();
			g_node->addChild(statistics);
		}
	});

	return true;
}
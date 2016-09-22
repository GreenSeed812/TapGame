#include "ClickLayer.h"
#include <cocostudio/CocoStudio.h>
#include "Ui\BgMusic.h"
#include "cocos-ext.h"
#include "Tool/SqLite.h"
#include "SaveData/PlayerData.h"
#include "ui/CocosGUI.h"
#include "SaveData/State.h"
#include "Animation.h"
#include <time.h>
USING_NS_CC_EXT;
USING_NS_CC;
using namespace cocostudio;
using namespace ui;
bool ClickLayer::init()
{
	m_clickPerSecond = 10;
	if (!Layer::init())
	{
		return false;
	}

	touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(ClickLayer::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(ClickLayer::onTouchEnded, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(ClickLayer::onTouchCanceled, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
	m_armature = Armature::create("Effect_atk_hunter");
	m_armature->retain();
	scheduleOnce(SEL_SCHEDULE(&ClickLayer::updateOnce), 0);
	

	return true;
}

void ClickLayer::updateOnce(float dt)
{
	this->getParent()->addChild(m_armature);
}
bool ClickLayer::onTouchBegan(Touch *touch, Event*)
{
	
	auto point = touch->getLocation();
	
	if (point.y >= 607)
	{

		m_armature->getAnimation()->playByIndex(0, -1, 0);
		m_armature->setPosition(point);
		
		MyState::getInstance()->setTaped(true);
		MyState::getInstance()->setKTap(true);
		BgMusic::getInstance()->playEff();
		return true;
	}
	else
		return false;

}

void ClickLayer::onTouchEnded(Touch *touch, Event*)
{
	MyState::getInstance()->setKTap(false);
}
void ClickLayer::onTouchCanceled(Touch *touch, Event*)
{
}

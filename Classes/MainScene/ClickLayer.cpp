#include "ClickLayer.h"
#include <cocostudio\CocoStudio.h>
#include "cocos-ext.h"
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
	touchListener->onTouchMoved = CC_CALLBACK_2(ClickLayer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(ClickLayer::onTouchEnded, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(ClickLayer::onTouchCanceled, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
	return true;
}

bool ClickLayer::onTouchBegan(Touch *touch, Event*)
{
	static long time = 0;

	struct timeval tv;
	gettimeofday(&tv, NULL);
	auto t_now = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	if (t_now - time > 1000 / m_clickPerSecond)
	{
		Armature* amature = (Armature*)this->getParent()->getChildByName("MonsterNode");
		amature->getAnimation()->play("Hurt",-1,0);
		time = t_now;
		return true;
	}
	return false;
}
void ClickLayer::onTouchMoved(Touch *touch, Event*)
{
	static long time = 0;
	struct timeval tv;
	gettimeofday(&tv, NULL);
	auto t_now = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	if (t_now - time > 1000 / m_clickPerSecond)
	{
		Armature* amature = (Armature*)this->getParent()->getChildByName("MonsterNode");
		amature->getAnimation()->play("Hurt", -1, 0);
		time = t_now;
	}

}
void ClickLayer::onTouchEnded(Touch *touch, Event*)
{

}
void ClickLayer::onTouchCanceled(Touch *touch, Event*)
{
}
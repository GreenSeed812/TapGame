#include "ClickLayer.h"
#include <cocostudio\CocoStudio.h>
#include "cocos-ext.h"
#include "Tool\SqLite.h"
#include "SaveData\PlayerData.h"
#include "ui/CocosGUI.h"
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
	touchListener->onTouchMoved = CC_CALLBACK_2(ClickLayer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(ClickLayer::onTouchEnded, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(ClickLayer::onTouchCanceled, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
	attackeffection();
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
		Node* monsterNode = (Node*)this->getParent()->getChildByName("MonsterNode");
		Armature* armature = (Armature*)monsterNode->getChildByName("MonsterArmature");
		normalAtk();
		armature->getAnimation()->play("Hurt",-1,0);
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
		Node* monsterNode = (Node*)this->getParent()->getChildByName("MonsterNode");
		Armature* armature = (Armature*)monsterNode->getChildByName("MonsterArmature");
		normalAtk();
		armature->getAnimation()->play("Hurt", -1, 0);
		time = t_now;
	}

}
void ClickLayer::onTouchEnded(Touch *touch, Event*)
{

}
void ClickLayer::onTouchCanceled(Touch *touch, Event*)
{
}
void ClickLayer::normalAtk()
{
	PlayerData::getInstance()->subHp();
	Slider* slider = (Slider*)this->getParent()->getChildByName("HpSlider");
	
	if (PlayerData::getInstance()->getHpByID(PlayerData::getInstance()->getLevel())->Mathbit == PlayerData::getInstance()->getHpNow().Mathbit)
		slider->setPercent(PlayerData::getInstance()->getHpNow().number * 1000000);
	else if (PlayerData::getInstance()->getHpByID(PlayerData::getInstance()->getLevel())->Mathbit - PlayerData::getInstance()->getHpNow().Mathbit == 1)
		slider->setPercent(PlayerData::getInstance()->getHpNow().number * 1000);
	else if (PlayerData::getInstance()->getHpByID(PlayerData::getInstance()->getLevel())->Mathbit - PlayerData::getInstance()->getHpNow().Mathbit == 2)
		slider->setPercent(PlayerData::getInstance()->getHpNow().number);
	else if (PlayerData::getInstance()->getHpByID(PlayerData::getInstance()->getLevel())->Mathbit - PlayerData::getInstance()->getHpNow().Mathbit > 2)
		slider->setPercent(0);

	TextBMFont* tbm = (TextBMFont*)this->getParent()->getChildByName("hpNow");
	tbm->setString(Ruler::getInstance()->showNum(&PlayerData::getInstance()->getHpNow()));

	auto effectSprite = Sprite::create();
	
	Node* effection = (Node*)this->getParent()->getChildByName("normalAtk");
	effection->addChild(effectSprite);
	auto animate = Animate::create(ani);
	auto r = random(0, 360);
	auto rotate = RotateBy::create(0.0416, Vec3(0, 0, r));
	auto spawn = Spawn::create(rotate, animate, NULL);
	effectSprite->runAction(spawn);

}
void ClickLayer::attackeffection()
{
	
	
	auto cache = SpriteFrameCache::getInstance();

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("effection/normalAttack.plist");
	ani = Animation::create();
	for (int i = 0; i < 9; i++)
	{
		ani->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("normalAttack_%d.png", i)));
	}
	ani->setDelayPerUnit(0.0416);
	
	
   
	
	ani->retain();
	
}
#include "ClickLayer.h"
#include <cocostudio\CocoStudio.h>
#include "cocos-ext.h"
#include "Tool\SqLite.h"
#include "SaveData\PlayerData.h"
#include "ui/CocosGUI.h"
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
	touchListener->setSwallowTouches(false);
	touchListener->onTouchBegan = CC_CALLBACK_2(ClickLayer::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(ClickLayer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(ClickLayer::onTouchEnded, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(ClickLayer::onTouchCanceled, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
	attackeffection();
	this->setContentSize(Size(1080,1960));
	
	return true;
}

void ClickLayer::effectInit()
{
	
}
bool ClickLayer::onTouchBegan(Touch *touch, Event*)
{
	static int t_time = 0;
	
	struct timeval tv;
	gettimeofday(&tv, nullptr);
	
	
	int t_now;
	tv.tv_sec = tv.tv_sec & 65535;
	t_now = tv.tv_sec * 1000 + tv.tv_usec / 1000;

	if (t_now - t_time > 1000 / m_clickPerSecond)
	{
		Node* monsterNode = (Node*)this->getParent()->getChildByName("MonsterNode");
		Armature* armature = (Armature*)monsterNode->getChildByName("MonsterArmature");
		normalAtk();
		armature->getAnimation()->play("Hurt",-1,0);
		t_time = t_now;
		return true;
	}
	return false;
}
void ClickLayer::onTouchMoved(Touch *touch, Event*)
{
	static long time = 0;
	struct timeval tv;
	gettimeofday(&tv, NULL);
	tv.tv_sec = tv.tv_sec & 65535;
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
	Slider* slider = (Slider*)this->getParent()->getChildByName("UiNode")->getChildByName("HpSlider");
	
	if (PlayerData::getInstance()->getHpByID(PlayerData::getInstance()->getLevel()).Mathbit == PlayerData::getInstance()->getHpNow().Mathbit)
		slider->setPercent(PlayerData::getInstance()->getHpNow().number * 1000000);
	else if (PlayerData::getInstance()->getHpByID(PlayerData::getInstance()->getLevel()).Mathbit - PlayerData::getInstance()->getHpNow().Mathbit == 1)
		slider->setPercent(PlayerData::getInstance()->getHpNow().number * 1000);
	else if (PlayerData::getInstance()->getHpByID(PlayerData::getInstance()->getLevel()).Mathbit - PlayerData::getInstance()->getHpNow().Mathbit == 2)
		slider->setPercent(PlayerData::getInstance()->getHpNow().number);
	else if (PlayerData::getInstance()->getHpByID(PlayerData::getInstance()->getLevel()).Mathbit - PlayerData::getInstance()->getHpNow().Mathbit > 2)
		slider->setPercent(0);

	TextBMFont* tbm = (TextBMFont*)this->getParent()->getChildByName("UiNode")->getChildByName("HpSlider")->getChildByName("hpNow");
	tbm->setString(Ruler::getInstance()->showNum(PlayerData::getInstance()->getHpNow()));

	
	effectSprite = Sprite::create();
	Node* effection = (Node*)this->getParent()->getChildByName("normalAtk");
	effection->addChild(effectSprite);
	
	auto animate = Animate::create(ani);
	auto r = random(0, 360);
	auto rotate = RotateBy::create(0.0416f, Vec3(0, 0, r));
	auto spawn = Spawn::create(rotate, animate, NULL);

	auto seq = Sequence::create(spawn, CallFuncN::create(CC_CALLBACK_1(ClickLayer::deleteSprite, this)), NULL);

	effectSprite->runAction(seq);
	
	TextBMFont* text = (TextBMFont*)CSLoader::createNode("DmgNum.csb")->getChildByName("Text");
	text->retain();
	text->removeFromParent();

	Node* monsterNode = (Node*)this->getParent()->getChildByName("MonsterNode");
	Armature* armature = (Armature*)monsterNode->getChildByName("MonsterArmature");
	text->setPosition(Vec2(0, armature->getContentSize().height * 10 / 7));
	effection->addChild(text);
	text->release();
	text->setString(Ruler::getInstance()->showNum(PlayerData::getInstance()->getDps()));
	

	auto textSeq = Sequence::create(MoveBy::create(1, Vec2(0, 300)), CallFuncN::create(CC_CALLBACK_1(ClickLayer::deleteSprite, this)), NULL);
	text->runAction(textSeq);
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
	ani->setDelayPerUnit(0.0416f);
	
	
	
	ani->retain();
	
}
void ClickLayer::deleteSprite(Node *node)
{
	node->removeFromParent();
}
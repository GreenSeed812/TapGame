#include"Animation.h"

MyAnimation * MyAnimation::m_animation = nullptr;

MyAnimation::MyAnimation()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("SpecialEffect/Harmer.plist");
	m_harmaer = Animation::create();
	for (size_t i = 0; i < 25; i++)
	{
		m_harmaer->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("harmer_%d.png", i)));
	}
	m_harmaer->retain();
}

MyAnimation* MyAnimation::getInstance()
{
	if (m_animation == nullptr)
	{
		m_animation = new MyAnimation();
	}
	return m_animation;
}

void MyAnimation::runHarmer(bool isRun,Node * node)
{
	auto animate = Animate::create(m_harmaer);
	auto sprite = Sprite::create();
	if (isRun)
	{
		sprite->runAction(RepeatForever::create(animate));
	}
	sprite->setPosition(node->getContentSize()/2);
	node->addChild(sprite);
}
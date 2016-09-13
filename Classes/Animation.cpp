#include"Animation.h"

MyAnimation * MyAnimation::m_animation = nullptr;

MyAnimation::MyAnimation()
{
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("SpecialEffect/gongjianzuo.plist");
	//m_harmaer = Animation::create();
	//for (size_t i = 0; i < 18; i++)
	//{
	//	m_harmaer->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("gongjianzuo%d.png", i).c_str()));
	//}
	//m_harmaer->setDelayPerUnit(0.0816f);
	//m_harmaer->retain();

	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("SpecialEffect/aoshu.plist");
	//m_aoshu = Animation::create();
	//for (size_t i = 0; i < 25; i++)
	//{
	//	m_aoshu->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("xiaofagong_%d.png", i).c_str()));
	//}
	//m_aoshu->setDelayPerUnit(0.1216f);
	//m_aoshu->retain();
}

MyAnimation* MyAnimation::getInstance()
{
	if (m_animation == nullptr)
	{
		m_animation = new MyAnimation();
		m_animation->initXiangyunani();
	}
	return m_animation;
}

//void MyAnimation::runHarmer(bool isRun,Node * node)
//{
//	auto animate = Animate::create(m_harmaer);
//	auto sprite = Sprite::create();
//	sprite->setScale(0.6);
//	sprite->setName("Harmer");
//	if (isRun)
//	{
//		sprite->runAction(RepeatForever::create(animate));
//	}
//	sprite->setPosition(Vec2(node->getContentSize().width - 700,node->getContentSize().height -500));
//	node->addChild(sprite);
//}
//
//void MyAnimation::runAoshu(bool isRun, Node * node)
//{
//	auto animate = Animate::create(m_aoshu);
//	auto sprite = Sprite::create();
//	sprite->setScale(2);
//	sprite->setName("aoshu");
//	if (isRun)
//	{
//		sprite->runAction(RepeatForever::create(animate));
//	}
//	sprite->setPosition(Vec2(node->getContentSize().width / 2, node->getContentSize().height - 500));
//	node->addChild(sprite);
//}

void MyAnimation::setPos()
{

}
void MyAnimation::initXiangyunani()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("SpecialEffect/xiangyun.plist");
	m_xiangyunani = Animation::create();
	for (int i = 0; i < 40; i++)
	{
		auto str = StringUtils::format("xiangyun%02d.png", i);
		m_xiangyunani->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("xiangyun%02d.png", i)));
	}
	m_xiangyunani->setDelayPerUnit(0.0416f);

	m_xiangyunani->retain();
}
Animate* MyAnimation::getAnimate()
{
	return Animate::create(m_xiangyunani);
}

Animation * MyAnimation::getxiangyunAni()
{
	return m_xiangyunani;
}
#include"bossButton.h"

bossButton::bossButton()
{
}

bossButton::~bossButton()
{
}

bool bossButton::init()
{
	if (!Layer::init())
	{
		return false;
	}
	m_sprite = Sprite::create("ui/bossButton.png");
	this->addChild(m_sprite);
	
	this->setContentSize(m_sprite->getContentSize());
	touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(bossButton::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(bossButton::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
	this->setAnchorPoint(Vec2(0.5, 0.5));
	i = 0;
	return true;
}

bool bossButton::onTouchBegan(Touch *touch, Event*)
{
	auto loc = this->convertTouchToNodeSpace(touch);

	if (m_sprite->getBoundingBox().containsPoint(loc))
		return true;
	else
		return false;
}
void bossButton::onTouchEnded(Touch *touch, Event*)
{
	
	if (i == 1)
	{
		m_sprite->setTexture("ui/bossButton.png");
		
	}
	else
	{
		m_sprite->setTexture("ui/bossButton2.png");
	}
	i = (i + 1) % 2;
}
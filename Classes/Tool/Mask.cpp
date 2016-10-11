#include "Mask.h"
int Mask::step = 100;
bool Mask::existing = false;
bool Mask::init()
{
	if (!Layer::init())
	{
		return false;
	}
	touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(Mask::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
	return true;
}
bool Mask::onTouchBegan(Touch *touch, Event *pEvent)
{
	auto point = touch->getLocation();
	switch (step)
	{
		case 0:
		{
			if (point.y >= 714)
			{
				touchListener->setSwallowTouches(false);
				//saveUserdefault();
				Mask::step++;
				Mask::existing = false;
				this->removeFromParent();
				
			}
			else
			{
				touchListener->setSwallowTouches(true);
			}
		}
		break; 
		case 1:
		case 5:
		{
			if (this->getParent()->getChildren().at(0)->getChildByName("UiNode")->getChildByName("OptionLayer")->getChildByName("playerButton")->getBoundingBox().containsPoint(point))
			{
				touchListener->setSwallowTouches(false);
				Mask::step++;
				Mask::existing = false;
				this->removeFromParent();
			}
			else
			{
				touchListener->setSwallowTouches(true);
			}
		}
		break;
		case 2:
		{	
			touchListener->setSwallowTouches(false);
			this->removeFromParent();
			Mask::existing = false;
			Mask::step++;
			//saveUserdefault();
		}
		break;
		case 3:
		{
			if (this->getParent()->getChildren().at(0)->getChildByName("UiNode")->getChildByName("OptionLayer")->getChildByName("servantButton")->getBoundingBox().containsPoint(point))
			{
				touchListener->setSwallowTouches(false);
				Mask::step++;
				Mask::existing = false;
				this->removeFromParent();
			}
			else
			{
				touchListener->setSwallowTouches(true);
			}
		}
		break;
		case 4:
		{
			touchListener->setSwallowTouches(false);
			this->removeFromParent();
			Mask::existing = false;
			Mask::step++;
			//saveUserdefault();
		}
		break;
		case 6:
		{
			touchListener->setSwallowTouches(false);
			this->removeFromParent();
			Mask::existing = false;
			Mask::step++;
			//saveUserdefault();
		}
	default:
		break;
	}
	return true;
}
void Mask::initAnimation()
{
	existing = true;
	switch (step)
	{
		case 0:
		{
			auto position = this->getParent()->getChildren().at(0)->getChildByName("normalAtk")->getPosition();
			auto spr = Sprite::create("finger.png");
			spr->setPosition(position);
			auto  move = MoveBy::create(0.3f,Vec2(0, 30));
			auto seq = Sequence::create(move,move->reverse(),NULL);
			auto rep = RepeatForever::create(seq);
			spr->runAction(rep);
			this->addChild(spr);
		}
		break;
		case 1:
		case 5:
		{
			auto position = this->getParent()->getChildren().at(0)->getChildByName("UiNode")->getChildByName("OptionLayer")->getChildByName("playerButton")->getPosition() - Point(0,30);
			auto spr = Sprite::create("finger.png");
			spr->setPosition(position);
			auto  move = MoveBy::create(0.3f, Vec2(0,-30));
			auto seq = Sequence::create(move, move->reverse(), NULL);
			auto rep = RepeatForever::create(seq);
			spr->runAction(rep);
			this->addChild(spr);
		}
		break;
		case 2:
		{
			
			//auto position = ;
			
			auto spr = Sprite::create("finger.png");
			spr->setPosition(Vec2(900,500));
			auto  move = MoveBy::create(0.3f, Vec2(0, -30));
			auto seq = Sequence::create(move, move->reverse(), NULL);
			auto rep = RepeatForever::create(seq);
			spr->runAction(rep);
			this->addChild(spr);
			
			
		}
		break;
		case 3:
		{
			auto position = this->getParent()->getChildren().at(0)->getChildByName("UiNode")->getChildByName("OptionLayer")->getChildByName("servantButton")->getPosition() - Point(0, 30);
			auto spr = Sprite::create("finger.png");
			spr->setPosition(position);
			auto  move = MoveBy::create(0.3f, Vec2(0, -30));
			auto seq = Sequence::create(move, move->reverse(), NULL);
			auto rep = RepeatForever::create(seq);
			spr->runAction(rep);
			this->addChild(spr);
		}
		break;
		case 4:
		{
			auto spr = Sprite::create("finger.png");
			spr->setPosition(Vec2(900, 500));
			auto  move = MoveBy::create(0.3f, Vec2(0, -30));
			auto seq = Sequence::create(move, move->reverse(), NULL);
			auto rep = RepeatForever::create(seq);
			spr->runAction(rep);
			this->addChild(spr);
		}
		break;
		case 6:
		{
			auto spr = Sprite::create("finger.png");
			spr->setPosition(Vec2(900, 400));
			auto  move = MoveBy::create(0.3f, Vec2(0, -30));
			auto seq = Sequence::create(move, move->reverse(), NULL);
			auto rep = RepeatForever::create(seq);
			spr->runAction(rep);
			this->addChild(spr);
		}
		default:
			break;
	}
}
//void Mask::saveUserdefault()
//{
//	UserDefault::getInstance()->setIntegerForKey("Guide",step);
//	UserDefault::getInstance()->flush();
//}
//void Mask::readUserdefault()
//{
//	step = UserDefault::getInstance()->getIntegerForKey("Guide");
//}
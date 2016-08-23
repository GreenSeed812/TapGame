#include "SkillCD.h"
#include "ui/CocosGUI.h"
#include <cocostudio/CocoStudio.h> 
using namespace cocostudio;
using namespace cocos2d;
using namespace ui;
bool SkillCD::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	
	
	m_percentNow = 100;
	
	return true;
}

void SkillCD::setPercentNow(float p)
{
	m_percentNow -= p;
	cd->setPercentage(m_percentNow);
	
}
void SkillCD::initImage(int i)
{
	
	cd = ProgressTimer::create(Sprite::create(StringUtils::format("skillCD/%d.png", i)));
	cd->setType(ProgressTimer::Type::RADIAL);
	cd->setPercentage(100);
	this->addChild(cd);
}
void SkillCD::initkpImage(int i)
{
	
	cd = ProgressTimer::create(Sprite::create(StringUtils::format("skillCD/n%d.png", i)));
	cd->setType(ProgressTimer::Type::RADIAL);
	cd->setPercentage(100);
	this->addChild(cd);
}
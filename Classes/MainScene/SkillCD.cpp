#include "SkillCD.h"
#include "ui/CocosGUI.h"
#include "SaveData/PlayerData.h"
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

void SkillCD::setPercentNow(float dt)
{
	m_kpTime -= dt;
	cd->setPercentage((m_kpTime / m_kpMaxTime )* 100);
	
}
void SkillCD::initImage(int i)
{
	
	cd = ProgressTimer::create(Sprite::create(StringUtils::format("skillCD/%d.png", i)));
	cd->setType(ProgressTimer::Type::RADIAL);
	cd->setPercentage(100);
	m_kpTime = PlayerData::getInstance()->getBanTime(i);
	m_kpMaxTime = m_kpTime;
	this->addChild(cd);
}
void SkillCD::initkpImage(int i)
{
	
	cd = ProgressTimer::create(Sprite::create(StringUtils::format("skillCD/n%d.png", i)));
	cd->setType(ProgressTimer::Type::RADIAL);
	cd->setPercentage(100);
	m_kpTime = PlayerData::getInstance()->getKeepTime(i);
	m_kpMaxTime = m_kpTime;
	this->addChild(cd);
}
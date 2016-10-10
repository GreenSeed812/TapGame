#include "SkillCD.h"
#include "ui/CocosGUI.h"
#include "SaveData/PlayerData.h"
#include <cocostudio/CocoStudio.h> 
#include "SaveData/ArtifactData.h"
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
	if (m_type == SKILLCD)
	{
		int time;
		std::string unit;
		if (m_kpTime > 3600)
		{
			time = m_kpTime / 3600;
			unit = "h";
		}
		else if (m_kpTime > 60)
		{
			time = m_kpTime / 60;
			unit = "m";
		}
		else
		{
			time = m_kpTime;
			unit = "s";
		}
		PlayerData::getInstance()->setSkillCD(m_id, m_kpTime);
		Label* Tm = (Label*)cd->getChildByName("time");
		auto string = StringUtils::format("%d%s", time, unit.c_str());
		Tm->setString(string);
	}	
}
void SkillCD::initImage(int i)
{
	cd = ProgressTimer::create(Sprite::create(StringUtils::format("skillCD/%d.png", i)));
	cd->setType(ProgressTimer::Type::RADIAL);
	cd->setReverseProgress(true);
	cd->setPercentage(100);
	m_kpTime = PlayerData::getInstance()->getBanTime(i);
	int time;
	std::string unit;
	if (m_kpTime > 3600)
	{
		time = m_kpTime / 3600;
		unit = "h";
	}
	else if (m_kpTime > 60)
	{
		time = m_kpTime / 60;
		unit = "m";
	}
	else
	{
		time = m_kpTime;
		unit = "s";
	}
	auto string = StringUtils::format("%d%s", time, unit.c_str());
	Label* cdTime = Label::create();
	cdTime->setPosition(cd->getContentSize() / 2);
	cdTime->setScale(2.0f);
	cdTime->setString(string);
	cdTime->setName("time");
	cd->addChild(cdTime);
	
	m_kpTime = m_kpTime * (1 - ArtifactData::getInstance()->getskillBanTimeS(i));
	m_kpMaxTime = m_kpTime;
	m_type = SKILLCD;
	m_id = i;
	this->addChild(cd);
	
}
void SkillCD::initImage(int i, float kpt)
{
	cd = ProgressTimer::create(Sprite::create(StringUtils::format("skillCD/%d.png", i)));
	cd->setReverseProgress(true);
	cd->setType(ProgressTimer::Type::RADIAL);
	int time;
	std::string unit;
	if (kpt > 3600)
	{
		time = kpt / 3600;
		unit = "h";
	}
	else if (kpt > 60)
	{
		time = kpt / 60;
		unit = "m";
	}
	else
	{
		time = kpt;
		unit = "s";
	}
	auto string = StringUtils::format("%d%s", time, unit.c_str());
	Label* cdTime = Label::create();
	cdTime->setPosition(cd->getContentSize() / 2);
	cdTime->setScale(2.0f);
	cdTime->setString(string);
	cdTime->setName("time");
	cd->addChild(cdTime);
	m_kpTime = kpt;
	m_kpTime = m_kpTime * (1 - ArtifactData::getInstance()->getskillBanTimeS(i));
	m_kpMaxTime = PlayerData::getInstance()->getBanTime(i)* (1 - ArtifactData::getInstance()->getskillBanTimeS(i));
	m_type = SKILLCD;
	m_id = i;
	cd->setPercentage((m_kpTime / m_kpMaxTime) * 100);
	this->addChild(cd);
	
}
void SkillCD::initkpImage(int i)
{
	
	cd = ProgressTimer::create(Sprite::create(StringUtils::format("skillCD/n%d.png", i)));
	cd->setReverseProgress(true);
	cd->setType(ProgressTimer::Type::RADIAL);
	cd->setPercentage(100);
	m_kpTime = PlayerData::getInstance()->getKeepTime(i);
	if (i == 1)
	{
		m_kpTime = m_kpTime * PlayerData::getInstance()->getSkillEFF(2);
	}
	m_kpTime = m_kpTime * (1 + ArtifactData::getInstance()->getskillTimeA(i));
	m_kpMaxTime = m_kpTime;
	m_type = SKILLKPCD;
	m_id = i;
	this->addChild(cd);
	
}
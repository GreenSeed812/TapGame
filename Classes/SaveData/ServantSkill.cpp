
#include "SaveData/ServantSkill.h"
#include "SaveData/PlayerData.h"
#include "Tool/Rule.h"
#include "Tool/SqLite.h"

bool ServantSkill::init()
{
	if (!Node::init())
	{
		return false;
	}

	m_state = LOCK;

	return true;
}

std::string ServantSkill::getText()
{
	auto strings = FileUtils::getInstance()->getValueMapFromFile("fonts/skillState.xml");
	if (m_state == LOCK)
	{
		m_text = strings["upLevel"].asString();
	}
	else
	{
		m_text = strings["unLock"].asString();
	}
	return m_text;
}

void ServantSkill::setState(int id)
{
	auto level = PlayerData::getInstance()->getPlayerLevel();
	for (auto lv : SqLite::getInstance()->m_servantUnlock)
	{
		if (level >= lv)
		{
			m_state == UNLOCK;
		}
		else
		{
			m_state == LOCK;
		}
	}
}

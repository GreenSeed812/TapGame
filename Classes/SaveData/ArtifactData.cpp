#include "ArtifactData.h"
#include "math.h"
#include "Tool/SqLite.h"
#include <cocos2d.h>
static ArtifactData* g_ar = nullptr;
ArtifactData* ArtifactData::getInstance()
{
	if (!g_ar)
	{
		g_ar = new ArtifactData();
	}
	return g_ar;
}
ArtifactData::ArtifactData()
 :m_artifactStone(100)
 ,m_artifactNum(0)
{
}

ArtifactData::~ArtifactData()
{
}
int ArtifactData::getNeededArStone()
{
	int a = pow(2.0f, m_artifactNum);
	return a;
}
int ArtifactData::addArNum()
{
	bool loop = true;
	int id;
	auto arthave = new ArtiHave();
	while (loop)
	{
		id = cocos2d::random(1, 29);
		loop = false;
		for (int i = 0; i < m_artifactNum; i++)
		{
			if (m_artifacts.at(i)->m_artifactID == id)
			{
				loop = true;
				break;
			}
			
		}
	}
	arthave->m_artifactID = id;
	arthave->m_artifactStar = 1;
	arthave->m_artifactLevel = 1;
	arthave->m_artimaxLevel = 1;

	m_artifactNum++;
	auto artSkill = SqLite::getInstance()->getArtifactSkillByID(id);
	arthave->m_artiDpsUp = artSkill.ar.AllDpsUp;
	m_artifacts.push_back(arthave);
	if (artSkill.ar.effid == 2)
	{
		m_dpsexper += artSkill.ar.effData;
	}
	if (artSkill.ar.effid == 6)
	{
		m_exploreProb += artSkill.ar.effData;
	}
	if (artSkill.ar.effid == 7)
	{
		m_explorePer += artSkill.ar.effData;
	}
	if (artSkill.ar.effid == 8)
	{
		m_AllDpsMul;
	}
	if (artSkill.ar.effid == 19)
	{
		rmGoldPer += artSkill.ar.effData;
	}
	if (artSkill.ar.effid == 20)
	{
		tenGoldPer += artSkill.ar.effData;
	}
	if (artSkill.ar.effid == 21)
	{
		bossGoldPer += artSkill.ar.effData;
	}
	if (artSkill.ar.effid == 22)
	{
		leaveGoldPer += artSkill.ar.effData;
	}
	if (artSkill.ar.effid == 29)
	{
		skillBanTimeS += artSkill.ar.effData;
	}
	if (artSkill.ar.effid == 30)
	{
		skilleffUp += artSkill.ar.effData;
	}
	if (artSkill.ar.effid == 31)
	{
		skillTimeA += artSkill.ar.effData;
	}
	if (artSkill.ar.effid == 32)
	{
		bossHpS += artSkill.ar.effData;
	}
	if (artSkill.ar.effid == 33)
	{
		heroLevelUpDown += artSkill.ar.effData;
	}
	if (artSkill.ar.effid == 34)
	{
		bossTimeUp += artSkill.ar.effData;
	}
	if (artSkill.ar.effid == 35)
	{
		artiUpPer += artSkill.ar.effData;
	}
	if (artSkill.ar.effid == 36)
	{
		servantLevelUpDown += artSkill.ar.effData;
	}
	if (artSkill.ar.effid == 37)
	{
		WaveDown += artSkill.ar.effData;
	}
	if (artSkill.ar.effid == 38)
	{
		servantUnlockDown += artSkill.ar.effData;
	}
	return id;

}


void ArtifactData::arLevelUp(int id)
{
	for (int i = 0; i < m_artifactNum; i++)
	{
		if (m_artifacts.at(i)->m_artifactID == id)
		{
			m_artifacts.at(i)->m_artifactLevel++;
			break;
		}
			
	}
}
void ArtifactData::arStarUp(int id)
{
	for (size_t i = 0; i < m_artifactNum; i++)
	{
		if (m_artifacts.at(i)->m_artifactID == id)
		{
			m_artifacts.at(i)->m_artifactStar++;
			break;
		}
	}
}
int ArtifactData::getLevel(int id)
{
	for (size_t i = 0; i < m_artifactNum; i++)
	{
		
		if (m_artifacts.at(i)->m_artifactID == id)
		{
			return m_artifacts.at(i)->m_artifactLevel;
		
		}
	}
	return -1;
}
int ArtifactData::getMaxLevel(int id)
{
	for (size_t i = 0; i < m_artifactNum; i++)
	{

		if (m_artifacts.at(i)->m_artifactID == id)
		{
			return m_artifacts.at(i)->m_artimaxLevel;

		}
	}
	return -1;
}
void ArtifactData::deleteArByID(int id)
{

	for (std::vector<ArtiHave*>::iterator it = m_artifacts.begin(); it != m_artifacts.end();)
	{
		
		if ((*it)->m_artifactID == id)
		{
			m_artifacts.erase(it);
			m_artifactNum--;
		}
	}
}

int ArtifactData::getStarNum(int id)
{
	for (std::vector<ArtiHave*>::iterator it = m_artifacts.begin(); it != m_artifacts.end();)
	{

		if ((*it)->m_artifactID == id)
		{
			return (*it)->m_artifactStar;
		}
	}
}
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
 :m_artifactStone(0)
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
	while (loop)
	{
		id = cocos2d::random(1, 29);
		loop = false;
		for (int i = 0; i < m_artifactNum; i++)
		{
			if (m_artifacts[i].m_artifactID == id)
			{
				loop = true;
				break;
			}
			
		}
	}
		
	m_artifacts[m_artifactNum].m_artifactID = id;
	m_artifacts[m_artifactNum].m_artifactStar = 1;
	m_artifacts[m_artifactNum].m_artifactLevel = 1;
	m_artifacts[m_artifactNum].m_artimaxLevel = 1;
	m_artifactNum++;
	auto artSkill = SqLite::getInstance()->getArtifactSkillByID(id);
	m_artifacts[m_artifactNum].m_artiDpsUp = artSkill.ar.AllDpsUp;

	return id;

}
void ArtifactData::arLevelUp(int id)
{
	for (int i = 0; i < m_artifactNum; i++)
	{
		if (m_artifacts[i].m_artifactID == id)
		{
			m_artifacts[i].m_artifactLevel++;
			break;
		}
			
	}
}
void ArtifactData::arStarUp(int id)
{
	for (size_t i = 0; i < m_artifactNum; i++)
	{
		if (m_artifacts[i].m_artifactID == id)
		{
			m_artifacts[i].m_artifactStar++;
			break;
		}
	}
}
int ArtifactData::getLevel(int id)
{
	for (size_t i = 0; i < m_artifactNum; i++)
	{
		if (m_artifacts[i].m_artifactID == id)
		{
			return m_artifacts[i].m_artifactLevel;
		
		}
	}
	return -1;
}
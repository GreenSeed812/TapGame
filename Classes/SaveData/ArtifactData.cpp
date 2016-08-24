#include "ArtifactData.h"
#include "math.h"
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
void ArtifactData::addArNum(int id)
{
	m_artifactID[m_artifactNum] = id;
	m_artifactStart[m_artifactNum] = 1;
	m_artifactLevel[m_artifactNum] = 1;
}
void ArtifactData::arLevelUp(int id)
{
	for (int i = 0; i < m_artifactNum; i++)
	{
		if (m_artifactID[i] == id)
		{
			m_artifactLevel[i++];
			break;
		}
			
	}
}
void ArtifactData::arStarUp(int id)
{
	for (size_t i = 0; i < m_artifactNum; i++)
	{
		if (m_artifactID[i] == id)
		{
			m_artifactStart[i]++;
			break;
		}
	}
}
int ArtifactData::getLevel(int id)
{
	for (size_t i = 0; i < m_artifactNum; i++)
	{
		if (m_artifactID[i] == id)
		{
			return m_artifactLevel[i];
		
		}
	}
	return -1;
}
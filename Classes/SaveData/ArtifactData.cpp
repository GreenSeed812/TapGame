#include "ArtifactData.h"
#include "math.h"
static Artifact* g_ar = nullptr;
Artifact* Artifact::getInstance()
{
	if (!g_ar)
	{
		g_ar = new Artifact();
	}
	return g_ar;
}
Artifact::Artifact()
 :m_artifactStone(0)
 ,m_artifactNum(0)
{
}

Artifact::~Artifact()
{
}
int Artifact::getNeededArStone()
{
	int a = pow(2.0f, m_artifactNum);
	return a;
}
void Artifact::addArNum(int id)
{

}
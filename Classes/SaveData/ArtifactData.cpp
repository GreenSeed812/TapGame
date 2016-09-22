#include "ArtifactData.h"
#include "math.h"
#include "Tool/SqLite.h"
#include "PlayerData.h"
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
 :m_artifactStone(10000)
 ,m_artifactNum(0)
 , m_dpsexper(0)
 ,m_AllDpsMul(0)
 ,m_exploreProb(0)
 ,m_explorePer(0)
 ,rmGoldPer(0)
 ,tenGoldPer(0)
 ,bossGoldPer(0)
 ,leaveGoldPer(0)
 ,bossHpS(0)
 ,heroLevelUpDown(0)
 ,bossTimeUp(0)
 ,artiUpPer(0)
 ,servantLevelUpDown(0)
 ,WaveDown(0) 
 ,servantUnlockDown(0)
 , m_fiveStar(0)
{
	for (int i = 0; i < 6; i++)
	{
		skillBanTimeS[i] = 0;
		skilleffUp[i] = 0;
		skillTimeA[i] = 0;
	}
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
		for (int i = 8; i < m_artifactNum; i++)
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
	AchieveData::getInstance()->ArMaxNum(m_artifactNum);
	auto artSkill = SqLite::getInstance()->getArtifactSkillByID(id);
	arthave->m_artiDpsUp = artSkill.ar.AllDpsUp;
	m_AllDpsMul += artSkill.ar.initAllDps;
	m_artifacts.push_back(arthave);
	if (artSkill.skillID != 0)
	{
		if (artSkill.ar.effid == 29)
		{
			skillBanTimeS[artSkill.skillID] += artSkill.ar.effData;
		}
		if (artSkill.ar.effid == 30)
		{
			skilleffUp[artSkill.skillID] += artSkill.ar.effData;
		}
		if (artSkill.ar.effid == 31)
		{
			skillTimeA[artSkill.skillID] += artSkill.ar.effData;
		}
	}
	else
	{
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
			m_AllDpsMul += artSkill.ar.effData;
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
	}
	PlayerData::getInstance()->saveUserData();	
	cocos2d::CCNotificationCenter::getInstance()->postNotification("ArChange");
	return id;

}


void ArtifactData::arLevelUp(int id)
{
	for (int i = 0; i < m_artifactNum; i++)
	{
		if (m_artifacts.at(i)->m_artifactID == id)
		{
			m_AllDpsMul += m_artifacts.at(i)->m_artiDpsUp;
			m_artifacts.at(i)->m_artifactLevel++;
			break;
		}
			
	}
}
void ArtifactData::arStarUp()
{
	auto id = cocos2d::random(0, m_artifactNum - m_fiveStar);

	for (std::vector<ArtiHave*>::iterator it = m_artifacts.begin();it!= m_artifacts.end() ;it++)
	{
		if ((*it)->m_artifactID == id)
		{
			(*it)->m_artifactStar++;
			if ((*it)->m_artifactStar == 5)
			{
				remove(m_artifacts.begin(),m_artifacts.end(),*it);
				m_fiveStar++;
			}
			break;
		}
	}
	
}
int ArtifactData::getLevel(int id)
{
	for (int i = 0; i < m_artifactNum; i++)
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
	for (int i = 0; i < m_artifactNum; i++)
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
	
	for (int i = 0; i < m_artifactNum; i++)
	{
		if (m_artifacts.at(i)->m_artifactID == id)
		{
			m_artifactStone += (m_artifacts.at(i)->m_artimaxLevel - 1) * 2;

		}
	}
	m_artifactStone += pow(2, m_artifactNum - 1);
	for (std::vector<ArtiHave*>::iterator it = m_artifacts.begin(); it != m_artifacts.end(); it++)
	{
		auto artSkill = SqLite::getInstance()->getArtifactSkillByID(id);
		if ((*it)->m_artifactID == id)
		{
			if (artSkill.ar.effid == 2)
			{
				m_dpsexper -= artSkill.ar.effData;
			}
			if (artSkill.ar.effid == 6)
			{
				m_exploreProb -= artSkill.ar.effData;
			}
			if (artSkill.ar.effid == 7)
			{
				m_explorePer -= artSkill.ar.effData;
			}
			if (artSkill.ar.effid == 8)
			{
				m_AllDpsMul -= artSkill.ar.effData;
			}
			if (artSkill.ar.effid == 19)
			{
				rmGoldPer -= artSkill.ar.effData;
			}
			if (artSkill.ar.effid == 20)
			{
				tenGoldPer -= artSkill.ar.effData;
			}
			if (artSkill.ar.effid == 21)
			{
				bossGoldPer -= artSkill.ar.effData;
			}
			if (artSkill.ar.effid == 22)
			{
				leaveGoldPer -= artSkill.ar.effData;
			}
			if (artSkill.ar.effid == 32)
			{
				bossHpS -= artSkill.ar.effData;
			}
			if (artSkill.ar.effid == 33)
			{
				heroLevelUpDown -= artSkill.ar.effData;
			}
			if (artSkill.ar.effid == 34)
			{
				bossTimeUp -= artSkill.ar.effData;
			}
			if (artSkill.ar.effid == 35)
			{
				artiUpPer -= artSkill.ar.effData;
			}
			if (artSkill.ar.effid == 36)
			{
				servantLevelUpDown -= artSkill.ar.effData;
			}
			if (artSkill.ar.effid == 37)
			{
				WaveDown -= artSkill.ar.effData;
			}
			if (artSkill.ar.effid == 38)
			{
				servantUnlockDown -= artSkill.ar.effData;
			}
			m_AllDpsMul -= ((*it)->m_artifactLevel-1) * (*it)->m_artiDpsUp + SqLite::getInstance()->getArtifactSkillByID(id).ar.initAllDps;
			m_artifacts.erase(it);
			m_artifactNum--;
			break;
		}
	}
	PlayerData::getInstance()->saveUserData();
}

int ArtifactData::getStarNum(int id)
{
	for (std::vector<ArtiHave*>::iterator it = m_artifacts.begin(); it != m_artifacts.end();)
	{
		if ((*it)->m_artifactID == id)
		{
			return (*it)->m_artifactStar;

		}
		it++;
	}
}

void ArtifactData::arReset(int id)
{
} 
void ArtifactData::saveUserDefault(Document& document)
{
	Document::AllocatorType& allocator = document.GetAllocator();
	document.AddMember("m_artifactStone", m_artifactStone, allocator);
	document.AddMember("m_artifactNum", m_artifactNum, allocator); 
	document.AddMember("m_dpsexper", m_dpsexper, allocator);
	document.AddMember("m_AllDpsMul", m_AllDpsMul, allocator);
	document.AddMember("m_exploreProb", m_exploreProb, allocator);
	document.AddMember("m_explorePer", m_explorePer, allocator);
	document.AddMember("rmGoldPer", rmGoldPer, allocator);
	document.AddMember("tenGoldPer", tenGoldPer, allocator);
	document.AddMember("bossGoldPer", bossGoldPer, allocator);
	document.AddMember("bossHpS", bossHpS, allocator);
	document.AddMember("leaveGoldPer", leaveGoldPer, allocator);
	document.AddMember("heroLevelUpDown", heroLevelUpDown, allocator);
	document.AddMember("bossTimeUp", bossTimeUp, allocator);
	document.AddMember("servantLevelUpDown", servantLevelUpDown, allocator);
	document.AddMember("WaveDown", WaveDown, allocator);
	document.AddMember("servantUnlockDown", servantUnlockDown, allocator);
	
	if (m_artifacts.size() > 0)
	{
		document.AddMember("m_artifacts.at(0)->m_artiDpsUp", m_artifacts.at(0)->m_artiDpsUp, allocator);
		document.AddMember("m_artifacts.at(0)->m_artifactID", m_artifacts.at(0)->m_artifactID, allocator);
		document.AddMember("m_artifacts.at(0)->m_artifactLevel", m_artifacts.at(0)->m_artifactLevel, allocator);
		document.AddMember("m_artifacts.at(0)->m_artimaxLevel", m_artifacts.at(0)->m_artimaxLevel, allocator);
		document.AddMember("m_artifacts.at(0)->m_artiDpsUp", m_artifacts.at(0)->m_artiDpsUp, allocator);

	}
	if (m_artifacts.size() > 1)
	{
		document.AddMember("m_artifacts.at(1)->m_artiDpsUp", m_artifacts.at(1)->m_artiDpsUp, allocator);
		document.AddMember("m_artifacts.at(1)->m_artifactID", m_artifacts.at(1)->m_artifactID, allocator);
		document.AddMember("m_artifacts.at(1)->m_artifactLevel", m_artifacts.at(1)->m_artifactLevel, allocator);
		document.AddMember("m_artifacts.at(1)->m_artimaxLevel", m_artifacts.at(1)->m_artimaxLevel, allocator);
		document.AddMember("m_artifacts.at(1)->m_artiDpsUp", m_artifacts.at(1)->m_artiDpsUp, allocator);

	}
	if (m_artifacts.size() > 2)
	{
		document.AddMember("m_artifacts.at(2)->m_artiDpsUp", m_artifacts.at(2)->m_artiDpsUp, allocator);
		document.AddMember("m_artifacts.at(2)->m_artifactID", m_artifacts.at(2)->m_artifactID, allocator);
		document.AddMember("m_artifacts.at(2)->m_artifactLevel", m_artifacts.at(2)->m_artifactLevel, allocator);
		document.AddMember("m_artifacts.at(2)->m_artimaxLevel", m_artifacts.at(2)->m_artimaxLevel, allocator);
		document.AddMember("m_artifacts.at(2)->m_artiDpsUp", m_artifacts.at(2)->m_artiDpsUp, allocator);

	}
	if (m_artifacts.size() > 3)
	{
		document.AddMember("m_artifacts.at(3)->m_artiDpsUp", m_artifacts.at(3)->m_artiDpsUp, allocator);
		document.AddMember("m_artifacts.at(3)->m_artifactID", m_artifacts.at(3)->m_artifactID, allocator);
		document.AddMember("m_artifacts.at(3)->m_artifactLevel", m_artifacts.at(3)->m_artifactLevel, allocator);
		document.AddMember("m_artifacts.at(3)->m_artimaxLevel", m_artifacts.at(3)->m_artimaxLevel, allocator);
		document.AddMember("m_artifacts.at(3)->m_artiDpsUp", m_artifacts.at(3)->m_artiDpsUp, allocator);

	}
	if (m_artifacts.size() > 4)
	{
		document.AddMember("m_artifacts.at(4)->m_artiDpsUp", m_artifacts.at(4)->m_artiDpsUp, allocator);
		document.AddMember("m_artifacts.at(4)->m_artifactID", m_artifacts.at(4)->m_artifactID, allocator);
		document.AddMember("m_artifacts.at(4)->m_artifactLevel", m_artifacts.at(4)->m_artifactLevel, allocator);
		document.AddMember("m_artifacts.at(4)->m_artimaxLevel", m_artifacts.at(4)->m_artimaxLevel, allocator);
		document.AddMember("m_artifacts.at(4)->m_artiDpsUp", m_artifacts.at(4)->m_artiDpsUp, allocator);

	}
	if (m_artifacts.size() > 5)
	{
		document.AddMember("m_artifacts.at(5)->m_artiDpsUp", m_artifacts.at(5)->m_artiDpsUp, allocator);
		document.AddMember("m_artifacts.at(5)->m_artifactID", m_artifacts.at(5)->m_artifactID, allocator);
		document.AddMember("m_artifacts.at(5)->m_artifactLevel", m_artifacts.at(5)->m_artifactLevel, allocator);
		document.AddMember("m_artifacts.at(5)->m_artimaxLevel", m_artifacts.at(5)->m_artimaxLevel, allocator);
		document.AddMember("m_artifacts.at(5)->m_artiDpsUp", m_artifacts.at(5)->m_artiDpsUp, allocator);

	}
	if (m_artifacts.size() > 6)
	{
		document.AddMember("m_artifacts.at(6)->m_artiDpsUp", m_artifacts.at(6)->m_artiDpsUp, allocator);
		document.AddMember("m_artifacts.at(6)->m_artifactID", m_artifacts.at(6)->m_artifactID, allocator);
		document.AddMember("m_artifacts.at(6)->m_artifactLevel", m_artifacts.at(6)->m_artifactLevel, allocator);
		document.AddMember("m_artifacts.at(6)->m_artimaxLevel", m_artifacts.at(6)->m_artimaxLevel, allocator);
		document.AddMember("m_artifacts.at(6)->m_artiDpsUp", m_artifacts.at(6)->m_artiDpsUp, allocator);

	}
	if (m_artifacts.size() > 7)
	{
		document.AddMember("m_artifacts.at(7)->m_artiDpsUp", m_artifacts.at(7)->m_artiDpsUp, allocator);
		document.AddMember("m_artifacts.at(7)->m_artifactID", m_artifacts.at(7)->m_artifactID, allocator);
		document.AddMember("m_artifacts.at(7)->m_artifactLevel", m_artifacts.at(7)->m_artifactLevel, allocator);
		document.AddMember("m_artifacts.at(7)->m_artimaxLevel", m_artifacts.at(7)->m_artimaxLevel, allocator);
		document.AddMember("m_artifacts.at(7)->m_artiDpsUp", m_artifacts.at(7)->m_artiDpsUp, allocator);
	}
	if (m_artifacts.size() > 8)
	{
		document.AddMember("m_artifacts.at(8)->m_artiDpsUp", m_artifacts.at(8)->m_artiDpsUp, allocator);
		document.AddMember("m_artifacts.at(8)->m_artifactID", m_artifacts.at(8)->m_artifactID, allocator);
		document.AddMember("m_artifacts.at(8)->m_artifactLevel", m_artifacts.at(8)->m_artifactLevel, allocator);
		document.AddMember("m_artifacts.at(8)->m_artimaxLevel", m_artifacts.at(8)->m_artimaxLevel, allocator);
		document.AddMember("m_artifacts.at(8)->m_artiDpsUp", m_artifacts.at(8)->m_artiDpsUp, allocator);

	}
	if (m_artifacts.size() > 9)
	{
		document.AddMember("m_artifacts.at(9)->m_artiDpsUp", m_artifacts.at(9)->m_artiDpsUp, allocator);
		document.AddMember("m_artifacts.at(9)->m_artifactID", m_artifacts.at(9)->m_artifactID, allocator);
		document.AddMember("m_artifacts.at(9)->m_artifactLevel", m_artifacts.at(9)->m_artifactLevel, allocator);
		document.AddMember("m_artifacts.at(9)->m_artimaxLevel", m_artifacts.at(9)->m_artimaxLevel, allocator);
		document.AddMember("m_artifacts.at(9)->m_artiDpsUp", m_artifacts.at(9)->m_artiDpsUp, allocator);

	}
	if (m_artifacts.size() > 10)
	{
		document.AddMember("m_artifacts.at(10)->m_artiDpsUp", m_artifacts.at(10)->m_artiDpsUp, allocator);
		document.AddMember("m_artifacts.at(10)->m_artifactID", m_artifacts.at(10)->m_artifactID, allocator);
		document.AddMember("m_artifacts.at(10)->m_artifactLevel", m_artifacts.at(10)->m_artifactLevel, allocator);
		document.AddMember("m_artifacts.at(10)->m_artimaxLevel", m_artifacts.at(10)->m_artimaxLevel, allocator);
		document.AddMember("m_artifacts.at(10)->m_artiDpsUp", m_artifacts.at(10)->m_artiDpsUp, allocator);

	}
	if (m_artifacts.size() > 11)
	{
		document.AddMember("m_artifacts.at(11)->m_artiDpsUp", m_artifacts.at(11)->m_artiDpsUp, allocator);
		document.AddMember("m_artifacts.at(11)->m_artifactID", m_artifacts.at(11)->m_artifactID, allocator);
		document.AddMember("m_artifacts.at(11)->m_artifactLevel", m_artifacts.at(11)->m_artifactLevel, allocator);
		document.AddMember("m_artifacts.at(11)->m_artimaxLevel", m_artifacts.at(11)->m_artimaxLevel, allocator);
		document.AddMember("m_artifacts.at(11)->m_artiDpsUp", m_artifacts.at(11)->m_artiDpsUp, allocator);

	}
	if (m_artifacts.size() > 12)
	{
		document.AddMember("m_artifacts.at(12)->m_artiDpsUp", m_artifacts.at(12)->m_artiDpsUp, allocator);
		document.AddMember("m_artifacts.at(12)->m_artifactID", m_artifacts.at(12)->m_artifactID, allocator);
		document.AddMember("m_artifacts.at(12)->m_artifactLevel", m_artifacts.at(12)->m_artifactLevel, allocator);
		document.AddMember("m_artifacts.at(12)->m_artimaxLevel", m_artifacts.at(12)->m_artimaxLevel, allocator);
		document.AddMember("m_artifacts.at(12)->m_artiDpsUp", m_artifacts.at(12)->m_artiDpsUp, allocator);

	}
	if (m_artifacts.size() > 13)
	{
		document.AddMember("m_artifacts.at(13)->m_artiDpsUp", m_artifacts.at(13)->m_artiDpsUp, allocator);
		document.AddMember("m_artifacts.at(13)->m_artifactID", m_artifacts.at(13)->m_artifactID, allocator);
		document.AddMember("m_artifacts.at(13)->m_artifactLevel", m_artifacts.at(13)->m_artifactLevel, allocator);
		document.AddMember("m_artifacts.at(13)->m_artimaxLevel", m_artifacts.at(13)->m_artimaxLevel, allocator);
		document.AddMember("m_artifacts.at(13)->m_artiDpsUp", m_artifacts.at(13)->m_artiDpsUp, allocator);

	}
	if (m_artifacts.size() > 14)
	{
		document.AddMember("m_artifacts.at(14)->m_artiDpsUp", m_artifacts.at(14)->m_artiDpsUp, allocator);
		document.AddMember("m_artifacts.at(14)->m_artifactID", m_artifacts.at(14)->m_artifactID, allocator);
		document.AddMember("m_artifacts.at(14)->m_artifactLevel", m_artifacts.at(14)->m_artifactLevel, allocator);
		document.AddMember("m_artifacts.at(14)->m_artimaxLevel", m_artifacts.at(14)->m_artimaxLevel, allocator);
		document.AddMember("m_artifacts.at(14)->m_artiDpsUp", m_artifacts.at(14)->m_artiDpsUp, allocator);

	}
	if (m_artifacts.size() > 15)
	{
		document.AddMember("m_artifacts.at(15)->m_artiDpsUp", m_artifacts.at(15)->m_artiDpsUp, allocator);
		document.AddMember("m_artifacts.at(15)->m_artifactID", m_artifacts.at(15)->m_artifactID, allocator);
		document.AddMember("m_artifacts.at(15)->m_artifactLevel", m_artifacts.at(15)->m_artifactLevel, allocator);
		document.AddMember("m_artifacts.at(15)->m_artimaxLevel", m_artifacts.at(15)->m_artimaxLevel, allocator);
		document.AddMember("m_artifacts.at(15)->m_artiDpsUp", m_artifacts.at(15)->m_artiDpsUp, allocator);

	}
	if (m_artifacts.size() > 16)
	{
		document.AddMember("m_artifacts.at(16)->m_artiDpsUp", m_artifacts.at(16)->m_artiDpsUp, allocator);
		document.AddMember("m_artifacts.at(16)->m_artifactID", m_artifacts.at(16)->m_artifactID, allocator);
		document.AddMember("m_artifacts.at(16)->m_artifactLevel", m_artifacts.at(16)->m_artifactLevel, allocator);
		document.AddMember("m_artifacts.at(16)->m_artimaxLevel", m_artifacts.at(16)->m_artimaxLevel, allocator);
		document.AddMember("m_artifacts.at(16)->m_artiDpsUp", m_artifacts.at(16)->m_artiDpsUp, allocator);

	}
	if (m_artifacts.size() > 17)
	{
		document.AddMember("m_artifacts.at(17)->m_artiDpsUp", m_artifacts.at(17)->m_artiDpsUp, allocator);
		document.AddMember("m_artifacts.at(17)->m_artifactID", m_artifacts.at(17)->m_artifactID, allocator);
		document.AddMember("m_artifacts.at(17)->m_artifactLevel", m_artifacts.at(17)->m_artifactLevel, allocator);
		document.AddMember("m_artifacts.at(17)->m_artimaxLevel", m_artifacts.at(17)->m_artimaxLevel, allocator);
		document.AddMember("m_artifacts.at(17)->m_artiDpsUp", m_artifacts.at(17)->m_artiDpsUp, allocator);

	}
	if (m_artifacts.size() > 18)
	{
		document.AddMember("m_artifacts.at(18)->m_artiDpsUp", m_artifacts.at(18)->m_artiDpsUp, allocator);
		document.AddMember("m_artifacts.at(18)->m_artifactID", m_artifacts.at(18)->m_artifactID, allocator);
		document.AddMember("m_artifacts.at(18)->m_artifactLevel", m_artifacts.at(18)->m_artifactLevel, allocator);
		document.AddMember("m_artifacts.at(18)->m_artimaxLevel", m_artifacts.at(18)->m_artimaxLevel, allocator);
		document.AddMember("m_artifacts.at(18)->m_artiDpsUp", m_artifacts.at(18)->m_artiDpsUp, allocator);

	}
	if (m_artifacts.size() > 19)
	{
		document.AddMember("m_artifacts.at(19)->m_artiDpsUp", m_artifacts.at(19)->m_artiDpsUp, allocator);
		document.AddMember("m_artifacts.at(19)->m_artifactID", m_artifacts.at(19)->m_artifactID, allocator);
		document.AddMember("m_artifacts.at(19)->m_artifactLevel", m_artifacts.at(19)->m_artifactLevel, allocator);
		document.AddMember("m_artifacts.at(19)->m_artimaxLevel", m_artifacts.at(19)->m_artimaxLevel, allocator);
		document.AddMember("m_artifacts.at(19)->m_artiDpsUp", m_artifacts.at(19)->m_artiDpsUp, allocator);

	}
	if (m_artifacts.size() > 20)
	{
		document.AddMember("m_artifacts.at(20)->m_artiDpsUp", m_artifacts.at(20)->m_artiDpsUp, allocator);
		document.AddMember("m_artifacts.at(20)->m_artifactID", m_artifacts.at(20)->m_artifactID, allocator);
		document.AddMember("m_artifacts.at(20)->m_artifactLevel", m_artifacts.at(20)->m_artifactLevel, allocator);
		document.AddMember("m_artifacts.at(20)->m_artimaxLevel", m_artifacts.at(20)->m_artimaxLevel, allocator);
		document.AddMember("m_artifacts.at(20)->m_artiDpsUp", m_artifacts.at(20)->m_artiDpsUp, allocator);

	}
	if (m_artifacts.size() > 21)
	{
		document.AddMember("m_artifacts.at(21)->m_artiDpsUp", m_artifacts.at(21)->m_artiDpsUp, allocator);
		document.AddMember("m_artifacts.at(21)->m_artifactID", m_artifacts.at(21)->m_artifactID, allocator);
		document.AddMember("m_artifacts.at(21)->m_artifactLevel", m_artifacts.at(21)->m_artifactLevel, allocator);
		document.AddMember("m_artifacts.at(21)->m_artimaxLevel", m_artifacts.at(21)->m_artimaxLevel, allocator);
		document.AddMember("m_artifacts.at(21)->m_artiDpsUp", m_artifacts.at(21)->m_artiDpsUp, allocator);

	}
	if (m_artifacts.size() > 22)
	{
		document.AddMember("m_artifacts.at(22)->m_artiDpsUp", m_artifacts.at(22)->m_artiDpsUp, allocator);
		document.AddMember("m_artifacts.at(22)->m_artifactID", m_artifacts.at(22)->m_artifactID, allocator);
		document.AddMember("m_artifacts.at(22)->m_artifactLevel", m_artifacts.at(22)->m_artifactLevel, allocator);
		document.AddMember("m_artifacts.at(22)->m_artimaxLevel", m_artifacts.at(22)->m_artimaxLevel, allocator);
		document.AddMember("m_artifacts.at(22)->m_artiDpsUp", m_artifacts.at(22)->m_artiDpsUp, allocator);

	}
	if (m_artifacts.size() > 23)
	{
		document.AddMember("m_artifacts.at(23)->m_artiDpsUp", m_artifacts.at(23)->m_artiDpsUp, allocator);
		document.AddMember("m_artifacts.at(23)->m_artifactID", m_artifacts.at(23)->m_artifactID, allocator);
		document.AddMember("m_artifacts.at(23)->m_artifactLevel", m_artifacts.at(23)->m_artifactLevel, allocator);
		document.AddMember("m_artifacts.at(23)->m_artimaxLevel", m_artifacts.at(23)->m_artimaxLevel, allocator);
		document.AddMember("m_artifacts.at(23)->m_artiDpsUp", m_artifacts.at(23)->m_artiDpsUp, allocator);

	}
	if (m_artifacts.size() > 24)
	{
		document.AddMember("m_artifacts.at(24)->m_artiDpsUp", m_artifacts.at(24)->m_artiDpsUp, allocator);
		document.AddMember("m_artifacts.at(24)->m_artifactID", m_artifacts.at(24)->m_artifactID, allocator);
		document.AddMember("m_artifacts.at(24)->m_artifactLevel", m_artifacts.at(24)->m_artifactLevel, allocator);
		document.AddMember("m_artifacts.at(24)->m_artimaxLevel", m_artifacts.at(24)->m_artimaxLevel, allocator);
		document.AddMember("m_artifacts.at(24)->m_artiDpsUp", m_artifacts.at(24)->m_artiDpsUp, allocator);

	}
	if (m_artifacts.size() > 25)
	{
		document.AddMember("m_artifacts.at(25)->m_artiDpsUp", m_artifacts.at(25)->m_artiDpsUp, allocator);
		document.AddMember("m_artifacts.at(25)->m_artifactID", m_artifacts.at(25)->m_artifactID, allocator);
		document.AddMember("m_artifacts.at(25)->m_artifactLevel", m_artifacts.at(25)->m_artifactLevel, allocator);
		document.AddMember("m_artifacts.at(25)->m_artimaxLevel", m_artifacts.at(25)->m_artimaxLevel, allocator);
		document.AddMember("m_artifacts.at(25)->m_artiDpsUp", m_artifacts.at(25)->m_artiDpsUp, allocator);

	}
	if (m_artifacts.size() > 26)
	{
		document.AddMember("m_artifacts.at(26)->m_artiDpsUp", m_artifacts.at(26)->m_artiDpsUp, allocator);
		document.AddMember("m_artifacts.at(26)->m_artifactID", m_artifacts.at(26)->m_artifactID, allocator);
		document.AddMember("m_artifacts.at(26)->m_artifactLevel", m_artifacts.at(26)->m_artifactLevel, allocator);
		document.AddMember("m_artifacts.at(26)->m_artimaxLevel", m_artifacts.at(26)->m_artimaxLevel, allocator);
		document.AddMember("m_artifacts.at(26)->m_artiDpsUp", m_artifacts.at(26)->m_artiDpsUp, allocator);

	}
	if (m_artifacts.size() > 27)
	{
		document.AddMember("m_artifacts.at(27)->m_artiDpsUp", m_artifacts.at(27)->m_artiDpsUp, allocator);
		document.AddMember("m_artifacts.at(27)->m_artifactID", m_artifacts.at(27)->m_artifactID, allocator);
		document.AddMember("m_artifacts.at(27)->m_artifactLevel", m_artifacts.at(27)->m_artifactLevel, allocator);
		document.AddMember("m_artifacts.at(27)->m_artimaxLevel", m_artifacts.at(27)->m_artimaxLevel, allocator);
		document.AddMember("m_artifacts.at(27)->m_artiDpsUp", m_artifacts.at(27)->m_artiDpsUp, allocator);

	}
	if (m_artifacts.size() > 28)
	{
		document.AddMember("m_artifacts.at(28)->m_artiDpsUp", m_artifacts.at(28)->m_artiDpsUp, allocator);
		document.AddMember("m_artifacts.at(28)->m_artifactID", m_artifacts.at(28)->m_artifactID, allocator);
		document.AddMember("m_artifacts.at(28)->m_artifactLevel", m_artifacts.at(28)->m_artifactLevel, allocator);
		document.AddMember("m_artifacts.at(28)->m_artimaxLevel", m_artifacts.at(28)->m_artimaxLevel, allocator);
		document.AddMember("m_artifacts.at(28)->m_artiDpsUp", m_artifacts.at(28)->m_artiDpsUp, allocator);

	}
}
void ArtifactData::readUserDefault()
{
	std::string json = cocos2d::UserDefault::getInstance()->getStringForKey("UserDefault");
	rapidjson::Document jsd;
	jsd.Parse<8>(json.c_str());
	if (jsd.IsObject() && jsd.HasMember("m_artifactStone"))
	{
		m_artifactStone = jsd["m_artifactStone"].GetInt();
		m_artifactNum = jsd["m_artifactNum"].GetInt();
		m_dpsexper = jsd["m_dpsexper"].GetDouble();
		m_AllDpsMul = jsd["m_AllDpsMul"].GetDouble();
		m_exploreProb = jsd["m_exploreProb"].GetInt();
		m_explorePer = jsd["m_explorePer"].GetDouble();
		rmGoldPer = jsd["rmGoldPer"].GetDouble();
		tenGoldPer = jsd["tenGoldPer"].GetDouble();
		bossGoldPer = jsd["bossGoldPer"].GetDouble();
		bossHpS = jsd["bossHpS"].GetDouble();
		leaveGoldPer = jsd["leaveGoldPer"].GetDouble();
		heroLevelUpDown = jsd["heroLevelUpDown"].GetDouble();
		bossTimeUp = jsd["bossTimeUp"].GetDouble();
		servantLevelUpDown = jsd["servantLevelUpDown"].GetDouble();
		WaveDown = jsd["WaveDown"].GetDouble();
		servantUnlockDown = jsd["servantUnlockDown"].GetDouble();
	
		for (int i = 0; i < m_artifactNum; i++)
		{
			ArtiHave * arhave = new ArtiHave();
			arhave->m_artiDpsUp = jsd[cocos2d::StringUtils::format("m_artifacts.at(%d)->m_artiDpsUp", i).c_str()].GetDouble();
			arhave->m_artifactID = jsd[cocos2d::StringUtils::format("m_artifacts.at(%d)->m_artifactID", i).c_str()].GetInt();
			arhave->m_artifactLevel = jsd[cocos2d::StringUtils::format("m_artifacts.at(%d)->m_artifactLevel", i).c_str()].GetInt();
			arhave->m_artimaxLevel = jsd[cocos2d::StringUtils::format("m_artifacts.at(%d)->m_artimaxLevel", i).c_str()].GetInt();
			m_artifacts.push_back(arhave);
		}
		
	

	}
}


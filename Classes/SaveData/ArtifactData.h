#ifndef _ArtifactData_H_
#define _ArtifactData_H_

#include<cocos2d.h>

struct ArtiHave
{
	int m_artifactID;
	int m_artifactStar;
	int m_artifactLevel;
	int m_artimaxLevel;
	float m_artiDpsUp;
};

class ArtifactData
{
public:
	static ArtifactData* getInstance();
	void subArtiStone(int i){ m_artifactStone -= i; cocos2d::CCNotificationCenter::getInstance()->postNotification("ArChange"); }
	int getArtiStone(){ return m_artifactStone; }
	int getNeededArStone();
	int getLevel(int id);
	void addArNum(int id);
	void arLevelUp(int id);
	void arStarUp(int id);

private:
	ArtifactData();
	~ArtifactData();
	int m_artifactStone;
	int m_artifactNum;
	int m_star;
	float m_AllDpsMul;
	ArtiHave m_artifacts[29];
	float m_dpsexper;
	int m_exploreProb;
	float m_explorePer;
	float rmGoldPer;
	float tenGoldPer;
	float bossGoldPer;
	float leaveGoldPer;
	float skillBanTimeS;
	float skilleffUp;
	float skillTimeA;
	float bossHpS;
	float heroLevelUpDown;
	float bossTimeUp;
	float artiUpPer;
	float servantLevelUpDown;
	float WaveDown;
	float servantUnlockDown;
};



#endif
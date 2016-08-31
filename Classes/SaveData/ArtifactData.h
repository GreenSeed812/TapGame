#ifndef _ArtifactData_H_
#define _ArtifactData_H_

#include<cocos2d.h>
#include "Tool/Rule.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
using namespace  rapidjson;
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
	void subArtiStone(int i){ m_artifactStone -= i; 
	cocos2d::CCNotificationCenter::getInstance()->postNotification("ArChange"); }
	void addArtiStone(int i){
		m_artifactStone += i;
		cocos2d::CCNotificationCenter::getInstance()->postNotification("ArChange");
	}
	int getArtiStone(){ return m_artifactStone; }
	int getArNum(){ return m_artifactNum; }
	int getNeededArStone();
	int getLevel(int id);
	int getMaxLevel(int id);
	int getStarNum(int id);
	int addArNum();
	void arLevelUp(int id);
	void arStarUp();
	void arReset(int id);
	void deleteArByID(int id);
	void saveUserDefault(Document& document);
	void readUserDefault();
public:
	float getAllDpsMul(){ return m_AllDpsMul; }
	float getdpsexper(){ return m_dpsexper; }
	int getexploreProb(){ return m_exploreProb; }
	float getexplorePer(){ return m_explorePer; }
	float getrmGoldPer(){ return rmGoldPer; }
	float gettenGoldPer(){ return tenGoldPer; }
	float getbossGoldPer(){ return bossGoldPer; }
	float getleaveGoldPer(){ return leaveGoldPer; }
	float getskillBanTimeS(int id){ return skillBanTimeS[id-1]; }
	float getskilleffUp(int id){ return skilleffUp[id-1]; }
	float getskillTimeA(int id){ return skillTimeA[id-1]; }
	float getbossHpS(){ return bossHpS; }
	float getHeroLevelupDown(){ return heroLevelUpDown; }
	float getbossTimeUp(){ return bossTimeUp; }
	float getWaveDown(){ return WaveDown; }
	float getSSUD(){ return servantUnlockDown; }
	float getSLUP(){ return servantLevelUpDown; }
private:
	ArtifactData();
	~ArtifactData();
	int m_artifactStone;
	int m_artifactNum;
	int m_star;
	float m_AllDpsMul;
	std::vector<ArtiHave*> m_artifacts;
	float m_dpsexper;
	int m_exploreProb;
	float m_explorePer;
	float rmGoldPer;
	float tenGoldPer;
	float bossGoldPer;
	float leaveGoldPer;
	float skillBanTimeS[6];
	float skilleffUp[6];
	float skillTimeA[6];
	float bossHpS;
	float heroLevelUpDown;
	float bossTimeUp;
	float artiUpPer;
	float servantLevelUpDown;
	float WaveDown;
	float servantUnlockDown;
};



#endif
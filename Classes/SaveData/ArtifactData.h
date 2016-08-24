#ifndef _ArtifactData_H_
#define _ArtifactData_H_
#include<cocos2d.h>
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
	int m_artifactID[29];
	int m_artifactStart[29];
	int m_artifactLevel[29];


};



#endif
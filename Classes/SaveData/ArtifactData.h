#ifndef _ArtifactData_H_
#define _ArtifactData_H_
class ArtifactData
{
public:
	static ArtifactData* getInstance();
	void subArtiStone(int i){ m_artifactStone -= i; }
	int getArtiStone(){ return m_artifactStone; }
	int getNeededArStone();
	int getLevel(int id){ return m_artifactLevel[id]; }
	void addArNum(int id);
	void arLevelUp(int id);
	void arStarUp(int id);

private:
	ArtifactData();
	~ArtifactData();
	int m_artifactStone;
	int m_artifactNum;
	float m_AllDpsMul;
	int m_artifactID[29];
	int m_artifactStart[29];
	int m_artifactLevel[29];

};



#endif
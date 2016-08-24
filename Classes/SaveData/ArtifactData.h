#ifndef _ArtifactData_H_
#define _ArtifactData_H_
class ArtifactData
{
public:
	static ArtifactData* getInstance();
	void subArtiStone(int i){ m_artifactStone -= i; }
	int getArtiStone(){ return m_artifactStone; }
	int getNeededArStone();
	void addArNum(int id);
private:
	ArtifactData();
	~ArtifactData();
	int m_artifactStone;
	int m_artifactNum;
	int m_star;

};



#endif
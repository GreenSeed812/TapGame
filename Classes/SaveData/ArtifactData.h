#ifndef _ArtifactData_H_
#define _ArtifactData_H_
class Artifact
{
public:
	static Artifact* getInstance();
	void subArtiStone(int i){ m_artifactStone -= i; }
	int getArtiStone(){ return m_artifactStone; }
	int getNeededArStone();
	void addArNum(int id);
private:
	Artifact();
	~Artifact();
	int m_artifactStone;
	int m_artifactNum;
};



#endif
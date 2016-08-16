#ifndef _State_H_
#define _State_H_
class State
{
public:
	
	static State* getInstance();
	void setBossButtonDown(bool boolean){ m_bossButton = boolean; }
	bool getBossButtonDown(){ return m_bossButton; }
private:
	bool m_bossButton;
	
	State();
	~State();
};



#endif
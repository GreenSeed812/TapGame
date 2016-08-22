#ifndef _State_H_
#define _State_H_
class MyState
{
public:
	
	static MyState* getInstance();
	void setBossButtonDown(bool boolean){ m_bossButton = boolean; }
	bool getBossButtonDown(){ return m_bossButton; }
private:
	bool m_bossButton;
	
	MyState();
	~MyState();
};



#endif
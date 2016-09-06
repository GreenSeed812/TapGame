#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
using namespace  rapidjson;
#ifndef _State_H_
#define _State_H_
class MyState
{
public:
	
	static MyState* getInstance();
	void setBossButtonDown(bool boolean){ m_bossButton = boolean; }
	bool getBossButtonDown(){ return m_bossButton; }
	void setTaped(bool tap){ m_Tap = tap; }
	void setKTap(bool tap){ m_keepTap = tap; }
	bool getTaped(){ return m_Tap; }
	bool getKTap(){ return m_keepTap; }
	void saveUserDefault(Document& document);
	void readUserDefault();
private:
	bool m_bossButton;
	bool m_Tap;
	bool m_keepTap;
	MyState();
	~MyState();
};



#endif
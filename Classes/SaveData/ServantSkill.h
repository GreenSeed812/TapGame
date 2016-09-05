
enum SKILLSTATE
{
	LOCK,
	UNLOCK
};

#ifndef _SERVANTSKILL_H_
#define _SERVANTSKILL_H_

#include <cocos2d.h>
using namespace cocos2d;

class ServantSkill : public cocos2d::Node
{
public:
	bool init();
	void setID(int id){ m_id = id; }
	void setState(int id);
	bool getState(int id){ return m_state; };
	std::string getText();
	CREATE_FUNC(ServantSkill);
private:
	int m_id;
	std::string m_text;
	SKILLSTATE m_state;
};

#endif
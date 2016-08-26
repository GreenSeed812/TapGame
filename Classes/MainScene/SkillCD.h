#ifndef _SkillCD_H_
#define _SkillCD_H_
#include <cocos2d.h>
class SkillCD :public cocos2d::Layer
{
public:
	bool init();

	CREATE_FUNC(SkillCD);
	void setPercentNow(float p);
	float getkpTime(){ return m_kpTime; }
	void initImage(int i);
	void initkpImage(int i);
private:
	float m_kpTime;
	float m_kpMaxTime;
	float m_percentNow;
	cocos2d::ProgressTimer * cd;
};



#endif // !_SkillCD_H_

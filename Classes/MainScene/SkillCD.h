#ifndef _SkillCD_H_
#define _SkillCD_H_
#include <cocos2d.h>
class SkillCD :public cocos2d::Layer
{
public:
	bool init();

	CREATE_FUNC(SkillCD);
	void setPercentNow(float p);
	void initImage(int i);
private:
	float m_percentNow;
	cocos2d::ProgressTimer * cd;
};



#endif // !_SkillCD_H_

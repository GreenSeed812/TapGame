#ifndef _AchieveLayer_H_
#define _AchieveLayer_H_
#include <cocos2d.h>
using namespace cocos2d;
class AchieveLayer :public cocos2d::Layer
{
public:
	virtual bool init();
	void initAchieveLayer();
	bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*){ return true; }
	CREATE_FUNC(AchieveLayer);

private:
	Node* m_rootNode;
	Node * m_bg;
	void setStar(int id, int num, const std::string& fileName);
	void setMoney(int id,int money);
	void setText(int id);
	void setNum(int id);
	void setBtn(int id, bool state, const std::string& fileName);
};



#endif
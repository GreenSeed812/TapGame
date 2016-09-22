#ifndef _LoadingScene_H_
#define _LoadingScene_H_
#include<cocos2d.h>
using namespace cocos2d;
class LoadingScene :public Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	CREATE_FUNC(LoadingScene);
private:
	Node * m_rootNode;
	void initLoading();
	void end(float);
};



#endif
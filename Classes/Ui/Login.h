
#ifndef _LOGIN_H_
#define _LOGIN_H_

#include <cocos2d.h>
using namespace cocos2d;

class Login : public cocos2d::Layer
{
public:
	bool init();
	void initLogin(bool check);
	CREATE_FUNC(Login);
private:
	Node * m_rootNode;
	bool m_isFrist;
};


#endif
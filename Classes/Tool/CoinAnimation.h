#include <cocos2d.h>
using namespace cocos2d;
class CoinAnimation
{
public:
	static CoinAnimation* getInstance();
	float getKnum(){ return m_knum; };
private:
	CoinAnimation();
	~CoinAnimation();
	float m_knum;
};


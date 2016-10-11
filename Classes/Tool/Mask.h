#include <cocos2d.h>
using namespace cocos2d;
class Mask :public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(Mask);
	virtual bool onTouchBegan(Touch *, Event*);
	void initAnimation();
	static int step;
	static bool existing;
	//static void saveUserdefault();
	//static void readUserdefault();
private:
	
	EventListenerTouchOneByOne *touchListener;
};


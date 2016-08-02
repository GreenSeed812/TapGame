#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <cocostudio\CocoStudio.h>
using namespace cocostudio;

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	void callBackFunc(Armature *, MovementEventType, const std::string&);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
private:
	Node* rootNode;
};

#endif // __HELLOWORLD_SCENE_H__

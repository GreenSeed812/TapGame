#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <cocostudio/CocoStudio.h>
#include "MainScene/ClickLayer.h"
#include "Ui/bossButton.h"
#include "ui/CocosGUI.h"
using namespace cocostudio;
using namespace ui;
class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	void callBackFunc(Armature *, MovementEventType, const std::string&);
	void createMonster();
	void killBoss();
	void uiInit();
	void uiCallBack();
	void playerSkillCallBack();
	bool initDownLayer(Node*&);
	bool initDownLayerAr(Node*&);
	bool initDownLayerSh(Node*&);
	void coinChange(Ref*);
	virtual void update(float dt);
	void skillCDUpdate(float dt);
	void skillKpCDUpdate(float dt);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
private:
	Node* rootNode;
	ClickLayer * clickLayer;
	Armature* armature;
	Node * m_heroLayer;
	Node * m_servantLayer;
	Node * m_artifactLayer;
	Node * m_shopLayer;
	Node * noNode;
	Node * m_skillButton[6];
	bool showTime;
	int timeNow;
	bossButton * bossBt;
	Button * m_skill[6];
};

#endif // __HELLOWORLD_SCENE_H__

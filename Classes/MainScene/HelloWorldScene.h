#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <cocostudio/CocoStudio.h>
#include "MainScene/ClickLayer.h"
#include "Ui/bossButton.h"
#include "ui/CocosGUI.h"
#include "Tool/MyNum.h"
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
	void ArChange(Ref*);
	void itemChange(Ref*);
	void itemEff9(Armature * armature, MovementEventType type, const std::string& action);
	void playerChange(Ref*);
	virtual void update(float dt);
	void showSiTime(int id,float dt);
	void skillCDUpdate(float dt);
	void skillKpCDUpdate(float dt);
	void skillEff(float);
	void skilleff1(Armature * armature, MovementEventType type, const std::string& action);
	void skilleff2(Ref*);
	void skillButtonInit();
	void attackeffection();
	void deleteSprite(Node *);
	void deleteArmature(Armature * armature, MovementEventType type, const std::string& action);
	void playMusic(Node * node);
	void gameContinue(Node*);
	void normalAtk();
	void shopItemEff(float);
	static void setBg(bool off_on){ m_bg = off_on; }
	static void setSou(bool off_on){ m_sou = off_on; }
	static void changeCount(bool state){ m_coutChange = state; }
	static void dayChange();
	static int getDay(){ return m_dayCount; }
	static int getSignCount(){ return m_signCount; }
	static tm* getTime(){ return m_time; }
	void initAr();
	void initSer();
	void runAni();
	void mapChange();
	bool mapInit();
	void bgChange(Node*);
	void relife();
	void shopItemCDUpDate(float dt);
	void saveSkillCD(float dt);
	void coinAni();
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
	int m_exchangeCount;
	bossButton * bossBt;
	Button * m_skill[6];
	Animation* ani;
	Sprite * effectSprite;
	MyNum num;
	bool m_hitlogic;
	bool m_gamelogic;
	int m_arCount;
	static bool m_bg;
	static bool m_sou;
	static bool m_coutChange;
	static int m_dayCount;
	static int m_signCount;
	static tm* m_time;
	Sprite* m_kssjEffect;
	Sprite* m_klgjEffect;
	
};

#endif // __HELLOWORLD_SCENE_H__

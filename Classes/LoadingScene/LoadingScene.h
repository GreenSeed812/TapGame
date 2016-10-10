#ifndef _LoadingScene_H_
#define _LoadingScene_H_
#include<cocos2d.h>
#include "extensions/cocos-ext.h"
USING_NS_CC_EXT;
USING_NS_CC;
class LoadingScene :public Layer,public cocos2d::ui::EditBoxDelegate
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(LoadingScene);
private:
	Node * m_rootNode;
	LayerColor * m_bgLayer;
	void initLoading();
	void end(float);
	void editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox){};
	void editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox){};
	void editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string &text){};
	void editBoxReturn(cocos2d::extension::EditBox *editBox){};
	void callback(Node *node);
	void callbackLogoH(Node * node);
	void callbackLogoG(Node * node);
};



#endif
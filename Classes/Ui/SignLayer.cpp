#include "SignLayer.h"
#include "ui/CocosGUI.h"
#include <cocostudio/CocoStudio.h> 
#include "Tool/SqLite.h"
#include "SaveData/PlayerData.h"
using namespace cocostudio;
using namespace cocos2d;
using namespace ui;
bool SignLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	rootNode = CSLoader::createNode("singLayer.csb");
	this->addChild(rootNode);
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(SignLayer::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
	initSignLayer();
	return true;
}

void SignLayer::initSignLayer()
{
	
	Button* bt = (Button*)rootNode->getChildByName("esc");
	bt->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type){
		if (type == Widget::TouchEventType::ENDED)
		{
			this->removeFromParent();
		}
	});
}
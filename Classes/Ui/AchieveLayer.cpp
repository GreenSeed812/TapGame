#include "AchieveLayer.h"
#include "ui/CocosGUI.h"
#include <cocostudio/CocoStudio.h> 
#include "Tool/SqLite.h"
#include "SaveData/PlayerData.h"
using namespace cocostudio;
using namespace cocos2d;
using namespace ui;
bool AchieveLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	m_rootNode = CSLoader::createNode("achieveLayer.csb");
	m_bg = m_rootNode->getChildByName("bg");
	this->addChild(m_rootNode);
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(AchieveLayer::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
	Button* bt = (Button*)m_rootNode->getChildByName("esc");
	bt->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type){
		if (type == Widget::TouchEventType::ENDED)
		{
			this->removeFromParent();
		}
	});

	return true;
}

void AchieveLayer::initAchieveLayer()
{
	for (size_t i = 0; i < 7; i++)
	{

	}
}

void AchieveLayer::setStar(int id, int num, const std::string& fileName)
{
	auto star = (ImageView*)m_bg->getChildByName(StringUtils::format("bgAchieve%d", id).c_str())->getChildByName(StringUtils::format("star%d", num).c_str());
	star->loadTexture(fileName);
}

void AchieveLayer::setMoney(int id,int num)
{
	auto money = (TextBMFont*)m_bg->getChildByName(StringUtils::format("bgAchieve%d", id).c_str())->getChildByName("money");
	money->setString(StringUtils::format("%d", num).c_str());
}

void AchieveLayer::setText(int id)
{
	auto text = (Text*)m_bg->getChildByName(StringUtils::format("bgAchieve%d", id).c_str())->getChildByName("Text");
	auto info = "";
	text->setString(info);
}

void AchieveLayer::setNum(int id)
{
	auto num = (TextBMFont*)m_bg->getChildByName(StringUtils::format("bgAchieve%d", id).c_str())->getChildByName("Text");
	auto text = "";
	num->setString(text);
}

void AchieveLayer::setBtn(int id, bool state, const std::string& fileName)
{
	auto btn = (Button*)m_bg->getChildByName(StringUtils::format("bgAchieve%d", id).c_str())->getChildByName("btn");
	btn->setVisible(state);
	if (sizeof(fileName)>= 0)
	{
		btn->loadTextureDisabled(fileName);
	}
}

#include "Ui/Login.h"
#include "SaveData/PlayerData.h"
#include "ui/CocosGUI.h"
#include <cocostudio/CocoStudio.h> 
#include "Tool/SqLite.h"
#include "SaveData/PlayerData.h"
using namespace cocostudio;
using namespace ui;

bool Login::init()
{
	if (!Layer::init())
	{
		return false;
	}

	m_rootNode = CSLoader::createNode("denglu.csb");
	this->addChild(m_rootNode);
}

void Login::initLogin(bool check)
{
	m_isFrist = check;
	auto head = (ImageView*)m_rootNode->getChildByName("head");
	auto nameBg = (ImageView*)m_rootNode->getChildByName("nameBg");
	auto name = (TextField*)m_rootNode->getChildByName("name");
	auto img = (ImageView*)m_rootNode->getChildByName("img");
	auto btn = (Button*)m_rootNode->getChildByName("btn");
	auto load = (TextBMFont*)m_rootNode->getChildByName("loadText");
	if (m_isFrist)
	{
		head->setVisible(true);
		nameBg->setVisible(true);
		name->setVisible(true);
		img->setVisible(true);
		btn->setVisible(true);
		load->setVisible(false);
		btn->addTouchEventListener([this,name](Ref* sender, Widget::TouchEventType type){
			if (type == Widget::TouchEventType::ENDED)
			{
				PlayerData::getInstance()->setName(name->getStringValue());
				//Director::getInstance()->
			}
		});
	}
	else
	{
		head->setVisible(false);
		nameBg->setVisible(false);
		name->setVisible(false);
		img->setVisible(false);
		btn->setVisible(false);
		load->setVisible(true);
	}
}
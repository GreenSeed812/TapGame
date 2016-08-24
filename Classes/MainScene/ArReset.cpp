
#include "MainScene/ArReset.h"
#include "ui/CocosGUI.h"
#include <cocostudio/CocoStudio.h> 
#include "SaveData/PlayerData.h"
#include "Tool/SqLite.h"
using namespace ui;

bool ArReset::init()
{
	if (!Layer::init())
	{
		return false;
	}

	m_node = CSLoader::createNode("ArtifactLayer1.csb");
	m_layer = (Layer*)m_node->getChildByName("layer");
	this->setContentSize(m_node->getContentSize());
	this->addChild(m_node);

	return true;
}

void ArReset::initArResetLayer(int id)
{
	//获取控件
	auto escBtn = (Button*)m_layer->getChildByName("esc");
	auto head = (Sprite*)m_layer->getChildByName("head");
	auto name = (Text*)m_layer->getChildByName("arName")->getChildByName("name");
	auto starLvNow = (Text*)m_layer->getChildByName("starBg")->getChildByName("starLvNow");
	auto starLvNext = (Text*)m_layer->getChildByName("starBg")->getChildByName("starLvNext");
	auto LvNow = (Text*)m_layer->getChildByName("starBg")->getChildByName("LvNow");
	auto LvNext = (Text*)m_layer->getChildByName("starBg")->getChildByName("LvNext");
	auto arLvNow = (Text*)m_layer->getChildByName("lvBg")->getChildByName("lvNowbg")->getChildByName("lvNow");
	auto arlvNext = (Text*)m_layer->getChildByName("lvBg")->getChildByName("lvNextbg")->getChildByName("lvNext");
	auto arNowNL = (Text*)m_layer->getChildByName("lvBg")->getChildByName("jiNeng1")->getChildByName("nengLi");
	auto arNowGJ = (Text*)m_layer->getChildByName("lvBg")->getChildByName("jiNeng1")->getChildByName("gonfJi");
	auto arNextNL = (Text*)m_layer->getChildByName("lvBg")->getChildByName("jiNeng2")->getChildByName("nengLi");
	auto arNextGJ = (Text*)m_layer->getChildByName("lvBg")->getChildByName("jiNeng2")->getChildByName("gonfJi");
	auto arStoneNum = (Text*)m_layer->getChildByName("lshNum")->getChildByName("num");
	auto zsNum = (Text*)m_layer->getChildByName("reset")->getChildByName("num");
	//设置控件
	head->setTexture(StringUtils::format("ui/downUi/artifact/%d.png",id+1));
	escBtn->addTouchEventListener([this](Ref* Sender, Widget::TouchEventType Event)
	{
		if (Event == Widget::TouchEventType::ENDED)
		{
			m_node->removeFromParent();
		}
	});
	


}
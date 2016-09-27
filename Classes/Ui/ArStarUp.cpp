
#include "Ui/ArStarUp.h"
#include "ui/CocosGUI.h"
#include <cocostudio/CocoStudio.h> 
#include "SaveData/ArtifactData.h"
using namespace ui;

ArStarUp * ArStarUp::g_asu = nullptr;

ArStarUp* ArStarUp::getInstance()
{
	if (g_asu == nullptr)
	{
		g_asu = new ArStarUp();
	}
	return g_asu;
}

bool ArStarUp::init(int id)
{
	if (!Layer::init())
	{
		return false;
	}

	m_bgLayer = LayerColor::create(Color4B(50, 50, 50, 155));
	this->addChild(m_bgLayer);
	m_node = CSLoader::createNode("starUp.csb");
	auto head = (Sprite*)m_node->getChildByName("head");
	auto name = (Text*)m_node->getChildByName("name");
	auto starNum = ArtifactData::getInstance()->getStarNum(id);
	head->setTexture(StringUtils::format("ui/downUi/artifact/%d.png",id+1).c_str());

	for (size_t i = 1; i <= starNum; i++)
	{
		auto star = m_node->getChildByName(StringUtils::format("star%d",i).c_str());
		auto color = Color3B(255, 255, 255);
		auto tinTo = TintTo::create(3,color);
		if (i == starNum)
		{
			auto action = Sequence::create(tinTo,CallFuncN::create(CC_CALLBACK_1(ArStarUp::arCallBack, this)), nullptr);
			star->runAction(action);
		}
		else
		{
			star->setColor(color);
		}
	}
	m_mainNode->addChild(m_node);
	return true;
}

void ArStarUp::arCallBack(Node * node)
{
	m_node->removeFromParent();
}
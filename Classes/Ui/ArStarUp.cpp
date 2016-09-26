
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

	m_node = CSLoader::createNode("starUp.csb");
	auto head = (Sprite*)m_node->getChildByName("head");
	auto name = (Text*)m_node->getChildByName("name");
	auto starNum = ArtifactData::getInstance()->getStarNum(id);
	
	for (size_t i = 1; i < starNum; i++)
	{
		auto star = m_node->getChildByName(StringUtils::format("star%d",i+1).c_str());
		star->setColor(ccc3(255,255,255));
	}
	this->addChild(m_node);
	return true;
}
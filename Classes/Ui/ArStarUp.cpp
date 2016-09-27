
#include "Ui/ArStarUp.h"
#include "ui/CocosGUI.h"
#include <cocostudio/CocoStudio.h> 
#include "SaveData/ArtifactData.h"
#include "Tool/SqLite.h"
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
	head->setTexture(StringUtils::format("ui/downUi/artifact/%d.png",id).c_str());
	name->setString(SqLite::getInstance()->getArtifactSkillByID(id).ar.NAME);
	for (size_t i = 1; i <= starNum; i++)
	{
		auto star = m_node->getChildByName(StringUtils::format("star%d",i).c_str());
		auto color = Color3B(255, 255, 255);
		auto tinTo = TintTo::create(3,color);
		if (i == starNum)
		{
			auto action = Sequence::create(tinTo,DelayTime::create(2),CallFuncN::create(CC_CALLBACK_1(ArStarUp::arCallBack, this)), nullptr);
			star->runAction(action);
		}
		else
		{
			star->setColor(color);
		}
	}
	m_bgLayer = LayerColor::create(Color4B(50, 50, 50, 155));
	m_mainNode->addChild(m_bgLayer);
	m_mainNode->addChild(m_node);

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [](Touch*, Event*)->bool{return true; };
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, m_node);
	
	return true;
}

void ArStarUp::arCallBack(Node * node)
{
	m_bgLayer->removeFromParent();
	m_node->removeFromParent();
}
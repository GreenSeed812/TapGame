#include "MainScene/ArtifactButton.h"
#include "ui/CocosGUI.h"
#include <cocostudio/CocoStudio.h> 
#include "SaveData/PlayerData.h"
#include "Tool/SqLite.h"
using namespace ui;

Node* ArtifactButton::g_lv = nullptr;

bool ArtifactButton::init()
{
	if (!Layer::init())
	{
		return false;
	}

	node = CSLoader::createNode("artifactNode.csb");
	m_layer = (Layer*)node->getChildByName("Layer");
	this->setContentSize(node->getContentSize());
	this->addChild(node);

	return true;
}

void ArtifactButton::initArtifactLayer(int id)
{
	/*auto newNode = ArtifactButton::create();
	PlayerData::getInstance()->addServantNum();
	newNode->initArtifactLayer(0);
	auto frame = Widget::create();
	frame->setContentSize(newNode->getContentSize());
	frame->addChild(newNode);
	ListView* lv = (ListView*)g_lv;
	lv->pushBackCustomItem(frame);*/
}

//void ArtifactButton::coinChange(Ref*)
//{
//
//}


#include "MainScene/ArReset.h"
#include "ui/CocosGUI.h"
#include <cocostudio/CocoStudio.h> 
#include "SaveData/PlayerData.h"
#include "SaveData/ArtifactData.h"
#include "SaveData/ShopData.h"
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
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [](Touch*, Event*)->bool{return true; };
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,m_layer);

	return true;
}

void ArReset::initArResetLayer(int id)
{
	CCNotificationCenter::getInstance()->addObserver(this, callfuncO_selector(ArReset::arResetChange), "arResetChange", nullptr);

	m_id = id;
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
	auto arNowGJ = (Text*)m_layer->getChildByName("lvBg")->getChildByName("jiNeng1")->getChildByName("gongJi");
	auto arNextNL = (Text*)m_layer->getChildByName("lvBg")->getChildByName("jiNeng2")->getChildByName("nengLi");
	auto arNextGJ = (Text*)m_layer->getChildByName("lvBg")->getChildByName("jiNeng2")->getChildByName("gongJi");
	auto arStoneNum = (Text*)m_layer->getChildByName("lshNum")->getChildByName("num");
	auto reSet = (Button*)m_layer->getChildByName("reset");
	auto reSetNum = (Text*)m_layer->getChildByName("reset")->getChildByName("num");

	//设置控件
	head->setTexture(StringUtils::format("ui/downUi/artifact/%d.png",id));
	name->setString(SqLite::getInstance()->getArtifactSkillByID(id).ar.NAME);
	auto starNum = ArtifactData::getInstance()->getStarNum(id);
	starLvNow->setString(StringUtils::format("%d", starNum).c_str());
	starLvNext->setString(StringUtils::format("%d", starNum+1).c_str());
	auto level = ArtifactData::getInstance()->getLevel(id);
	LvNow->setString(StringUtils::format("%d",level).c_str());
	LvNext->setString(StringUtils::format("%d", level + 1).c_str());
	arLvNow->setString(StringUtils::format("Lv%d", level).c_str());
	arlvNext->setString(StringUtils::format("Lv%d", level + 1).c_str());
	auto effid = SqLite::getInstance()->getArtifactSkillByID(id).ar.effid;
	auto effData = SqLite::getInstance()->getArtifactSkillByID(id).ar.effData;
	auto effDataUp = SqLite::getInstance()->getArtifactSkillByID(m_id).ar.effDataUp;
	effData += effDataUp*level;
	arNowNL->setString(SqLite::getInstance()->getSkillEffDis(effid) + StringUtils::format("+%.1f%%", effData * 100).c_str());
	effData += effDataUp*(level+1);
	arNextNL->setString(SqLite::getInstance()->getSkillEffDis(effid) + StringUtils::format("+%.1f%%", effData * 100).c_str());
	auto dpsData = SqLite::getInstance()->getArtifactSkillByID(m_id).ar.initAllDps;
	auto dpsUp = SqLite::getInstance()->getArtifactSkillByID(m_id).ar.AllDpsUp;
	auto levelNum = ArtifactData::getInstance()->getLevel(m_id);
	dpsData += dpsUp*(levelNum - 1);
	arNowGJ->setString(StringUtils::format("+%.1f%%",dpsData*100).c_str());
	dpsData += dpsUp*levelNum;
	arNextGJ->setString(StringUtils::format("+%.1f%%", dpsData * 100).c_str());
	arStoneNum->setString(StringUtils::format("%d", m_StoneNum).c_str());
	reSetNum->setString(StringUtils::format("%d", 200).c_str());

	reSet->addTouchEventListener([this](Ref* Sender, Widget::TouchEventType Event)
	{
		if (Event == Widget::TouchEventType::ENDED)
		{
			ShopData::getInstance()->subShopGold(200);
			ArtifactData::getInstance()->deleteArByID(m_id);
			ArtifactData::getInstance()->addArtiStone(m_StoneNum);
			m_StoneNum = 0;
			arResetChange(this);
		}
	});

	escBtn->addTouchEventListener([this](Ref* Sender, Widget::TouchEventType Event)
	{
		if (Event == Widget::TouchEventType::ENDED)
		{
			m_node->removeFromParent();
		}
	});
	arResetChange(this);
}

void ArReset::arResetChange(Ref*)
{
	auto reSet = (Button*)m_layer->getChildByName("reset");
	if (ShopData::getInstance()->getShopGold() >= 200)
	{
		reSet->setEnabled(true);
	}
	else
	{
		reSet->setEnabled(false);
	}
}
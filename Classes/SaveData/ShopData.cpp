#include "ShopData.h"
#include "Tool/SqLite.h"
#include "MissionData.h"
#include "SaveData/ArtifactData.h"
#include "Ui/ItemLayer.h"
#include "PlayerData.h"
static ShopData* g_SD = nullptr;
ShopData::ShopData()
	:m_shopGold(99999)
{
}

ShopData::~ShopData()
{

}

ShopData* ShopData::getInstance()
{
	if (!g_SD)
	{
		g_SD = new ShopData();
		g_SD->init();
	}
	return g_SD;
}
void ShopData::init()
{
	for (int i = 0; i < 13; i++)
	{
		m_items[i] = new ItemData();
		m_items[i]->ID = i;
		m_items[i]->isUsing = false;
		m_items[i]->itemNum = 0;
		m_items[i]->leftTime = SqLite::getInstance()->getItemByID(i)->time;
		m_num[i] = m_items[i]->leftTime;
	}
}
void ShopData::useItemByID(int id)
{
	getItemDataById(id)->leftTime = SqLite::getInstance()->getItemByID(id)->time;
	m_items[id]->isUsing = true;
	m_items[id]->itemNum--;
}
void ShopData::buyItemByID(int id)
{
	if (id < 4)
	{
		m_items[id]->itemNum++;
	}
	else
	{
		if (id == 5)
		{
			MissionData::getInstance()->addMissionTimesById(5);
			for (size_t i = 0; i < 6; i++)
			{
				PlayerData::getInstance()->setSkillCD(i+1,0);
			}	
		}
		getItemDataById(id)->leftTime = SqLite::getInstance()->getItemByID(id)->time;
		m_items[id]->isUsing = true;
	}
	CCNotificationCenter::getInstance()->postNotification("itemChange");
}
bool ShopData::getItemBeUsedById(int id)
{
	return m_items[id]->isUsing;
}
void ShopData::stopItemById(int id)
{
	m_items[id]->isUsing = false;
	CCNotificationCenter::getInstance()->postNotification("itemChange");
}

int ShopData::getCount(int id)
{
	return m_items[id]->itemNum;
}

void ShopData::subShopGold(int gold)
{
	m_shopGold -= gold; 
	PlayerData::getInstance()->saveUserData();
	CCNotificationCenter::getInstance()->postNotification("itemChange");
}
void ShopData::addShopGold(int gold)
{
	m_shopGold += gold; 
	PlayerData::getInstance()->saveUserData();
	CCNotificationCenter::getInstance()->postNotification("itemChange");
	
}

ItemData * ShopData::getItemDataById(int id)
{
	return m_items[id];
}
void ShopData::readUserData()
{
	std::string json = cocos2d::UserDefault::getInstance()->getStringForKey("UserDefault");
	rapidjson::Document jsd;
	jsd.Parse<8>(json.c_str());
	if (jsd.IsObject() && jsd.HasMember("m_items[12]->isUsing"))
	{
		for (int i = 0; i < 13; i++)
		{
			m_items[i]->leftTime = jsd[StringUtils::format("m_items[%d]->leftTime", i).c_str()].GetDouble();
			m_items[i]->itemNum = jsd[StringUtils::format("m_items[%d]->itemNum", i).c_str()].GetInt();
			m_items[i]->isUsing = jsd[StringUtils::format("m_items[%d]->isUsing", i).c_str()].GetBool();
		}
	}
	m_shopGold = jsd["m_shopGold"].GetInt();
}
void ShopData::setNum(int id){
	if (m_items[id]->isUsing)
	{
		if (m_num[id] < 60)
		{
			m_num[id]--;
		}
		else if ((m_num[id] / 60) >= 1 && (m_num[id] / 60) < 60)
		{
			m_num[id] -= 60;
		}
		if ((m_num[id] / 60) >= 60)
		{
			m_num[id] -= 3600;
		}
	}
	else
	{
		m_num[id] = m_items[id]->leftTime;
	}
}
void ShopData::saveUserData(Document& document)
{
	Document::AllocatorType& allocator = document.GetAllocator();
	document.AddMember("m_shopGold",m_shopGold,allocator);
	document.AddMember("m_items[0]->leftTime", m_items[0]->leftTime, allocator);
	document.AddMember("m_items[0]->itemNum",  m_items[0]->itemNum, allocator);
	document.AddMember("m_items[0]->isUsing", m_items[0]->isUsing, allocator);
	document.AddMember("m_items[1]->leftTime", m_items[1]->leftTime, allocator);
	document.AddMember("m_items[1]->itemNum", m_items[1]->itemNum, allocator);
	document.AddMember("m_items[1]->isUsing", m_items[1]->isUsing, allocator);
	document.AddMember("m_items[2]->leftTime", m_items[2]->leftTime, allocator);
	document.AddMember("m_items[2]->itemNum", m_items[2]->itemNum, allocator);
	document.AddMember("m_items[2]->isUsing", m_items[2]->isUsing, allocator);
	document.AddMember("m_items[3]->leftTime", m_items[3]->leftTime, allocator);
	document.AddMember("m_items[3]->itemNum", m_items[3]->itemNum, allocator);
	document.AddMember("m_items[3]->isUsing", m_items[3]->isUsing, allocator);
	document.AddMember("m_items[4]->leftTime", m_items[4]->leftTime, allocator);
	document.AddMember("m_items[4]->itemNum", m_items[4]->itemNum, allocator);
	document.AddMember("m_items[4]->isUsing", m_items[4]->isUsing, allocator);
	document.AddMember("m_items[5]->leftTime", m_items[5]->leftTime, allocator);
	document.AddMember("m_items[5]->itemNum", m_items[5]->itemNum, allocator);
	document.AddMember("m_items[5]->isUsing", m_items[5]->isUsing, allocator);
	document.AddMember("m_items[6]->leftTime", m_items[6]->leftTime, allocator);
	document.AddMember("m_items[6]->itemNum", m_items[6]->itemNum, allocator);
	document.AddMember("m_items[6]->isUsing", m_items[6]->isUsing, allocator);
	document.AddMember("m_items[7]->leftTime", m_items[7]->leftTime, allocator);
	document.AddMember("m_items[7]->itemNum", m_items[7]->itemNum, allocator);
	document.AddMember("m_items[7]->isUsing", m_items[7]->isUsing, allocator);
	document.AddMember("m_items[8]->leftTime", m_items[8]->leftTime, allocator);
	document.AddMember("m_items[8]->itemNum", m_items[8]->itemNum, allocator);
	document.AddMember("m_items[8]->isUsing", m_items[8]->isUsing, allocator);
	document.AddMember("m_items[9]->leftTime", m_items[9]->leftTime, allocator);
	document.AddMember("m_items[9]->itemNum", m_items[9]->itemNum, allocator);
	document.AddMember("m_items[9]->isUsing", m_items[9]->isUsing, allocator);
	document.AddMember("m_items[10]->leftTime", m_items[10]->leftTime, allocator);
	document.AddMember("m_items[10]->itemNum", m_items[10]->itemNum, allocator);
	document.AddMember("m_items[10]->isUsing", m_items[10]->isUsing, allocator);
	document.AddMember("m_items[11]->leftTime", m_items[11]->leftTime, allocator);
	document.AddMember("m_items[11]->itemNum", m_items[11]->itemNum, allocator);
	document.AddMember("m_items[11]->isUsing", m_items[11]->isUsing, allocator);
	document.AddMember("m_items[12]->leftTime", m_items[12]->leftTime, allocator);
	document.AddMember("m_items[12]->itemNum", m_items[12]->itemNum, allocator);
	document.AddMember("m_items[12]->isUsing", m_items[12]->isUsing, allocator);	
}

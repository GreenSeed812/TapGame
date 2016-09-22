#include "ShopData.h"
#include "Tool/SqLite.h"
#include "MissionData.h"
#include "Ui/ItemLayer.h"
static ShopData* g_SD = nullptr;
ShopData::ShopData()
:m_shopGold(10000)
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
		}
		getItemDataById(id)->leftTime = SqLite::getInstance()->getItemByID(id)->time;
		m_items[id]->isUsing = true;
	}

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
}
void ShopData::addShopGold(int gold)
{
	m_shopGold += gold; 
}

ItemData * ShopData::getItemDataById(int id)
{
	return m_items[id];
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
			m_num[id]-=60;
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
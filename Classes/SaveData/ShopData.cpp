#include "ShopData.h"
static ShopData* g_SD = nullptr;
ShopData::ShopData()
	:m_shopGold(100000)
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
	}
	return g_SD;
}
void ShopData::useItemByID(int i)
{
	if (i == 1)
	{
		m_haichaoS = true;
	}
	else if (i == 2)
	{
		m_shandianS = true;
	}
	else if (i == 3)
	{
		m_huoshe = true;
	}
	else if (i == 4)
	{
		m_fengnu = true;
	}
	
}
void ShopData::buyItemByID(int i)
{
	if (i == 1)
	{
		m_haiChao++;
	}
	else if (i == 2)
	{
		m_shandian++;
	}
	else if (i == 3)
	{
		m_huoshe++;
	}
	else if (i == 4)
	{
		m_fengnu++;
	}
	else if (i == 5)
	{
		m_bankS = true;
	}
	else if (i == 6)
	{
		
	}
}
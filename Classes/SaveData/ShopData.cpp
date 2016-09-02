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
		m_keepGodPowerS = true;
	}
	else if (i == 7)
	{
		m_refreshS = true;
	}
	else if (i == 8)
	{

	}
	else if (i == 9)
	{

	}
	else if (i == 10)
	{
		m_relifeS = true;
	}
	else if (i == 11)
	{
		m_whosyourdaddyS = true;
	}
	else if (i == 12)
	{
		
	}
}
bool ShopData::getItemBeUsedById(int id)
{
	if (id == 1)
	{
		return m_haichaoS;
	}
	else if (id == 2)
	{
		return m_shandianS;
	}
	else if (id == 3)
	{
		return m_huosheS;
	}
	else if (id == 4)
	{
		return m_fengnuS;
	}
	else if (id == 5)
	{
		return m_bankS;
	}
	else if (id == 6)
	{
		return m_keepGodPowerS;
	}
	else if (id == 7)
	{
		return m_refreshS;
	}
	else if (id == 8)
	{

	}
	else if (id == 9)
	{

	}
	else if (id == 10)
	{
		return m_relifeS;
	}
	else if (id == 11)
	{
		return m_whosyourdaddyS;
	}
	else if (id == 12)
	{
	
	}
}
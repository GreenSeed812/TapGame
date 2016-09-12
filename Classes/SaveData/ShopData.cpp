#include "ShopData.h"
static ShopData* g_SD = nullptr;
ShopData::ShopData()
	:m_shopGold(0)
	, m_haiChao(0)
	, m_shandian(0)
	, m_huoshe(0)
	, m_fengnu(0)
	,m_haichaoS(false)
	,m_shandianS(false)
	,m_huosheS(false)
	,m_fengnuS(false)
	,m_bankS(false)
	,m_keepGodPowerS(false)
	,m_refreshS(false)
	,m_whosyourdaddyS(false)
	,m_treasurebayS(false)
	,m_luckyCoinS(false)
	,m_kuangluanS(false)
	,m_relifeS(false)
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
void ShopData::useItemByID(int id)
{
	switch (id+1)
	{
	case 1:
		m_haiChao--;
		m_haichaoS = true;
		break;
	case 2:
		m_shandian--;
		m_shandianS = true;
		break;
	case 3:
		m_huoshe--;
		m_huosheS = true;
		break;
	case 4:
		m_fengnu--;
		m_fengnuS = true;
		break;
	}
}
void ShopData::buyItemByID(int id)
{
	id += 1;
	if (id == 1)
	{
		m_haiChao++;
		m_haichaoS = false;
	}
	else if (id == 2)
	{
		m_shandian++;
		m_shandianS = false;
	}
	else if (id == 3)
	{
		m_huoshe++;
		m_huosheS = false;
	}
	else if (id == 4)
	{
		m_fengnu++;
		m_fengnuS = false;
	}
	else if (id == 5)
	{
		m_bankS = true;
	}
	else if (id == 6)
	{
		m_keepGodPowerS = true;
	}
	else if (id == 7)
	{
		m_refreshS = true;
	}
	else if (id == 8)
	{
		return;
	}
	else if (id == 9)
	{
		return;
	}
	else if (id == 10)
	{
		m_relifeS = true;
	}
	else if (id == 11)
	{
		m_whosyourdaddyS = true;
	}
	else if (id == 12)
	{
		m_treasurebayS = true;
		
	}
	else if (id == 13)
	{
		m_luckyCoinS = true;
	}
	else if (id == 14)
	{
		m_kuangluanS = true;
	}
}
bool ShopData::getItemBeUsedById(int id)
{
	id += 1;
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
		return 0;
	}
	else if (id == 9)
	{
		return 0;
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
		return m_treasurebayS ;

	}
	else if (id == 13)
	{
		return m_luckyCoinS;
	}
	else if (id == 14)
	{
		return m_kuangluanS;
	}

}
void ShopData::stopItemById(int id)
{
	id += 1;
	if (id == 1)
	{
		m_haichaoS = false;
	}
	else if (id == 2)
	{
		m_shandianS = false;
	}
	else if (id == 3)
	{
		m_huosheS = false;
	}
	else if (id == 4)
	{
		m_fengnuS = false;
	}
	else if (id == 5)
	{
		m_bankS = false;
	}
	else if (id == 6)
	{
		m_keepGodPowerS = false;
	}
	else if (id == 7)
	{
		m_refreshS = false;
	}
	else if (id == 8)
	{

	}
	else if (id == 9)
	{

	}
	else if (id == 10)
	{
		m_relifeS = false;
	}
	else if (id == 11)
	{
		m_whosyourdaddyS = false;
	}
	else if (id == 12)
	{
		m_treasurebayS = false;
	}
	else if (id == 13)
	{
		m_luckyCoinS = false;
	}
	else if (id == 14)
	{
		m_kuangluanS = false;
	}
}

int ShopData::getCount(int id)
{
	switch (id+1)
	{
	case 1:
		return m_haiChao;
	case 2:
		return m_shandian;
	case 3:
		return m_huoshe;
	case 4:
		return m_fengnu;
	}
}

void ShopData::subShopGold(int gold)
{
	m_shopGold -= gold; 
}
void ShopData::addShopGold(int gold)
{
	m_shopGold += gold; 
}


#include "ShopData.h"
static ShopData* g_SD = nullptr;
ShopData::ShopData()
	:m_shopGold(1000)
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
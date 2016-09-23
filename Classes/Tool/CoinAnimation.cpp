#include "CoinAnimation.h"
static CoinAnimation * g_ani;
CoinAnimation::CoinAnimation()
{
	m_knum = 1;
}

CoinAnimation::~CoinAnimation()
{
}
CoinAnimation* CoinAnimation::getInstance()
{
	if (!g_ani)
	{
		g_ani = new CoinAnimation();
	}
	return g_ani;
}
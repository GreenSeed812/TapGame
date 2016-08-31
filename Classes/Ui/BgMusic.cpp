
#include "BgMusic.h"

BgMusic*  bgm = nullptr;

bool BgMusic::init()
{
	m_count = 0;
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BG_MUSIC);
	SimpleAudioEngine::getInstance()->preloadEffect(EFFECT_MUSIC);
	return true;
}

BgMusic* BgMusic::getInstance()
{
	if (bgm == nullptr)
	{
		bgm = new BgMusic();
		bgm->init();
	}
	return bgm;
}

void BgMusic::playBg(bool off_on)
{
	if (off_on)
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic(BG_MUSIC);		
	}
	else
	{
		SimpleAudioEngine::getInstance()->stopBackgroundMusic(BG_MUSIC);
	}
}

void BgMusic::playEff()
{
	SimpleAudioEngine::getInstance()->playEffect(EFFECT_MUSIC);
}
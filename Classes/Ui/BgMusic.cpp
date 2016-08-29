
#include "BgMusic.h"

BgMusic*  bgm = nullptr;

bool BgMusic::init()
{
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

void BgMusic::playEff(bool off_on)
{
	if (off_on)
	{
		SimpleAudioEngine::getInstance()->playEffect(EFFECT_MUSIC);
	}
	else
	{
		SimpleAudioEngine::getInstance()->stopAllEffects();
	}
}
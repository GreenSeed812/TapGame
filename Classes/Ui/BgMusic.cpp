
#include "BgMusic.h"

BgMusic*  bgm = nullptr;

void BgMusic::init()
{
	m_count = 0;
	m_Off_ON = true;
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BG_MUSIC);
	SimpleAudioEngine::getInstance()->preloadEffect(EFFECT_MUSIC);
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume((SimpleAudioEngine::getInstance()->getBackgroundMusicVolume() + 0.2f));	
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
		SimpleAudioEngine::getInstance()->playBackgroundMusic(BG_MUSIC,true);	
	}
	else
	{
		SimpleAudioEngine::getInstance()->setEffectsVolume((SimpleAudioEngine::getInstance()->getEffectsVolume() - 1.0f));
		SimpleAudioEngine::getInstance()->stopBackgroundMusic(BG_MUSIC);
	}
}

void BgMusic::playEff()
{
	if (m_Off_ON)
	{
		SimpleAudioEngine::getInstance()->playEffect(EFFECT_MUSIC);
	}
}
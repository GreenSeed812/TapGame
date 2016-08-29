#ifndef _BGMUSIC_H_
#define _BGMUSIC_H_

#include <cocos2d.h>
#include "SimpleAudioEngine.h"
using namespace cocos2d;
using namespace CocosDenshion;

#define BG_MUSIC "musics/Comradeship.mp3"
#define EFFECT_MUSIC "musics/5474.mp3"

class BgMusic
{
public:
	bool init();
	static BgMusic* getInstance();
	void playBg(bool off_on);
	void playEff();
private:
	BgMusic(){}
	bool m_Off_ON;
	int m_count;
};


#endif
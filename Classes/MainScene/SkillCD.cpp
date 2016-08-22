#include "SkillCD.h"
#include "ui/CocosGUI.h"
#include <cocostudio/CocoStudio.h> 
using namespace cocostudio;
using namespace cocos2d;
using namespace ui;
bool SkillCD::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto rootNode = CSLoader::createNode("");
	return true;
}

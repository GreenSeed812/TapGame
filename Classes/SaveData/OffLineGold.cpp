
#include "OffLineGold.h"
OffLineGold* offLine = nullptr;
bool OffLineGold::init()
{
	if (!Node::init())
	{
		return false;
	}
	return true;
}

OffLineGold * OffLineGold::getInstance()
{
	if (offLine == nullptr)
	{
		offLine = new OffLineGold();
		offLine->init();
	}
	return offLine;
}

double OffLineGold::getMillSecond()
{
	struct timeval tv;
	gettimeofday(&tv, nullptr);

	log("CurrentTime MillSecond %f", (double)tv.tv_sec * 1000 + (double)tv.tv_usec / 1000);

	return (double)tv.tv_sec * 1000 + (double)tv.tv_usec / 1000;
}
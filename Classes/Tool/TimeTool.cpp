
#include "TimeTool.h"
TimeTool * TimeTool::time_tool = nullptr;
tm * TimeTool::g_time = nullptr;

TimeTool* TimeTool::getInstance()
{
	if (time_tool == nullptr)
	{
		time_tool = new TimeTool();
	}
	return time_tool;
}

tm* TimeTool::getcurrTime()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

	struct timeval now;
	struct tm* time;

	gettimeofday(&now, NULL);

	time = localtime(&now.tv_sec);
	return time;

#endif

#if ( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
	time_t timep;
	time(&timep);
	auto tm = localtime(&timep);
	return tm;
#endif
}

int TimeTool::getTime()
{

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

			struct timeval now;
			gettimeofday(&now, NULL);
			return now.tv_sec;

	#endif

	#if ( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )

			time_t timep;
			time(&timep);
			return timep;

	#endif

}

tm* TimeTool::calTime(int time)
{
	time_t timeps;
	timeps = (time_t)time;
	auto times = localtime(&timeps);
	return times;
}
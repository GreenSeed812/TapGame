
#ifndef _TIMETOOL_H_
#define _TIMETOOL_H_

#include <cocos2d.h>
USING_NS_CC;

class TimeTool
{
public:
	static TimeTool* getInstance();
	tm* getcurrTime();
	int getTime();
	tm* calTime(int time);
	static TimeTool * time_tool;
	static tm* g_time;
private:
	TimeTool(){};
};

#endif
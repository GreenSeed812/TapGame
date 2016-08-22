#ifndef __Ruler_H__
#define __Ruler_H__
#include<string>
#include "Tool/MyNum.h"
class Ruler
{
public:
	static Ruler* getInstance();
	std::string showNum(MyNum);
	MyNum addNum(MyNum , MyNum );
	MyNum subNum(MyNum , MyNum );
	MyNum multiplay(MyNum,double scale);
	MyNum multiplayUp(MyNum num, double scale);
	MyNum addNumUp(MyNum , MyNum );
	MyNum addNumS(MyNum, MyNum);
	int devid(MyNum,MyNum);
	bool Zero(MyNum num){ if (num.Mathbit <= 0 && num.number <= 0) return true; else return false; }
private:
	int Ary;									// 进制(final)
	int Accuracy;								// 除法精度位数(final)
	std::string unit[32];
	Ruler();
	~Ruler();
	MyNum addRule(MyNum, MyNum);
	
};


#endif
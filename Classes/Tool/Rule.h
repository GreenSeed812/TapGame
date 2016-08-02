#ifndef __Ruler_H__
#define __Ruler_H__
#include<string>
struct MyNum
{
	double number = 0;
	int Mathbit = 0;

};
class Ruler
{
public:
	static Ruler* getInstance();
	std::string showNum(MyNum*);
	MyNum* addNum(MyNum *, MyNum *);
	MyNum* subNum(MyNum *, MyNum *);
	MyNum* multiplay(MyNum*,double scale);
	int devid(MyNum*,MyNum*);
private:
	int Ary;									// 进制(final)
	int Accuracy;								// 除法精度位数(final)
	std::string unit[32];
	Ruler();
	~Ruler();
	MyNum* addRule(MyNum*, MyNum*);
	
};


#endif
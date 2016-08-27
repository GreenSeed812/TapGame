#include "Tool/Rule.h"
#include <cocos2d.h>
using namespace cocos2d;
static Ruler * g_rule = nullptr;
Ruler::Ruler()
	:Ary(1000)
	, Accuracy(3)
{
	unit[0] = "";
	unit[1] = "k";
	unit[2] = "m";
	unit[3] = "b";
	unit[4] = "t";
	for (int i = 0; i < 26; i++)
	{
		std::string s;
		s = StringUtils::format( "%c%c", 'a' + i, 'a' + i);
		unit[i + 5] = s;

	}
	for (int i = 0; i < 26; i++)
	{
		std::string s;
		s = StringUtils::format("%c+", 'a' + i);
		unit[i + 31] = s;

	}
	unit[59] = "¡Þ";
}

Ruler::~Ruler()
{
}
Ruler* Ruler::getInstance()
{
	if (!g_rule)
	{
		g_rule = new Ruler();
		
	}
	return g_rule;

}

std::string Ruler::showNum(MyNum num)
{
	if (num.number == 0)
	{
		return "0";
	}
	
	std::string s;
	s = StringUtils::format("%.1lf", num.number);
	//sprintf_s(s, "%lf", num->number);
	if (num.Mathbit == 0)
	{
		for (int i = 0; i < 10; i++)
		{
			if (s[i] == '.')
			{
				s[i] = '\0';
				break;
			}

		}
	}
	else
	{
		for (int i = 0; i < 10; i++)
		{
			if (s[i] == '.')
			{
				s[i + 2] = '\0';
				break;
			}

		}
	}
	
	s += unit[num.Mathbit] ;
	
	return s;
}

MyNum Ruler::addNum(MyNum num1, MyNum num2)
{
	MyNum num;
	if (num1.Mathbit > num2.Mathbit)
	{
		num = addRule(num1, num2);
	}
	else if (num1.Mathbit == num2.Mathbit)
	{
		
		num.Mathbit = num1.Mathbit;
		num.number = num1.number + num2.number;
	}
	else
	{
		num = addRule(num2, num1);
	}
	if (num.number >= 1000)
	{
		num.number /= 1000;
		num.Mathbit++;
	}
	
	return num;

	
}
MyNum Ruler::addNumS(MyNum num1, MyNum num2)
{
	MyNum num = addNum(num1, num2);
	if (num.Mathbit == 0)
	{
		int intNum = num.number + 0.5;
		num.number = intNum;
	}
	return num;
}
MyNum Ruler::addNumUp(MyNum num1, MyNum num2)
{
	MyNum num = addNum(num1, num2);
	if (num.Mathbit == 0)
	{
		int intNum = num.number;
		if (intNum < num.number)
			num.number = intNum + 1;
	
	}
	return num;
}
MyNum Ruler::addRule(MyNum big, MyNum little)
{
	MyNum num = MyNum();
	if (big.Mathbit - little.Mathbit > 2)
	{
		num.number = big.number;
		num.Mathbit = big.Mathbit;
	}
	else
	{
		auto circle = big.Mathbit - little.Mathbit;
		auto scale = 1;
		for (int i = 0; i < circle; i++)
		{
			scale *= Ary;
		}
		num.number = big.number + little.number / scale;
		num.Mathbit = big.Mathbit;
	}
	if (num.Mathbit == 0)
	{
		int intNum = num.number + 0.5;
		num.number = intNum;
	}
	return num;

}
MyNum Ruler::subNum(MyNum num1, MyNum num2)
{
	MyNum num;
	if (num1.Mathbit < num2.Mathbit)
	{
		num.Mathbit = 0;
		num.number = 0;
	}
	else if (num1.Mathbit == num2.Mathbit)
	{
		if (num1.number < num2.number)
			num.number = 0;
		else
		{
			num.number = num1.number - num2.number;
			num.Mathbit = num1.Mathbit;
		}
	}
	else if (num1.Mathbit - num2.Mathbit > 7)
	{
		num = num1;
	}
	else
	{
		auto circle = num1.Mathbit - num2.Mathbit;
		auto scale = 1;
		for (size_t i = 0; i < circle; i++)
		{
			scale *= Ary;
		}
		num.Mathbit = num1.Mathbit;
		num.number = num1.number - num2.number / scale;
		
	}
	if (num.number < 1 && num.Mathbit > 0)
	{
		num.Mathbit--;
		num.number *= 1000;
	}
	
	return num;
}

MyNum Ruler::multiplay(MyNum num, double scale)
{
	MyNum newNum ;
	while (scale > 1000)
	{
		newNum.Mathbit++;
		scale /= 1000;
	}
	
	newNum.number = num.number*scale;
	if (newNum.number >= 1000)
	{
		newNum.number /= 1000;
		newNum.Mathbit++;
	}
	if (newNum.number<1)
	{
		newNum.number *= 1000;
		newNum.Mathbit--;
	}
	newNum.Mathbit += num.Mathbit;
	return newNum;
}
MyNum Ruler::multiplayUp(MyNum num, double scale)
{
	auto retNum = multiplay(num, scale);
	if (retNum.Mathbit == 0)
	{
		int n = retNum.number;
		if (retNum.number - n != 0)
		{
			retNum.number = n+1;
		}
	}
	return retNum;
}

int Ruler::devid(MyNum dividend, MyNum divisor)
{
	auto num = new MyNum();
	
	num->Mathbit = dividend.Mathbit - divisor.Mathbit;
	auto scale = 1;
	for (size_t i = 0; i < num->Mathbit; i++)
	{
		scale *= 1000;
	}
	double res;
	res = dividend.number * scale / divisor.number;
	return res;
}

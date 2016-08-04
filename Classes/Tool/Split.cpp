#include "Split.h"
static Split *m_sp = nullptr;

Split::Split()
{

}

Split::~Split()
{
}

Split * Split::getInstance()
{
	if (!m_sp)
	{
		m_sp = new Split();
	}
	return m_sp;
}
list<string> Split::strsplit(string strAll, string strS)
{
	list<string> list;
	string str;
	for (int i = 0; i < strAll.length(); i++)
	{
		
		
		if (strAll.at(i) == strS.at(0))
		{
			list.push_back(str);
			str.clear();
		}
		else
		{
			str.push_back(strAll.at(i));
		}
	}
	list.push_back(str);
	return list;
}
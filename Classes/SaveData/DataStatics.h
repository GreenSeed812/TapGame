#include <cocos2d.h>
class DataStatics
{
public:
	static DataStatics* getInstance();
	std::string getCurrent(int id);
	std::string getStatic(int id);
	void setGameDay(int time){ m_initGameDay = time; };
	void setRelifeTime(int time){ m_lastRelife = time; }
private:
	DataStatics();
	~DataStatics();
	int m_playerTotalLevel;
	int m_servantMaxNum;
	int m_exploreNum;
	int m_lastRelife;
	int m_initGameDay;
};


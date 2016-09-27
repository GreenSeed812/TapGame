#include <cocos2d.h>
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
using namespace  rapidjson;
class DataStatics
{
public:
	static DataStatics* getInstance();
	std::string getCurrent(int id);
	std::string getStatic(int id);
	void setGameDay(int time){ m_initGameDay = time; };
	void setRelifeTime(int time){ m_lastRelife = time; }
public:
	void playerLevelUp(){ m_playerTotalLevel++; }
	int getservantMaxNum(){ return m_servantMaxNum; }
	void setservantNumMax(int num){ m_servantMaxNum = num; }
public:
	void saveUserDefault(Document& document);
	void readUserDefault();
private:
	DataStatics();
	~DataStatics();
	int m_playerTotalLevel;
	int m_servantMaxNum;
	int m_lastRelife;
	int m_initGameDay;
};


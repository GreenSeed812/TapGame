
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
using namespace  rapidjson;

class MissionData
{
public:

	static MissionData* getInstance();
	void reset();
	void addMissionTimesById(int id);
	int getMissionTimesById(int id){ return m_missionTimes[id]; };
	void setMissionTimesById(int id, int num){ m_missionTimes[id] = num; }
	void saveUserDefault(Document& document);
	void readUserDefault();
private:
	MissionData();
	~MissionData();
	int m_missionTimes[9];

};


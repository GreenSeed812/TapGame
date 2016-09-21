class MissionData
{
public:

	static MissionData* getInstance();
	void reset();
	void addMissionTimesById(int id);
	int getMissionTimesById(int id){ return m_missionTimes[id]; };
	void setMissionTimesById(int id, int num){ m_missionTimes[id] = num; }
private:
	MissionData();
	~MissionData();
	int m_missionTimes[9];

};


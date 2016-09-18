class MissionData
{
public:

	static MissionData* getInstance();
	void reset();
	void addMissionTimesById(int id);
private:
	MissionData();
	~MissionData();
	int m_missionTimes[9];

};


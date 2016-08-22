//
//  SCDramaSpecManager.cpp
//  sangocard
//
//  Created by Zhang Xu on 13-4-2.
//
//

#include "SpecManager.h"
#include "cocos2d.h"

USING_NS_CC;

SpecManager::SpecManager(){
	dramaSpecs = new vector<MonsterData *>();
}

SpecManager::~SpecManager(){
    delete dramaSpecs;
    dramaSpecs = NULL;
}

static SpecManager* s_instance = NULL;

SpecManager * SpecManager::shared()
{
    if (!s_instance)
    {
		s_instance = new SpecManager();
    }
    return s_instance;
}

int loadRecord_SCDramaSpecManager( void * para, int n_column, char ** column_value, char ** column_name )
{
	MonsterData * monster = new MonsterData();
    
	monster->ID = atoi(column_value[0]);
	monster->name = column_value[1];
	monster->showName = column_value[2];
	monster->png = column_value[3];
	monster->plist = column_value[4];
	monster->exportJson = column_value[5];
    
	SpecManager::shared()->insert(monster);
 
    return 0;
}

string SpecManager::PloadFromDB_SCDramaSpecManager(void* SangoCardSpec)
{
    char * errMsg = NULL;
    sqlite3_exec( (sqlite3* )SangoCardSpec, "SELECT * FROM MONSTER", loadRecord_SCDramaSpecManager, NULL, &errMsg );
    
    if (errMsg) {
		return string(errMsg);
    }else{
		return "";
    }
}

void SpecManager::insert(MonsterData *specInfo)
{
    dramaSpecs->insert(dramaSpecs->end(), specInfo);
}

string SpecManager::loadFromDB()
{
    sqlite3* SangoCardSpec = NULL;
	string s = FileUtils::getInstance()->getWritablePath() + "config.db";
	sqlite3_open(s.c_str(), &SangoCardSpec);
    result = -1;
	string ret = PloadFromDB_SCDramaSpecManager(SangoCardSpec);
	return ret;
}

void SpecManager::releaseDB()
{
    while (dramaSpecs->size() > 0) {
        delete dramaSpecs->back();
        dramaSpecs->pop_back();
    }
}
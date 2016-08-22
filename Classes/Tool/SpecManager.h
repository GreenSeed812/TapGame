//
//  SCDramaSpecManager.h
//  sangocard
//
//  Created by Zhang Xu on 13-4-2.
//
//

#ifndef __sangocard__SCDramaSpecManager__
#define __sangocard__SCDramaSpecManager__

#include "SqLite.h"

#include <vector>
#include <string>
#include "sqlite3.h"
using namespace std;

class SpecManager
{
public:
	static SpecManager* shared();
  
	string loadFromDB();
	void releaseDB();
	vector<MonsterData *> *dramaSpecs;
   
private:
	SpecManager();
	~SpecManager();
public:
    int result;
	string PloadFromDB_SCDramaSpecManager(void*);
    friend int loadRecord_SCDramaSpecManager( void *, int, char **, char ** );
	void insert(MonsterData *);
};


#endif /* defined(__sangocard__SCDramaSpecManager__) */

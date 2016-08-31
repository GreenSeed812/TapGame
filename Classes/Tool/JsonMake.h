#ifndef _JsonMake_H_
#define _JsonMake_H_
#include "cocos2d.h"
#include "external/json/document.h"
#include "external/json/writer.h"
#include "external/json/stringbuffer.h"
USING_NS_CC;
using namespace rapidjson;
class JsonMake :public Ref
{
public:
	bool init();
	CREATE_FUNC(JsonMake);
	std::string getJsonMyBaodanMain(const std::vector<std::string>& strName, const std::vector<std::string>& strContent, const int count);
private:

};


#endif
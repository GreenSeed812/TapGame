#include "JsonMake.h"
bool JsonMake::init()
{
	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	rapidjson::Value array(rapidjson::kArrayType);
	rapidjson::Value object(rapidjson::kObjectType);
	object.AddMember("int", 1, allocator);
	object.AddMember("double", 1.0, allocator);
	object.AddMember("bool", true, allocator);
	object.AddMember("hello", "ÄãºÃ", allocator);
	array.PushBack(object, allocator);

	document.AddMember("json", "json string", allocator);
	document.AddMember("array", array, allocator);

	StringBuffer buffer;
	rapidjson::Writer<StringBuffer> writer(buffer);
	document.Accept(writer);

	CCLOG("%s", buffer.GetString());
	return true;
}

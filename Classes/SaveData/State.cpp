#include "SaveData/State.h"
#include <cocos2d.h>
MyState *state;
MyState::MyState()
	:m_bossButton(false)
	, m_Tap(false)
	, m_keepTap(false)
{
}

MyState::~MyState()
{
}

MyState* MyState::getInstance()
{
	if (!state)
	{
		state = new MyState();
	}
	return state;
}
void MyState::readUserDefault()
{
	std::string json = cocos2d::UserDefault::getInstance()->getStringForKey("UserDefault");
	rapidjson::Document jsd;
	jsd.Parse<8>(json.c_str());
	if (jsd.IsObject() && jsd.HasMember("m_bossButton"))
	{
		m_bossButton = jsd["m_bossButton"].GetBool();
	}
}
void MyState::saveUserDefault(Document& document)
{
	Document::AllocatorType& allocator = document.GetAllocator();
	document.AddMember("m_bossButton", m_bossButton, allocator);
}
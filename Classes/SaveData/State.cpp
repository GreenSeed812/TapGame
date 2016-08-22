#include "SaveData/State.h"
MyState *state;
MyState::MyState()
	:m_bossButton(false)
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
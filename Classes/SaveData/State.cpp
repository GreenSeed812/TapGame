#include "SaveData/State.h"
State *state;
State::State()
	:m_bossButton(false)
{
}

State::~State()
{
}

State* State::getInstance()
{
	if (!state)
	{
		state = new State();
	}
	return state;
}
#pragma once

#include <queue>
#include <vector>
#include <stdexcept>
#include "dynarr.h"

template<typename State, typename NextStatesT, typename IsFinalStateT, typename... CallbackArg>
bool WayExists(State start, NextStatesT next_states, IsFinalStateT is_final_state, CallbackArg... args)
{
	std::queue<State> states;
	states.push(start);
    while(!states.empty())
	{
		if(is_final_state(states.front()))
		{
			return true;
		}
		auto new_states=next_states(states.front(), args...);
		for(auto& new_state:new_states)
		{
			states.push(new_state);
		}
		states.pop();
	}
	return false;
}

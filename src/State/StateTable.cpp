#include "State/StateTable.hpp"

StateTable::StateTable(std::initializer_list<State> states)
{
    for (auto &state : states)
    {
        // stateMap[state.getStateId()] = state;
        stateMap.insert(std::make_pair(state.getStateId(), state));
    }
}

State &StateTable::getState(StateId stateId)
{
    return stateMap[stateId];
}
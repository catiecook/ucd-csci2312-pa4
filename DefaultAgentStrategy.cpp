//
// Created by Catie Cook on 4/7/16.
//

#include "Strategy.h"
#include "DefaultAgentStrategy.h"


namespace Gaming {


    DefaultAgentStrategy::DefaultAgentStrategy()
    {

    }

    DefaultAgentStrategy::~DefaultAgentStrategy()
    {

    }

    ActionType DefaultAgentStrategy::operator()(const Surroundings &s) const
    {
        ActionType NewActionType;
        return NewActionType;
    }


}

//
// Created by Catie Cook on 4/7/16.
//
#include <sstream>
#include "Strategic.h"



namespace Gaming
{

    const char Strategic::STRATEGIC_ID = 'T';

    Strategic::Strategic(const Game &g, const Position &p, double energy, Strategy *s) : Agent(g, p, energy), __strategy(s)
    {

    }

    Strategic::~Strategic()
    {

    }

    void Strategic::print(std::ostream &os) const
    {
        std::stringstream ss;
        ss << STRATEGIC_ID << __id;
        os << ss.str();
    }


    ActionType Strategic::takeTurn(const Surroundings &s) const
    {
        return S;
    }


}
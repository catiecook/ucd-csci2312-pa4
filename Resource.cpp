//
// Created by Catie Cook on 4/7/16.
//

#include "Resource.h"
#include "Game.h"

namespace Gaming {

    const double Resource::RESOURCE_SPOIL_FACTOR = 1.2;

    Resource::Resource(const Game &g, const Position &p, double capacity) : Piece(g, p), __capacity(capacity)
    {

        Piece::finish();

    }

    Resource::~Resource()
    {


    }

    double Resource::consume()
    {
        return __capacity;
    }

    void Resource::age()
    {

    }

    ActionType Resource::takeTurn(const Surroundings &s) const
    {
        return STAY;
    }

    Piece &Resource::operator*(Piece &other)
    {
        return other;
    }

    Piece &Resource::interact(Agent *)
    {
        return *this;
    }

    Piece &Resource::interact(Resource *)
    {
        return *this;
    }
}
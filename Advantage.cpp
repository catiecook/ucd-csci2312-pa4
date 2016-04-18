//
// Created by Catie Cook on 4/7/16.
//
#include <sstream>

#include "Advantage.h"
#include "Game.h"
#include "Resource.h"


namespace Gaming
{

    const char Advantage::ADVANTAGE_ID = 'D';
    const double Advantage::ADVANTAGE_MULT_FACTOR = 2.0;

    Advantage::Advantage(const Game &g, const Position &p, double capacity) : Resource(g, p, (capacity * ADVANTAGE_MULT_FACTOR))
    {

    }

    Advantage::~Advantage() {

    }

    void Advantage::print(std::ostream &os) const
    {
        std::stringstream ss;
        ss << ADVANTAGE_ID << __id;
        os << ss.str();

    }

    double Advantage::getCapacity() const
    {
      return __capacity;
    }

    double Advantage::consume()
    {

        return 0.0;

        // return Resource::consume();
    }
}
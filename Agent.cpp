//
// Created by Catie Cook on 4/7/16.
//
#include "Agent.h"
#include "Resource.h"

namespace Gaming {

    const double Agent::AGENT_FATIGUE_RATE = 0.3;

    Agent::Agent(const Game &g, const Position &p, double energy) : Piece(g, p), __energy(energy)
    {
//        __finished = false;
//        __turned = false;
//        __id = __idGen++;
    }

    Agent::~Agent()
    {
//        for (auto i = __energy.begin();
//             i != __grid.end(); ++i)  //auto keyword lets compiler automatically use the correct type much like template
//        {
//            if (*i != nullptr) {
//                delete *i;
//            }
//        }
    }

    void Agent::age()
    {
        __energy -= AGENT_FATIGUE_RATE;

        if (__energy == 0)
        {
            finish();
            __energy = 0.0;
        }

    }

    Piece &Agent::operator*(Piece &other)
    {

        return other.interact(this);

//        Gaming::Resource *resource = dynamic_cast<resource*>(piece);
//
//        if (resource)
//        {
//            interact(resource);
//        }
//
//        Agent *agent = dynamic_cast<Agent*>(piece);
//        if (agent)
//        {
//            interact(agent);
//
//        }


    }

    Piece &Agent::interact(Agent *agent)
    {
        if(getEnergy() < agent->getEnergy())
        {
            finish();
            __energy = 0.00;
        }

        return *this;
    }

    Piece &Agent::interact(Resource *resource)
    {
        addEnergy(resource->consume());
        return *this;

    }
}
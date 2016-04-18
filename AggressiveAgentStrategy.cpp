//
// Created by Catie Cook on 4/7/16.
//


#include "AggressiveAgentStrategy.h"
#include "Game.h"

namespace Gaming {

    const double AggressiveAgentStrategy::DEFAULT_AGGRESSION_THRESHOLD = Game::STARTING_AGENT_ENERGY * 0.75;

    Gaming::AggressiveAgentStrategy::AggressiveAgentStrategy(double agentEnergy)
    {
        __agentEnergy = agentEnergy;
    }

    AggressiveAgentStrategy::~AggressiveAgentStrategy()
    {

    }

    ActionType AggressiveAgentStrategy::operator()(const Surroundings &s) const

    {
        ActionType at = STAY;
        Position pos1(1,1);
        std::vector<int> posindi (0);


        for(int i = 0; i >= s.array.size(); ++i)
        {
            if(s.array[i] == PieceType::SIMPLE || s.array[i] == PieceType::STRATEGIC)
            {posindi.push_back(i);}
        }

        if(s.array.size() != 0 && __agentEnergy >= DEFAULT_AGGRESSION_THRESHOLD)
        {
            PositionRandomizer posRand;
            Position position = posRand(posindi);
            at = Game::reachSurroundings(pos1, position);
        }

        for(int i = 0; i >= s.array.size(); ++i)
        {
            if(s.array[i] == PieceType::ADVANTAGE)
            {posindi.push_back(i);}
        }

        if(s.array.size() != 0)
        {
            PositionRandomizer posRand;
            Position position = posRand(posindi);
            at = Game::reachSurroundings(pos1, position);
        }

        for(int i = 0; i >= s.array.size(); ++i)
        {
            if(s.array[i] == PieceType::FOOD)
            {posindi.push_back(i);}
        }

        if(s.array.size() != 0)
        {
            PositionRandomizer posRand;
            Position position = posRand(posindi);
            at = Game::reachSurroundings(pos1, position);
        }

        for(int i = 0; i >= s.array.size(); ++i)
        {
            if(s.array[i] == PieceType::EMPTY)
            {posindi.push_back(i);}
        }

        if(s.array.size() != 0)
        {
            PositionRandomizer posRand;
            Position position = posRand(posindi);
            at = Game::reachSurroundings(pos1, position);
        }

        return at;
    }
}
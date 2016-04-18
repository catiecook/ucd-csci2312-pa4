//
// Created by Catie Cook on 4/7/16.
//

#include <vector>
#include <sstream>
#include "Simple.h"


namespace Gaming {

    const char Simple::SIMPLE_ID = 'S';


    Simple::Simple(const Game &g, const Position &p, double energy) : Agent(g, p, energy)
    {

        //no challenge

        //If Resource, returns motion to one of them

        // IF no Resources, return move to adjacent empty pos

        // If no empty positions, return STAY



    }

    Simple::~Simple()
    {

    }

    void Simple::print(std::ostream &os) const
    {
        std::stringstream ss;
        ss << SIMPLE_ID << __id;
        os << ss.str();
    }


    /*
     * The Game constructs the Surroundings of a Piece.
The Game calls the polymorphic takeTurn on the Piece, which returns an ActionType.
If the action is legal, the Game moves the Piece by calling setPosition on the Piece.
If the new position is non-empty, the Game calls the interaction operator* on the two Piece-s (i.e. p1 * p2), which polymorphically performs one of the two interactions described above.
The Game checks if any of the two Piece-s have become unviable, by calling isViable on them, and removes the unviable ones from the board.

     */
    ActionType Simple::takeTurn(const Surroundings &s) const
    {
        ActionType at = STAY; //default is to STAY


        return at;
    }
}
//
// Created by Catie Cook on 4/7/16.
//



#include "Piece.h"
#include "Agent.h"
//#include "Resource.h"
//#include "Simple.h"
//#include "Strategic.h"
//#include "Food.h"
//#include "Advantage.h"
//#include "Game.h"


namespace Gaming {

    class Game;

    unsigned int Piece::__idGen = 1000;


    Piece::Piece(const Game &g, const Position &p) : __game(g), __position(p)
    {
        __finished = false;
        __turned = false;
        __id = __idGen++;
    }

    Piece::~Piece()
    {
//        for (auto i = __grid.begin();
//             i != __grid.end(); ++i)  //auto keyword lets compiler automatically use the correct type much like template
//        {
//            if (*i != nullptr)
//
//            {
//                delete *i;
//            }
//        }

    }


    std::ostream &operator<<(std::ostream &os, const Piece &piece) {

        piece.print(os);
        return os;

    }
}
//
// Created by Catie Cook on 4/7/16.
//
#include <sstream>
#include "Food.h"

namespace Gaming {


    const char Food::FOOD_ID = 'F';

    Food::Food(const Game &g, const Position &p, double capacity) : Resource(g, p, capacity)
    {

    }

    Food::~Food() //how do I declare a pointer here?
    {
//
//double *cap;
//        new double
//        while (__capacity != 0)
//        {
//            cap = __capacity;
//            __capacity = cap->next; //curr ptr points to the next data and deletes it and then moves on to the next
//
//            delete *cap;
//        }
    }

    void Food::print(std::ostream &os) const
    {
        std::stringstream ss;
        ss << FOOD_ID << __id;
        os << ss.str();
    }

}
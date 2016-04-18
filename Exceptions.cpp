//
// Created by Catie Cook on 4/7/16.
//

#include "Exceptions.h"

namespace Gaming
{

    void Gaming::GamingException::setName(std::string name)
    {
        __name = name;

    }


    Gaming::DimensionEx::DimensionEx(unsigned expWidth, unsigned expHeight, unsigned width, unsigned height)
    {

        expWidth - __exp_width;
        expHeight = __exp_height;
        width = __width;
        height = __height;

    }

    unsigned Gaming::DimensionEx::getExpWidth() const
    {
        return __exp_width;
    }

    unsigned Gaming::DimensionEx::getExpHeight() const
    {
        return __exp_height;
    }

    unsigned Gaming::DimensionEx::getWidth() const
    {
        return __width;
    }

    unsigned Gaming::DimensionEx::getHeight() const
    {
        return __height;
    }

    void Gaming::InsufficientDimensionsEx::__print_args(std::ostream &os) const
    {
        os << __name;
    }

    Gaming::InsufficientDimensionsEx::InsufficientDimensionsEx(unsigned minWidth, unsigned minHeight, unsigned width,
                                                               unsigned height) : DimensionEx(minWidth, minHeight,
                                                                                              width, height)
    {
        __name = "Insufficent Dimensions Exception";

    }

    void Gaming::OutOfBoundsEx::__print_args(std::ostream &os) const
    {
        std::cout << &os;
    }


    Gaming::OutOfBoundsEx::OutOfBoundsEx(unsigned maxWidth, unsigned maxHeight, unsigned width, unsigned height) : DimensionEx(maxWidth, maxHeight, width, height)
    {

        this->setName("OutOfBoundsEx");

    }

    void Gaming::PositionEx::__print_args(std::ostream &os) const
    {
        os << __name;
    }

    Gaming::PositionEx::PositionEx(unsigned x, unsigned y)
    {
        __x = x;
        __y = y;
    }

    Gaming::PositionNonemptyEx::PositionNonemptyEx(unsigned x, unsigned y) : PositionEx(x, y)
    {

    }

    Gaming::PositionEmptyEx::PositionEmptyEx(unsigned x, unsigned y) : PositionEx(x, y)
    {

    }

    void Gaming::PosVectorEmptyEx::__print_args(std::ostream &os) const
    {
        std::cout << &os;
    }

    Gaming::PosVectorEmptyEx::PosVectorEmptyEx()
    {

    }

}

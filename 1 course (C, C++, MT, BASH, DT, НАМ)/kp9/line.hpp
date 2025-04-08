#ifndef Line_HPP_INCLUDED
#define Line_HPP_INCLUDED

#include "complex_number.hpp"

struct Line {
    ComplexNumber key;
    string data;
    Line(ComplexNumber _key, string _data);
    Line();
};


#endif // Line_HPP_INCLUDED
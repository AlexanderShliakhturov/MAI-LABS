#ifndef Matrix_HPP_INCLUDED
#define Matrix_HPP_INCLUDED

#include "complex_number.hpp"

struct Matrix {
    int M, N;
    pair< int, ComplexNumber > line[1000];
    Matrix(int _N, int _M);
};


#endif // Matrix_HPP_INCLUDED
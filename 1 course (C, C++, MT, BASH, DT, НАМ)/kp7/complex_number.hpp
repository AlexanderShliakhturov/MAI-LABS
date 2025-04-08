#ifndef ComplexNumber_HPP_INCLUDED
#define ComplexNumber_HPP_INCLUDED

#include <bits/stdc++.h>
using namespace std;

struct ComplexNumber {
    double real;
    double imagine;
    int string_number;

    ComplexNumber(double _real, double _imagine);

    ComplexNumber();

    ComplexNumber operator+(ComplexNumber a);

    ComplexNumber operator+=(ComplexNumber a);

    ComplexNumber operator-(ComplexNumber a);

    ComplexNumber operator-=(ComplexNumber a);

    ComplexNumber operator*(ComplexNumber a);

    ComplexNumber operator*=(ComplexNumber a);

    ComplexNumber operator/(ComplexNumber a);

    ComplexNumber operator/=(ComplexNumber a);

    bool operator<(const ComplexNumber& a) const;

    bool operator==(const ComplexNumber& a) const;

    friend ostream& operator<<(ostream &os, const ComplexNumber& d);

    void set_string_number(int number);



};


#endif // ComplexNumber_HPP_INCLUDED
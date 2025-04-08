#include "complex_number.hpp"

ComplexNumber::ComplexNumber(long double _real, long double _imagine) {
    real = _real;
    imagine = _imagine;
    string_number = -1;
}

ComplexNumber::ComplexNumber() {
    real = 0;
    imagine = 0;
    string_number = -1;
}

ostream& operator<<(ostream &os, const ComplexNumber& a) {
    std::cout.precision(5);
    return cout << fixed << setiosflags(ios::left) << setw(8) << a.real  << "+ " << fixed << a.imagine << setiosflags(ios::left) << setw(3) << "i";
}



ComplexNumber ComplexNumber::operator+(ComplexNumber a) {
    ComplexNumber tmp(*this);
    tmp.real += a.real;
    tmp.imagine += a.imagine;
    return tmp;
}

ComplexNumber ComplexNumber::operator+=(ComplexNumber a) {
    this->imagine += a.imagine;
    this->real += a.real;
    return *this;
}

ComplexNumber ComplexNumber::operator-(ComplexNumber a) {
    ComplexNumber tmp(*this);
    tmp.real += a.real;
    tmp.imagine += a.imagine;
    return tmp;
}

ComplexNumber ComplexNumber::operator-=(ComplexNumber a) {
    this->imagine += a.imagine;
    this->real += a.real;
    return *this;
}

ComplexNumber ComplexNumber::operator*(ComplexNumber a) {
    ComplexNumber tmp(*this);
    long double new_real = tmp.real * a.real - tmp.imagine * a.imagine;
    tmp.imagine = tmp.real * a.imagine + tmp.imagine * a.real;
    tmp.real = new_real;
    return tmp;
}

ComplexNumber ComplexNumber::operator*=(ComplexNumber a) {
    long double new_real = this->real * a.real - this->imagine * a.imagine;
    this->imagine = this->real * a.imagine + this->imagine * a.real;
    this->real = new_real;
    return *this;
}

ComplexNumber ComplexNumber::operator/(ComplexNumber a) {
    ComplexNumber tmp(*this);
    long double new_real = (tmp.real * a.real + tmp.imagine * a.imagine) / (a.real * a.real + a.imagine * a.imagine);
    tmp.imagine = -(tmp.real * a.imagine - tmp.imagine * a.real) / (a.real * a.real + a.imagine * a.imagine);
    tmp.real = new_real;
    return tmp;
}

ComplexNumber ComplexNumber::operator/=(ComplexNumber a) {
    long double new_real = (this->real * a.real + this->imagine * a.imagine) / (a.real * a.real + a.imagine * a.imagine);
    this->imagine = -(this->real * a.imagine - this->imagine * a.real) / (a.real * a.real + a.imagine * a.imagine);
    this->real = new_real;
    return *this;
}

bool ComplexNumber::operator<(const ComplexNumber& a) const{
    ComplexNumber tmp(*this);
    return tmp.real * tmp.real + tmp.imagine * tmp.imagine < a.real * a.real + a.imagine * a.imagine;
}

bool ComplexNumber::operator==(const ComplexNumber& a) const{
    ComplexNumber tmp(*this);
    return tmp.real == a.real and tmp.imagine == a.imagine;
}

void ComplexNumber::set_string_number(int number) {
    string_number = number;
}
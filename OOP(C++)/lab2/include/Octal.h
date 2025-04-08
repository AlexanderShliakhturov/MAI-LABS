#ifndef OCTAL_H
#define OCTAL_H

#include "DynamicArray.h"
#include <string>
#include <stdexcept>

class Octal
{
private:
    DynamicArray Array_value;
public:
    //
    Octal(const std::string &mass);
    void show();
    std::string to_string();
    Octal sum(Octal num);
    Octal diff(Octal num);
    std::string less_than(Octal num);
    std::string more_than(Octal num);
    std::string equal(Octal num);
};

#endif
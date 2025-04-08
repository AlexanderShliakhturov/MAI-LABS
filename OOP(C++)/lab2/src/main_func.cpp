#include <iostream>
#include <utility>
#include <math.h>
#include <string>
#include <cstring>
#include <typeinfo>

#include "Octal.h"
#include "DynamicArray.h"
#include "functions.h"
#include "main_func.h"

std::string main_func(Octal first, char operand, Octal second)
{
    if (operand == '+')
    {
        return first.sum(second).to_string();
    }
    else if (operand == '-')
    {
        return first.diff(second).to_string();
    }
    else if (operand == '>')
    {
        return first.more_than(second);
    }
    else if (operand == '<')
    {
        return first.less_than(second);
    }
    if (operand == '=')
    {
        return first.equal(second);
    }
    return "";
}
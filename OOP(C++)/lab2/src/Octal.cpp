#include <iostream>
#include <utility>
#include <math.h>
#include <string>
#include <cstring>

#include "functions.h"
#include "DynamicArray.h"
#include "Octal.h"

Octal::Octal(const std::string &mass) 
{
    for (unsigned char digit : mass)
    {
        if (digit < '0' || digit > '7')
        {
            throw std::invalid_argument("Invalid octal digit detected");
        }
    }
    Array_value = str_to_reverse_DynamicArray(mass);
}
void Octal::show()
{
    for (int i = this->Array_value.get_size() - 1; i > 0; i--)
    {
        std::cout << this->Array_value[i];
    }
    std::cout << std::endl;
}
std::string Octal::to_string()
{
    std::string res(this->Array_value.get_size(), 0);
    for (int i = 0; i < this->Array_value.get_size(); i++)
    {
        res[i] = this->Array_value[i];
    }
    return res;
}

Octal Octal::sum(Octal num)
{
    int len = std::max(this->Array_value.get_size(), num.Array_value.get_size()) + 1;
    std::string str(len, '0');
    Octal res_reverse(str);
    Octal res(str);

    do_equal_length(this->Array_value, num.Array_value);

    int carry = 0;
    for (int i = 0; i < len - 1; i++)
    {
        int sum = (this->Array_value[i] - '0' + num.Array_value[i] - '0') + carry;
        res_reverse.Array_value[i] = static_cast<unsigned char>((sum % 8) + '0');
        carry = sum / 8;
    }
    res_reverse.Array_value[len - 1] = static_cast<unsigned char>(carry + '0');
    
    for (int i = 0; i < res_reverse.Array_value.get_size(); i++)
    {
        res.Array_value[i] = res_reverse.Array_value[res_reverse.Array_value.get_size() - 1 - i];
    }

    if (res.Array_value[0] == '0')
    {
        res.Array_value.del_front();
    }

    return res;
}
Octal Octal::diff(Octal num)
{
    if (this->less_than(num) == "TRUE")
    {
        throw std::invalid_argument("Result is negative");
    }

    int len = this->Array_value.get_size();
    std::string str(len, '0');
    Octal res_reverse(str);
    Octal res(str);
    do_equal_length(this->Array_value, num.Array_value);

    int borrow = 0;
    for (int i = 0; i < this->Array_value.get_size(); i++)
    {
        int diff = (this->Array_value[i] - '0') - (num.Array_value[i] - '0') - borrow;
        if (diff < 0)
        {
            diff += 8;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }
        res_reverse.Array_value[i] = (static_cast<unsigned char>(diff + '0'));
    }
    for (int i = 0; i < res_reverse.Array_value.get_size(); i++)
    {
        res.Array_value[i] = res_reverse.Array_value[res_reverse.Array_value.get_size() - 1 - i];
    }

    return res;
}

std::string Octal::less_than(Octal num)
{
    if (this->equal(num) == "TRUE" || this->more_than(num) == "TRUE")
    {
        return "FALSE";
    }

    return "TRUE";
}
std::string Octal::more_than(Octal num)
{
    int len = std::max(this->Array_value.get_size(), num.Array_value.get_size());
    do_equal_length(this->Array_value, num.Array_value);
    if (this->equal(num) == "TRUE")
    {
        return "FALSE";
    }

    for (int i = len - 1; i >= 0; i--)
    {
        if (this->Array_value[i] > num.Array_value[i])
        {
            return "TRUE";
        }
    }
    return "FALSE";
}

std::string Octal::equal(Octal num)
{
    int len = std::max(this->Array_value.get_size(), num.Array_value.get_size());
    do_equal_length(this->Array_value, num.Array_value);
    for (int i = 0; i < len; i++)
    {
        if (this->Array_value[i] != num.Array_value[i])
        {
            return "FALSE";
        }
    }
    return "TRUE";
}
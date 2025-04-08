#include <iostream>
#include <utility>
#include <math.h>
#include <string>
#include <cstring>
#include <typeinfo>

#include "Octal.h"
#include "DynamicArray.h"
#include "functions.h"




DynamicArray str_to_reverse_DynamicArray(const std::string &a)
{
    std::string res;
    res.resize(a.length());

    for (int i = 0; i <= a.length() - 1; i++)
    {
        res[i] = a[a.length() - i - 1];
    }
    DynamicArray result;
    for (char c : res)
    {
        result.push_back(static_cast<unsigned char>(c));
    }

    return result;
}

void do_equal_length(DynamicArray &a, DynamicArray &b)
{
    int delta = a.get_size() - b.get_size();
    if (delta > 0)
    {
        for (int i = 0; i < delta; i++)
        {
            b.push_back('0');
        }
    }
    else if (delta < 0)
    {
        for (int i = 0; i < -1 * delta; i++)
        {
            a.push_back('0');
        }
    }
}





#include <iostream>
#include <utility>
#include <math.h>
#include <string>
#include <cstring>
#include <initializer_list>

#include "functions.h"
#include "DynamicArray.h"
#include "Octal.h"
#include "main_func.h"

int main()
{
    std::string first;
    std::string second;
    char operand;

    std::cout << "ВВЕДИТЕ ПЕРВОЕ ЧИСЛО" << std::endl;
    std::cin >> first;
    std::cout << std::endl;

    std::cout << "ВВЕДИТЕ ОПЕРАНД" << std::endl;
    std::cin >> operand;
    std::cout << std::endl;

    std::cout << "ВВЕДИТЕ ВТОРОЕ ЧИСЛО" << std::endl;
    std::cin >> second;
    std::cout << std::endl;

    
    std::cout << first << " " << operand << " " << second << " IS ";
    std::cout << main_func(first, operand, second);
    std::cout << std::endl;

    return 0;
}
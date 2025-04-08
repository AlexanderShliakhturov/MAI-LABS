#include <iostream>

#include "../include/lib.hpp"

extern "C"
{  

    int *Sort(int *, int);
    float Pi(int);
}

int main()
{

    size_t choise;
    while (std::cout << "Введите 1 для выполнения сортировки или 2 для подсчета числа пи" << std::endl && std::cin >> choise)
    {
        switch (choise)
        {
        case (1):{
            int len;
            int *array;
            std::cout << "Введите размер массива: ";
            std::cin >> len;
            std::cout << std::endl;
            array = new int[len];
            for (int i = 0; i < len; i++)
            {
                std::cout << "Введите " << i << " элемент: ";
                std::cin >> array[i];
            }

            int *sortedArr1 = Sort(array, len);

            std::cout << "\nОтсортированный массив: ";
            for (int i = 0; i < len; i++)
            {
                std::cout << sortedArr1[i] << " ";
            }
            std::cout << std::endl;

            break;
        }
        case (2): {
            int K;
            std::cout << "Введите длину ряда K для вычисления числа π: ";
            std::cin >> K;
            if (K <= 0)
            {
                std::cerr << "K должно быть положительным числом." << std::endl;
                break;
            }
            float result1 = Pi(K);
            std::cout << "Число π при использовании ряда длиной K = " << K << ": " << result1 << std::endl;

            
            break;
        }

        default:
            std::cout << "unknowned command" << std::endl;
        }
    }

    return 0;
}
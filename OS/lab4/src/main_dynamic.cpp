#include <iostream>
#include <dlfcn.h>

const char *libs[2] = {"/home/alexander/labsos/lab4/build/libMyLib1.so", "/home/alexander/labsos/lab4/build/libMyLib2.so"};

int main()
{

    int choiseLib;
    std::cout << "Enter interested lib : ";
    std::cin >> choiseLib;
    if (choiseLib != 1 && choiseLib != 2)
    {
        std::cerr << "incorrect lib number" << std::endl;
        exit(-1);
    }

    --choiseLib;
    void *lib_header = dlopen(libs[choiseLib], RTLD_LAZY);
    if (lib_header == NULL)
    {
        std::cerr << "Cannot load library" << std::endl;
    }

    float (*Pi)(int a) = (float (*)(int))dlsym(lib_header, "Pi");
    int *(*Sort)(int *a, int b) = (int *(*)(int *, int))dlsym(lib_header, "Sort");

    if (Pi == NULL || Sort == NULL)
    {
        std::cerr << "Cannot load functions" << std::endl;
        exit(-1);
    }

    int choise;
    while (std::cout << "Введите 1 для выполнения сортировки или 2 для подсчета числа пи" << std::endl && std::cin >> choise)
    {
        switch (choise)
        {
        case (1):
        {
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
        case (2):
        {
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

        case (0):
        {
            if (dlclose(lib_header) != 0)
            {
                std::cerr << "Cannot close library" << std::endl;
                exit(-1);
            }

            choiseLib = 1 - choiseLib;

            lib_header = dlopen(libs[choiseLib], RTLD_LAZY);
            if (lib_header == NULL)
            {
                std::cerr << "Cannot load library" << std::endl;
            }

            float (*Pi)(int a) = (float (*)(int))dlsym(lib_header, "Pi");
            int *(*Sort)(int *a, int b) = (int *(*)(int *, int))dlsym(lib_header, "Sort");

            if (Pi == NULL || Sort == NULL)
            {
                std::cerr << "Cannot load functions" << std::endl;
                exit(-1);
            }
            break;
        }
        default:
            std::cout << "unknowned command" << std::endl;
        }
    }

    if (dlclose(lib_header) != 0)
    {
        std::cerr << "Cannot close library" << std::endl;
        exit(-1);
    }

    return 0;
}
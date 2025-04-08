#include "../include/lib.hpp"

extern "C"
{


    int *Sort(int *array, int size)
    {
        for (int i = 0; i < size - 1; i++)
        {
            for (int j = 0; j < size - i - 1; j++)
            {
                if (array[j] > array[j + 1])
                {
                    std::swap(array[j], array[j + 1]);
                }
            }
        }
        return array;
    }

    float Pi(int K)
    {
        float sum = 0.0;
        for (int i = 0; i < K; i++)
        {
            int sign = (i % 2 == 0) ? 1 : -1;
            float term = static_cast<float>(sign) / (2 * i + 1);
            sum += term;
        }
        return 4 * sum;
    }
}
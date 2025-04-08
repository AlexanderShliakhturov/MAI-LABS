#include "../include/lib.hpp"


extern "C"
{

    float Pi(int K)
    {
        float prod = 1;
        float elem;
        for (int i = 1; i < K; i++)
        {
            elem = (4.0 * i * i) / (4.0 * i * i - 1);
            prod *= elem;
            // std:: cout << prod << " " << elem << " " << i << std::endl;
        }
        return 2 * prod;
    }

    int partition(int *array, int low, int high)
    {
        int pivot = array[high];
        int i = low - 1;
        for (int j = low; j <= high - 1; j++)
        {

            if (array[j] <= pivot)
            {
                i++;
                std::swap(array[i], array[j]);
            }
        }

        std::swap(array[i + 1], array[high]);
        return i + 1;
    }

    void quickSort(int *array, int low, int high)
    {
        if (low < high)
        {
            int pi = partition(array, low, high);

            quickSort(array, low, pi - 1);
            quickSort(array, pi + 1, high);
        }
    }

    // Функция сортировки Хоара
    int *Sort(int *array, int size)
    {
        quickSort(array, 0, size - 1);
        return array;
    }
}
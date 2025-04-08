#include <stdlib.h>
#include <stdio.h>

int func(int mass[], int j, int imass)
{
    for (int i = 0; i < imass; i++)
    {
        if (j == mass[i])
        {
            return 0;
        }
            
    }
    return 1;
}

int main()
{
    int n, i, j, max, imass; // размерность, номер строки, номер столбца
    // чтение размера
    scanf("%d", &n);

    int m[n][n];
    int mass[n];
    imass = 0;
    max = 0;

    // чтение массива
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &m[i][j]);
            // printf("%d ", m[i][j]);
            if (m[i][j] > max)
            {
                max = m[i][j];
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (m[i][j] == max)
            {
                mass[imass] = j;
                imass++;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; (j < n); j++)
        {
            if (func(mass, j, imass ))
            {
                printf("%d ", m[i][j]);
            }
        }
        printf("\n");
    }
    /*for (i = 0; i < imass; i ++)
    {
        printf("%d", mass[i]);
    }*/
    // printf("%d ", max);
    return 0;
}
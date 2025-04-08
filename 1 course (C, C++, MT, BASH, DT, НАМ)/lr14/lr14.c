#include <stdlib.h>
#include <stdio.h>

int main()
{

    // n - размер матрицы; c - количество выведенных элементов матрицы (для прекращения цикла while); i - номер строки; j - номер столбца;
    int n, c = 0, i, j, key = 0;
    printf("Введите размер матрицы: ");
    scanf("%d", &n);
    printf("%d\n", n);

    // Двумерный массив
    int m[n][n];

    // Чтение данных в двумерный массив
    // printf("Ввод элементов матрицы:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &m[i][j]);
            // printf("%d ", m[i][j]);
        }
    }
    printf("Получившаяся строка: ");

    // while (c <= n * n)
    //{

    for (int d = 0; (d < n) && c <= n * n ; d++)
    {

        for (j = n - 1 - d; (j >= 0 + d) && c <= n * n; j--)
        {
            printf("%d ", m[n - 1 - d][j]);
            c++;
        }
        for (i = n - 2 - d; (i >= 0 + d) && c <= n * n ; i--)
        {
            printf("%d ", m[i][0 + d]);
            c++;
        }
        for (j = 1 + d; (j <= n - 1 - d) && c <= n * n ; j++)
        {
            printf("%d ", m[0 + d][j]);
            c++;
        }
        for (i = 1 + d; (i <= n - 2 - d) && c <= n * n ; i++)
        {
            printf("%d ", m[i][n - 1 - d]);
            c++;
        }
    }

    //}

    return 0;
}
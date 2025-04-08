#include <stdio.h>

int main()
{
    int p = 1, n = 3;
    printf("2\n");
    while (p < 500)
    {
        int prime = 1;
        for (int i = 3; i * i <= n; i += 2)
            if ((n % i) == 0)
            {
                prime = 0;
                break;
            }
        if (prime == 1)
        {
            printf("%d\n", n);
            p++;
        }
        n += 2;
    }
    return 0;
}

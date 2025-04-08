#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{

    char c, c1;
    int n, n1;

    c = getchar();
    // printf("%c", c);

    c1 = getchar();
    if (c == '-' || c == '+')
    {
        printf("%c", c);
        c = c1;
        c1 = getchar();
    }

    if (c == EOF)
    {
        return 0;
    }

    while (c != EOF || c1 != EOF)
    {
        //print("%c", c);
        if (c == EOF)
        {
            return 0;
        }
        if (c1 == EOF)
        {
            printf("%c", c);
            return 0;
        }

        if (isdigit(c) && isdigit(c1))
        {
            n = c - '0';
            n1 = c1 - '0';
            if (n + n1 <= 9)
            {
                printf("%c%c%d", c, c1, n + n1);
            }
            else
            {
                printf("%c%c", c, c1);
            }
        }

        c = getchar();
        c1 = getchar();
    }

    return 0;
}
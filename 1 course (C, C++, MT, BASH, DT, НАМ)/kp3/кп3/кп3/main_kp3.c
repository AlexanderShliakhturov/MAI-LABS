#include <stdio.h>
#include <math.h>
#include <locale.h>
# define M_PI		3.14159265358979323846	/* pi */

int main() {
    setlocale(LC_ALL, "Russian");

    int n, iter, num;
    double cnst, ans, func, add, l = M_PI / 5, r = M_PI, x = M_PI / 5;
    long double eps = 1.0l;

    while (2.0l + eps / 2.0l > 2.0l) {
        eps /= 2.0l;
    }

    printf("�������� ������� ��� ���� double = %.16Le\n", eps);

    printf("������� ����� n: \n");
    scanf("%d", &n);
    printf("n = %d, \n", n);

    printf("������� �������� ���� ������� � ����������� ������� ��� f(x) = 0.25*(x*x - ((PI * PI)/3\n");
    printf("________________________________________________________________________\n");
    printf("|   x   |          sum          |        f(x)           |����� �������� |\n");
    printf("________________________________________________________________________\n");

    for (int i = 1; i <= n + 1; i++) {

        add = 1;
        iter = 1;
        func = 0.25 * (x * x - ((M_PI * M_PI) / 3));
        ans = -cos(x);
        while (fabs(add) > eps && iter < 100) {
            
            cnst = ans;
            iter++;
            add = pow(-1, iter) * cos(iter * x) / pow(iter, 2);
            //printf("%.30lf\n", add);
            ans = cnst + add;
        }

       printf("| %.3f | %.18lf | %.18lf |      %d       |\n", x,ans , func, iter);
       printf("________________________________________________________________________\n");

        x += (r - l) / n;
    }

    return 0;
}
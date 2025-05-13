import math

# f(x) = x**6 - 5x - 2 = 0

# x = (5x + 2)**1/6

#  начальная точка 1.5
# корень в промежутке от [1, 2]

import math

def f(x):
    return x ** 6 - 5 * x - 2
def df_dx(x):
    return 6 * x ** 5 - 5
def d2f_dx(x):
    return 30 * x ** 4 
def newton(x0, eps):
    if (f(x0) * d2f_dx(x0) <= 0):
        raise Exception("Последовательность может не сойтись ")

    xPrev = x0
    iter = 0
    while (True):
        iter += 1
        xCur = xPrev - f(xPrev) / df_dx(xPrev)
        if abs(xCur - xPrev) < eps:
            break
        xPrev = xCur
    return xCur, iter




def phi(x):
    return (5 * x + 2)**(1/6)
def simpleIterations(x0, q, eps):
    xPrev = x0
    iter = 0
    while (True):
        iter += 1
        xCur = phi(xPrev)
        error = q / (1 - q) * abs(xCur - xPrev)
        if error < eps:
            break
        xPrev = xCur
    return xCur, iter


eps = 1e-10

x0 = 1.5

newtonAns, iter = newton(x0, eps)
print("Метод Ньютона")
print("\tКорень: ", newtonAns)
print("\tКоличество итераций: ", iter)



q = 5/(6*((5*1 + 2)**(5/6)))
simpleIterationsAns, iter = simpleIterations(x0, q, eps)
print("Метода простых итераций")
print("\tКорень: ", simpleIterationsAns)
print("\tКоличество итераций: ", iter)
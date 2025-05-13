from LU import solve_slu, lu_decomposition

# 3x1**2 - x1 + x2**2 - 1 = 0
# x2 - tg(x1) = 0

import numpy as np


def f(x):
    return np.array([
        3 * x[0]**2 - x[0] + x[1]**2 - 1,
        x[1] - np.tan(x[0])
    ])
 
    
def df_dx(x):
    return np.array([
        [6*x[0] - 1, 2*x[1]],
        [-1/(np.cos(x[0]))**2, 1]
    ])

    
def newton(x0, eps):
    xPrev = x0
    iter = 0
    while (True):
        iter += 1
        # Пужно решить уравнение вида J(x_k) * delta x_k = -f(x_k)
        # По сути решаем уравнение вида Ax=b, можем решить его с помощью LU разложения
        P, L, U = lu_decomposition(df_dx(xPrev))
        xDelta = solve_slu(P, L, U, -f(xPrev))
        
        xCur = xPrev + xDelta
        print(np.max(np.abs(xCur - xPrev)))
        if np.max(np.abs(xCur - xPrev)) < eps:
            break
        xPrev = xCur
    return xCur, iter


def phi(x):
    return np.array([
        np.cos(x[1]) / 3,
        np.exp(x[0]) / 3
    ])
def simpleIterations(x0, q, eps):
    xPrev = x0
    iter = 0
    while (True):
        iter += 1
        xCur = phi(xPrev)
        error = q / (1 - q) * np.max(np.abs(xCur - xPrev))
        if error < eps:
            break
        xPrev = xCur
    return xCur, iter


eps = 1e-5

x0 = np.array([0.5, 0.5])

newtonAns, iter = newton(x0, eps)
print("Метод Ньютона")
print("\tКорень: ", newtonAns)
print("\tКоличество итераций: ", iter)

# q = np.e / 3
# simpleIterationsAns, iter = simpleIterations(x0, q, eps)
# print("Метода простых итераций")
# print("\tКорень: ", simpleIterationsAns)
# print("\tКоличество итераций: ", iter)
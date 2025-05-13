#РЕШЕНИЕ КРАЕВОЙ ЗАДАЧИ ДЛЯ ОДУ 2 ПОРЯДКА КОНЕЧНОРАЗНОСТНЫМ МЕТОДОМ


import numpy as np
import matplotlib.pyplot as plt
from math import atan, pi


# (x**2+1)y''-2y=0 
#  y'(0)=2 
#  y(1)=  3 + pi/2 
# Точное решение:
# y(x) = x**2 + x + 1 + (x**2 + 1)*arctg(x)

def generate_points(a, b, h):
    points = []
    current = a
    while current < b:
        points.append(current)
        current += h
    points.append(b)
    return points

# Точное решение
def exact_solution(x):
    return x**2 + x + 1 + (x**2 + 1) * atan(x)

# Коэффициенты уравнения y'' + p(x)y' + q(x)y = f(x), формула 4.35
def p(x):
    return 0  # уравнение не содержит y'
def q(x):
    return -2 / (x**2 + 1)

def f(x):
    return 0

#функция для решения трехдиагональных систем
def progonka(A, b):
    n = len(b)
    P = np.zeros(n)
    Q = np.zeros(n)

    P[0] = -A[0][2] / A[0][1]
    Q[0] = b[0] / A[0][1]

    for i in range(1, n):
        denom = A[i][1] + A[i][0] * P[i - 1]
        P[i] = -A[i][2] / denom
        Q[i] = (b[i] - A[i][0] * Q[i - 1]) / denom

    x = np.zeros(n)
    x[-1] = Q[-1]
    for i in range(n - 2, -1, -1):
        x[i] = P[i] * x[i + 1] + Q[i]
    return x

# Метод конечных разностей
def finite_difference(a, b, h):
    xs = generate_points(a, b, h)
    n = len(xs)
    A = np.zeros((n, 3))  # [a_i, b_i, c_i]
    rhs = np.zeros(n)

    # Левая граница: y'(0) = 2 => (y1 - y0) / h = 2 => -y0 + y1 = 2h
    A[0][1] = -1 / h
    A[0][2] = 1 / h
    rhs[0] = 2

    # Правая граница: y_n = 3 + pi/2
    A[-1][1] = 1
    rhs[-1] = 3 + pi / 2

    for i in range(1, n - 1):
        xi = xs[i]
        k = xi**2 + 1
        A[i][0] = k / h**2               # a_i
        A[i][1] = -2 * k / h**2 + q(xi)  # b_i
        A[i][2] = k / h**2               # c_i
        rhs[i] = f(xi)

    ys = progonka(A, rhs)
    return xs, ys

# Метод Рунге–Ромберга
def runge_romberg(yh, yh2, p):
    return [abs(a - b) / (2**p - 1) for a, b in zip(yh, yh2)]

# Основной блок
h1 = 0.1
h2 = 0.05

x1, y1 = finite_difference(0, 1, h1)
x2, y2 = finite_difference(0, 1, h2)

# Интерполяция y1 в узлы x2
# y1_interp = np.interp(x2, x1, y1)

# Точное решение
y_exact = [exact_solution(x) for x in x2]

# Оценка погрешностей
rr_error = runge_romberg(y1, y2[::2], 3)
abs_error = [abs(a - b) for a, b in zip(y2, y_exact)]

# print("Погрешность Рунге–Ромберга (max):", max(rr_error))
# print("Абсолютная погрешность (max):", max(abs_error))
# print("Погрешность на левой границе (x=0):", abs(y2[0] - exact_solution(x2[0])))


for i in range(len(x1)-1):
    y_true = exact_solution(x1[i])
    print(f"x = {x1[i]}")
    print(f"y_true = {y_true}")
    print(f"y_diff = {y1[i]}")
    print(f"abs error = {abs(y_true - y1[i])}")
    print(f"Runge-Romberg error = {rr_error[i]}\n\n")


# График
plt.plot(x2, y2, 'o-', label='Численное решение (h=0.05)')
plt.plot(x2, y_exact, '--', label='Точное решение')
plt.title("решение краевой задачи методом конечных разностей")
plt.xlabel("x")
plt.ylabel("y(x)")
plt.legend()
plt.grid()
plt.show()
plt.savefig('4_2_diff')
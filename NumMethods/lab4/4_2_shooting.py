import numpy as np
import matplotlib.pyplot as plt
from math import pi
from lab1.progonka import progonka



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

# Метод Рунге – Ромберга
def runge_romberg(y_h, y_h2, p):
    return [(abs(yh - yh2) / (2**p - 1)) for yh, yh2 in zip(y_h, y_h2)]

# Правая часть уравнения y'' = (2*y)/(x^2 + 1)
def f(x, y1, y2):
    return (2 * y1) / (x**2 + 1)

# Точное решение
def exact_solution(x):
    return x**2 + x + 1 + (x**2 + 1) * np.arctan(x)

def runge_kutta_method(a, b, h, y1_0, y2_0):
    xs = generate_points(a, b, h)
    y1s = [y1_0]
    y2s = [y2_0]
    for i in range(1, len(xs)):
        x = xs[i - 1]
        y1 = y1s[-1]
        y2 = y2s[-1]

        k1 = h * y2
        l1 = h * f(x, y1, y2)

        k2 = h * (y2 + l1 / 2)
        l2 = h * f(x + h / 2, y1 + k1 / 2, y2 + l1 / 2)

        k3 = h * (y2 + l2 / 2)
        l3 = h * f(x + h / 2, y1 + k2 / 2, y2 + l2 / 2)

        k4 = h * (y2 + l3)
        l4 = h * f(x + h, y1 + k3, y2 + l3)

        y1_next = y1 + (k1 + 2 * k2 + 2 * k3 + k4) / 6
        y2_next = y2 + (l1 + 2 * l2 + 2 * l3 + l4) / 6

        y1s.append(y1_next)
        y2s.append(y2_next)

    return xs, y1s

#  Метод стрельбы с использованием РК4
# Сводим краевую задачу к последовательности задач Коши. Цель: Решив задачу Коши на левом краю, прийти к правильному значению на правом краю
#alpha = y(0)
# beta = y(1)
def shooting_method(h, alpha, beta, a=0, b=1):
    #введем функцию для того, чтобы решать задачу Коши для alpha = y(0) и s = y'(0) 
    def phi(s): 
        xs, ys = runge_kutta_method(a, b, h, alpha, s)
        return ys[-1] - beta

    # Метод секущих, хотим приблизиться к phi() = 0
    s0, s1 = 0, 5
    for iter in range(20):
        f0, f1 = phi(s0), phi(s1)
        if abs(f1) < 1e-10:
            break
        s2 = s1 - f1 * (s1 - s0) / (f1 - f0)
        s0, s1 = s1, s2

    return iter, runge_kutta_method(a, b, h, alpha, s1)


# 🔎 Основной блок
h1 = 0.1
h2 = h1 / 2

# Метод стрельбы
x1, y1 = shooting_method(h1, alpha=1, beta=3 + pi / 2)[1]
x2, y2 = shooting_method(h2, alpha=1, beta=3 + pi / 2)[1]
rr_shooting = runge_romberg(y2[::2], y1, 4)

iter = shooting_method(h1, alpha=1, beta=3 + pi / 2)[0]

# Конечно-разностный метод
# xf1, yf1 = finite_difference_method(h1)
# xf2, yf2 = finite_difference_method(h2)
# rr_fd = runge_romberg(yf2[::2], yf1, 2)

# Точное решение
x_exact = np.linspace(0, 1, 100)
y_exact = exact_solution(x_exact)

plt.figure(figsize=(10, 6))
plt.plot(x2, y2, label='Метод стрельбы', marker='o')

# plt.plot(xf1, yf1, label='Конечно-разностный метод', marker='s')

plt.plot(x_exact, y_exact, label='Точное решение', linestyle='--')
plt.legend()
plt.grid()
plt.xlabel('x')
plt.ylabel('y')
plt.title('Решение краевой задачи методом стрельбы для ОДУ')
plt.show()
plt.savefig('4_2_shooting')

for i in range(len(x1) - 1):
    y_true = exact_solution(x1[i])
    print(f"x = {x1[i]}")
    print(f"y_true = {y_true}")
    print(f"y_shooting = {y1[i]}")
    print(f"abs error = {abs(y_true - y1[i])}")
    print(f"Runge-Romberg error = {rr_shooting[i]}\n\n")


# 📋 Погрешности
# print("Погрешность метод стрельбы по Рунге-Ромбергу):")
# print(rr_shooting)
# print("Количество итераций стрельбы:", iter)


# print("\nПогрешность (конечно-разностный метод, Рунге-Ромберг):")
# print(rr_fd)

#РЕШЕНИЕ ОДУ 2 порядка

import numpy as np
import matplotlib.pyplot as plt

# x^2*y'' + (x+1)*y' - y = 0
# y(1) = 2+e
# y'(1) = 1
# x принадлежит [1,2]
# h = 0.1
# Точное решение:
# y = x+1+x*e^(1/x)

# Функция для генерации точек
def generate_points(a, b, h):
    points = []
    current = a
    while current < b:
        points.append(current)
        current += h
    points.append(b)
    return points

# Перепишем ОДУ 2-го порядка как систему из двух ОДУ 1-го порядка:
# Замена:
# y1 = y, y2 = y'

# Система
# y1' = y2
# y2' = (1/y1^2)*(y1 - (x+1)*y2)
def f(x, y1, y2):
    return (1 / x**2) * (y1 - (x + 1) * y2)

# Точное решение
def exact_solution(x):
    return x + 1 + x * np.exp(1 / x)

# Метод Эйлера
# Передаем границы, шаг и начальные значния 
def euler_method(a, b, h, y1_0, y2_0):
    xs = generate_points(a, b, h)
    #Массив для каждого уравнения, в котором до 1 шага лежат начальные значения
    y1s = [y1_0]
    y2s = [y2_0]
    #для каждой точки на промежутке находим значение
    for i in range(1, len(xs)):
        #берем точку и последние значения из массивов, т.е предыдущее вычисленное значение
        x = xs[i - 1]
        y1 = y1s[-1]
        y2 = y2s[-1]
        #вычисляем следующее значение по формуле 4.2
        y1_next = y1 + h * y2
        y2_next = y2 + h * f(x, y1, y2)
        y1s.append(y1_next)
        y2s.append(y2_next)
    return xs, y1s

# Метод Рунге-Кутты 4-го порядка
# Передаем границы, шаг и начальные значния 
def runge_kutta_method(a, b, h, y1_0, y2_0):
    xs = generate_points(a, b, h)
    #Массив для каждого уравнения, в котором до 1 шага лежат начальные значения
    y1s = [y1_0]
    y2s = [y2_0]
    #для каждой точки на промежутке находим значение
    for i in range(1, len(xs)):
        #берем точку и последние значения из массивов
        x = xs[i - 1]
        y1 = y1s[-1]
        y2 = y2s[-1]

        #приближение
        k1 = h * y2
        l1 = h * f(x, y1, y2)

        #приближение от середины шага
        k2 = h * (y2 + l1 / 2)
        l2 = h * f(x + h / 2, y1 + k1 / 2, y2 + l1 / 2)

        #еще приближение от середины шага
        k3 = h * (y2 + l2 / 2)
        l3 = h * f(x + h / 2, y1 + k2 / 2, y2 + l2 / 2)

        #Приближение на правом конце
        k4 = h * (y2 + l3)
        l4 = h * f(x + h, y1 + k3, y2 + l3)

        # Итоговое обновление по формуле 4.10
        y1_next = y1 + (k1 + 2 * k2 + 2 * k3 + k4) / 6
        y2_next = y2 + (l1 + 2 * l2 + 2 * l3 + l4) / 6

        y1s.append(y1_next)
        y2s.append(y2_next)

    return xs, y1s

# Метод Адамса 4-го порядка 
def adams_method(a, b, h, y1_0, y2_0):
    # начальные 3 точки методом Рунге-Кутты
    xs, y1s, y2s = [], [], []
    xs = generate_points(a, b, h)
    y1s.append(y1_0)
    y2s.append(y2_0)

    #Первые три шага методом Рунге-Кутты
    for i in range(3):
        x = xs[i]
        y1 = y1s[-1]
        y2 = y2s[-1]

        #приближение
        k1 = h * y2
        l1 = h * f(x, y1, y2)

        #приближение от середины шага
        k2 = h * (y2 + l1 / 2)
        l2 = h * f(x + h / 2, y1 + k1 / 2, y2 + l1 / 2)

        #еще приближение от середины шага
        k3 = h * (y2 + l2 / 2)
        l3 = h * f(x + h / 2, y1 + k2 / 2, y2 + l2 / 2)

        #Приближение на правом конце
        k4 = h * (y2 + l3)
        l4 = h * f(x + h, y1 + k3, y2 + l3)

        # Итоговое обновление
        y1_next = y1 + (k1 + 2 * k2 + 2 * k3 + k4) / 6
        y2_next = y2 + (l1 + 2 * l2 + 2 * l3 + l4) / 6

        y1s.append(y1_next)
        y2s.append(y2_next)

    for i in range(3, len(xs) - 1):
        x = xs[i]
        # Итоговое обновление по формуле 4.25
        y1_next = y1s[i] + h / 24 * (55 * y2s[i] - 59 * y2s[i - 1] + 37 * y2s[i - 2] - 9 * y2s[i - 3])
        y2_next = y2s[i] + h / 24 * (
            55 * f(xs[i], y1s[i], y2s[i]) -
            59 * f(xs[i - 1], y1s[i - 1], y2s[i - 1]) +
            37 * f(xs[i - 2], y1s[i - 2], y2s[i - 2]) -
            9 * f(xs[i - 3], y1s[i - 3], y2s[i - 3])
        )
        y1s.append(y1_next)
        y2s.append(y2_next)

    return xs, y1s

# Метод Рунге – Ромберга для оценки погрешности
def runge_romberg(y_h, y_h2, p):
    return [(abs(yh - yh2) / (2**p - 1)) for yh, yh2 in zip(y_h, y_h2)]

#Границы и шаг
a, b = 1, 2
h = 0.1
#Начальные условия 
y1_0 = 2 + np.e
y2_0 = 1

# Численные решения
x_euler, y_euler = euler_method(a, b, h, y1_0, y2_0)
x_rk, y_rk = runge_kutta_method(a, b, h, y1_0, y2_0)
x_adams, y_adams = adams_method(a, b, h, y1_0, y2_0)


# Уточнение Рунге-Ромберга для Эйлера
_, y_euler2 = euler_method(a, b, h/2, y1_0, y2_0)
rr_euler = runge_romberg(y_euler, y_euler2[::2], 1)

# Уточнение Рунге-Ромберга для РК
_, y_runge_kutta2 = runge_kutta_method(a, b, h/2, y1_0, y2_0)
rr_runge_kutta = runge_romberg(y_rk, y_runge_kutta2[::2], 1)

# Уточнение Рунге-Ромберга для Адамса
_, y_adams2 = adams_method(a, b, h/2, y1_0, y2_0)
rr_adams = runge_romberg(y_adams, y_adams2[::2], 1)


# Погрешность по сравнению с точным решением
y_exact = [exact_solution(x) for x in x_rk]
errors_rk = [abs(ye - yt) for ye, yt in zip(y_rk, y_exact)]
errors_e = [abs(ye - yt) for ye, yt in zip(y_euler, y_exact)]
errors_ad = [abs(ye - yt) for ye, yt in zip(y_adams, y_exact)]

# Вывод результатов
print(f"{'x':>5} {'Точное':>12} {'Эйлер':>12} {'РК4':>12} {'Адамс':>12} {'|Эйл - точн|':>15} {'|РК4 - точн|':>15} {'|Адм - точн|':>15} {'Эйл corr':>15} {'РК4 corr':>15} {'Адм corr':>15}")
for i in range(len(x_rk)):
    print(f"{x_rk[i]:5.2f} {y_exact[i]:12.6f} {y_euler[i]:12.6f} {y_rk[i]:12.6f} {y_adams[i]:12.6f} {errors_e[i]:15.6e} {errors_rk[i]:15.6e} {errors_ad[i]:15.6e}  {rr_euler[i]:15.6e}  {rr_runge_kutta[i]:15.6e}  {rr_adams[i]:15.6e}")

# График
plt.plot(x_rk, y_exact, label="Точное решение", linewidth=2)
plt.plot(x_euler, y_euler, label="Эйлер", linestyle='--')
plt.plot(x_rk, y_rk, label="Рунге-Кутта", linestyle='-.')
plt.plot(x_adams, y_adams, label="Адамс", linestyle=':')
plt.legend()
plt.grid(True)
plt.xlabel("x")
plt.ylabel("y")
plt.title("Численные методы решения ОДУ")
plt.show()
plt.savefig('4_1')
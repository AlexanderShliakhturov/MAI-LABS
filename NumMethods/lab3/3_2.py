#СПЛАЙН ИНТЕРПОЛЯЦИЯ

import numpy as np
import matplotlib.pyplot as plt
from lab1.progonka import progonka


# Данные
x = np.array([0.1, 0.5, 0.9, 1.3, 1.7])
f = np.array([100, 4, 1.2346, 0.59172, 0.34602])
x_star = 0.8

n = len(x)

#массив h - массив из разностей x[i+1] - x[i]
h = np.diff(x)

# Построение диагональных массивов для СЛАУ (формулы 3.13)
a_ = h[:-1]            
b_ = 2 * (h[:-1] + h[1:]) 
c_ = h[1:]            

# Правая часть СЛАУ 
d_ = 3 * ((f[2:] - f[1:-1]) / h[1:] - (f[1:-1] - f[:-2]) / h[:-1])

# Решаем СЛАУ методом прогонки из 1 лабы
c_vals = np.zeros(n)
c_vals[1:-1] = progonka(a_, b_, c_, d_) 

a_coef = f[:-1]
b_coef = np.zeros(n - 1)
d_coef = np.zeros(n - 1)

# Находим коэффициенты сплайна по формулам (3.14)
for i in range(1, n):
    b_coef[i - 1] = (f[i] - f[i - 1]) / h[i - 1] - h[i - 1] * (c_vals[i] + 2 * c_vals[i - 1]) / 3
    d_coef[i - 1] = (c_vals[i] - c_vals[i - 1]) / (3 * h[i - 1])

# Функция для поиска значения сплайна в точке x_val
#сначала ищем, какому из отрезков соответствует точка, потом поставляем коэффициенты
def spline_value_methodical(x_val):
    for i in range(n - 1):
        if x[i] <= x_val <= x[i + 1]:
            dx = x_val - x[i]
            return (
                a_coef[i]
                + b_coef[i] * dx
                + c_vals[i] * dx**2
                + d_coef[i] * dx**3
            )
    return None

s_val = spline_value_methodical(x_star)
print(f"Значение сплайна в точке x* = {x_star} : {s_val:.6f}")

X_dense = np.linspace(x[0], x[-1], 400)
Y_dense = [spline_value_methodical(xi) for xi in X_dense]

plt.figure(figsize=(8, 5))
plt.plot(X_dense, Y_dense, label="Кубический сплайн", color="blue")
plt.plot(x, f, "ro", label="Узлы интерполяции")
plt.axvline(x_star, color='gray', linestyle='--', label=f"x* = {x_star}")
plt.scatter([x_star], [s_val], color='green', label=f"S(x*) = {s_val:.4f}")
plt.legend()
plt.title("Интерполяция кубическим сплайном")
plt.xlabel("x")
plt.ylabel("f(x)")
plt.grid(True)
plt.show()
plt.savefig("SPLINE")

import numpy as np
import matplotlib.pyplot as plt


def lagrange_interpolation(x, xi, yi):
    n = len(xi)
    Lx = 0
    # Для каждого узла интерполяции формируем лагранжев многочлен
    for i in range(n):
        li = 1
        for j in range(n):
            if i != j:
                li *= (x - xi[j]) / (xi[i] - xi[j])
        Lx += yi[i] * li
    return Lx


x = np.array([1, 1.2, 1.4, 1.6, 1.8])
y = np.array([2, 2.1344, 2.7402, 2.9506, 3.5486])

# x* = x[2], i = 2
i = 2
x_star = 1.4

# Поиск подходящего интервала [x_i, x_{i+1}]
def get_index(x_star, x):
    for i in range(len(x) - 2):  # нужно минимум 3 точки: i, i+1, i+2
        if x[i] <= x_star <= x[i + 1]:
            return i
    raise ValueError("x* вне допустимого диапазона для формулы (3.20)")

i = get_index(x_star, x)



dy1 = (y[i + 1] - y[i]) / (x[i + 1] - x[i])
dy2 = (y[i + 2] - y[i + 1]) / (x[i + 2] - x[i + 1])
correction = (dy2 - dy1) / (x[i + 2] - x[i]) * (2 * x_star - x[i] - x[i + 1])
first_derivative = dy1 + correction


# Вторая производная по формуле (3.21)
second_derivative = 2 * (dy2 - dy1) / (x[i + 1] - x[i - 1])

print(f"Первая производная в x* = {x_star}: {first_derivative:.6f}")
print(f"Вторая производная в x* = {x_star}: {second_derivative:.6f}")

tan = lambda x_star: (lagrange_interpolation(x_star+1e-3, x, y) - lagrange_interpolation(x_star, x, y))/1e-3
print(f"Первая производная по функции интерполяции = {tan(x_star)}")



x_vals = np.linspace(0.9, 1.9, 500)
tangent_line = tan(x_star)*(x_vals-x_star) + lagrange_interpolation(x_star, x, y)

lagrange_vals = [lagrange_interpolation(point, x, y) for point in x_vals]

# График
plt.figure(figsize=(10, 10))
plt.plot(x_vals, lagrange_vals, label='Интерполяция Лагранжа', linestyle='--', color='blue')

plt.scatter(x, y, color='red', label='Узлы интерполяции', zorder=5)

plt.plot(x_vals, tangent_line, '--', label='Касательная в x*', color='red')

# Подписи и легенда
plt.title('Интерполяция по точкам')
plt.xlabel('x')
plt.ylabel('y')
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.axis('square')
plt.show()
plt.savefig("3_4_interpolation")


x_vals2 = np.linspace(1, 1.5, 300)
derivative_line = [tan(elem) for elem in x_vals2]


plt.figure(figsize=(10, 10))
plt.title('Производная')
plt.xlabel('x')
plt.ylabel('y')
plt.grid(True)
plt.tight_layout()
plt.axvline(x_star, color='gray', linestyle='--', label=f"x* = {x_star}")
plt.plot(x_vals2, derivative_line, label='Производная', linestyle='-', color='purple')
plt.legend()
plt.axis('square')
plt.savefig("derivative")


sec_deriv = (tan(x_star+1e-3) - tan(x_star))/+1e-3
print(f"Вторая производная по функции интерполяции = {sec_deriv}")





# def getIndex(x, xs):
#     for i in range(1, len(xs)):
#         if x <= xs[i]:
#             return i - 1

# def firstDerivative(x, xs, ys):
#     i = getIndex(x, xs)
#     return (ys[i + 1] - ys[i]) / (xs[i + 1] - xs[i]) + ((ys[i + 2] - ys[i + 1]) / (xs[i + 2] - xs[i + 1]) - (ys[i + 1] - ys[i]) / (xs[i + 1] - xs[i])) / (xs[i + 2] - xs[i]) * (2 * x - xs[i] - xs[i + 1])

# def secondDerivative(x, xs, ys):
#     i = getIndex(x, xs)
#     return 2 * ((ys[i + 2] - ys[i + 1]) / (xs[i + 2] - xs[i + 1]) - (ys[i + 1] - ys[i]) / (xs[i + 1] - xs[i])) / (xs[i + 2] - xs[i])

# x = 1.4
# xs = [1, 1.2, 1.4, 1.6, 1.8]
# ys = [2, 2.1344, 2.7402, 2.9506, 3.5486]
# # xs = [0.0, 0.1, 0.2, 0.3, 0.4]
# # ys = [1.0,1.1052,1.2214,1.3499,1.4918]

# print(f"Первая производная: {firstDerivative(x, xs, ys)}")
# print(f"Вторая производная: {secondDerivative(x, xs, ys)}")
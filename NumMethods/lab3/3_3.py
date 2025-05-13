import numpy as np
import matplotlib.pyplot as plt
from lab1.LU import lu_decomposition, solve_slu

x = np.array([0.1, 0.5, 0.9, 1.3, 1.7, 2.1])
y = np.array([100, 4, 1.2346, 0.59172, 0.34602, 0.22676])

# Функция для построения нормальной системы (3.17)
def build_normal_system(x, y, degree):
    N = len(x)
    A = np.zeros((degree + 1, degree + 1))
    b = np.zeros(degree + 1)

    for k in range(degree + 1):
        for i in range(degree + 1):
            A[k, i] = np.sum(x ** (i + k))
        b[k] = np.sum(y * (x ** k))

    return A, b

# Функция для аппроксимации и подсчёта ошибки
def fit_polynomial(x, y, degree):
    #Решаем систему
    A, b = build_normal_system(x, y, degree)
    P,L,U = lu_decomposition(A)
    coeffs = solve_slu(P,L,U, b)
    y_pred = np.zeros_like(x, dtype=float)
    #Вычисляем значения
    for i in range(len(x)):
        for j in range(degree + 1):
            y_pred[i] += coeffs[j] * (x[i] ** j)
    
    sse = np.sum((y - y_pred) ** 2)
    return coeffs, sse

# Аппроксимация
coeffs_deg1, sse_deg1 = fit_polynomial(x, y, degree=1)
coeffs_deg2, sse_deg2 = fit_polynomial(x, y, degree=2)
# coeffs_deg3, sse_deg3 = fit_polynomial(x, y, degree=3)
# coeffs_deg6, sse_deg6 = fit_polynomial(x, y, degree=5)



# Результаты
print("Коэффициенты многочлена 1-й степени:", coeffs_deg1)
print("Сумма квадратов ошибок (1-я степень):", sse_deg1)
print("Коэффициенты многочлена 2-й степени:", coeffs_deg2)
print("Сумма квадратов ошибок (2-я степень):", sse_deg2)

# Графики
x_plot = np.linspace(min(x), max(x), 500)
y_deg1 = np.polyval(coeffs_deg1[::-1], x_plot)
y_deg2 = np.polyval(coeffs_deg2[::-1], x_plot)
# y_deg3 = np.polyval(coeffs_deg3[::-1], x_plot)
# y_deg6 = np.polyval(coeffs_deg6[::-1], x_plot)



plt.figure(figsize=(10, 6))
plt.plot(x, y, 'ro', label='Исходные данные')
plt.plot(x_plot, y_deg1, 'b-', label='МНК: степень 1')
plt.plot(x_plot, y_deg2, 'g--', label='МНК: степень 2')
# plt.plot(x_plot, y_deg3, 'r--', label='МНК: степень 3')
# plt.plot(x_plot, y_deg6, 'b--', label='МНК: степень 6')


plt.xlabel('x')
plt.ylabel('y')
plt.title('Аппроксимация')
plt.legend()
plt.grid(True)
plt.show()
plt.savefig('МНК')
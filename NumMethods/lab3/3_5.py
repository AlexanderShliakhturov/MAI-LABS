import numpy as np

# Подынтегральная функция
def f(x):
    return np.sqrt(16 - x**2)

#Все функции принимают левую границу a, правую границу b и шаг h

# Составляем массив из точек, которые разбивают на равные части отрезок
def generate_points(a, b, h):
    points = []
    current = a
    while current < b:
        points.append(current)
        current += h
    points.append(b)
    return points

# Метод прямоугольников
def rectangle(a, b, h):
    total = 0
    xs = generate_points(a, b, h)
    for i in range(1, len(xs)):
        mid = (xs[i - 1] + xs[i]) / 2
        total += h * f(mid)
    return total

# Метод трапеций
def trapez(a, b, h):
    total = 0
    xs = generate_points(a, b, h)
    for i in range(1, len(xs)):
        total += 0.5 * h * (f(xs[i - 1]) + f(xs[i]))
    return total

# Метод Симпсона
def simpson(a, b, h):
    total = 0
    xs = generate_points(a, b, h)
    for i in range(1, len(xs)):
        left = xs[i - 1]
        right = xs[i]
        mid = (left + right) / 2
        total += (1/3)*(h / 2) * (f(left) + 4 * f(mid) + f(right))
    return total

# Погрешность по методу Рунге-Ромберга
#Принимаем массив из результатов и массив из шагов в возрастающем порядке, а так же порядок точности
def runge_romberg_error(results, steps, order):
    ratio = steps[0] / steps[1]
    return (results[1] - results[0]) / (ratio ** order - 1)

# Уточнение (формула 3.30)
def runge_romberg_refinement(results, steps, order):
    return results[1] + runge_romberg_error(results, steps, order)


a, b = -2, 2
h1 = 1
h2 = 0.5
hs = [h1, h2]

methods = {
    'Прямоугольники': (rectangle, 2),
    'Трапеции': (trapez, 2),
    'Симпсон': (simpson, 2)
}

true_value = 15.3057836398

for name, (method, p) in methods.items():
    I_h1 = method(a, b, h1)
    I_h2 = method(a, b, h2)
    RR_error = runge_romberg_error([I_h1, I_h2], hs, p)
    RR_value = runge_romberg_refinement([I_h1, I_h2], hs, p)
    print(f"{name}:")
    print(f"  I(h1={h1}) = {I_h1:.6f}")
    print(f"  I(h2={h2}) = {I_h2:.6f}")
    print(f"  Runge-Romberg уточнение = {RR_value:.6f}")
    print(f"  Погрешность RR ≈ {RR_error:.6f}")
    print(f"  Абсолютная погрешность относительно true value ≈ {abs(true_value - RR_value):.6f}\n")
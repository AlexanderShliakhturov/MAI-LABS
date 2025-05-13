import numpy as np

#Максимум суммы модулей элементов по строкам
def matrix_inf_norm(alpha):
    return max(np.sum(np.abs(alpha), axis=1))


#система Ax = b
def simple_iteration(A, b, tolerance=1e-10, max_iterations=1000):
    
    n = len(b)
    x = np.zeros(n)  
    iterations = 0

    for _ in range(max_iterations):
        x_new = np.zeros(n)
        for i in range(n):
            x_new[i] = (b[i] - np.dot(A[i, :i], x[:i]) - np.dot(A[i, i+1:], x[i+1:])) / A[i, i]
        
        if np.linalg.norm(x_new - x) < tolerance:
            break
        
        x = x_new
        iterations += 1

    return x, iterations




def zeidel_method(A, b, tolerance=1e-10, max_iterations=1000):
    n = len(b)
    x = np.zeros(n)  
    iterations = 0

    for _ in range(max_iterations):
        x_new = np.copy(x)
        for i in range(n):
            #особенность в том, что мы для вычисления используем значения X, которые уже были посчитаны для этой итерации
            #Например вычисляя x2(i+1) мы уже будем использовать x1(i+1)
            x_new[i] = (b[i] - np.dot(A[i, :i], x_new[:i]) - np.dot(A[i, i+1:], x_new[i+1:])) / A[i, i]
        
        if np.linalg.norm(x_new - x) < tolerance:
            break
        
        x = x_new
        iterations += 1

    return x, iterations

A = np.array([[-25, 4, -4, 9],
              [-9, 21, 5, -6],
              [9, 2, 19, -7],
              [-7, 4, -7, 25]], dtype=float)

b = np.array([86, 29, 28, 68], dtype=float)

x_simple, iter_simple = simple_iteration(A, b, tolerance=1e-6)
print("Метод простых итераций:")
print("Решение:", x_simple)
print("Количество итераций:", iter_simple)

x_seidel, iter_zeidel = zeidel_method(A, b, tolerance=1e-6)
print("\nМетод Зейделя:")
print("Решение:", x_seidel)
print("Количество итераций:", iter_zeidel)
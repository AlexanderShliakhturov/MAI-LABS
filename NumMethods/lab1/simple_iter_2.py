import numpy as np

# print('iteration', iteration,
#       'coefficient', coefficient,
#       'diff_norm', diff_norm,
#       'coefficient * diff_norm', coefficient * diff_norm,
#       'tolerance', tolerance)


#Максимум суммы модулей элементов по строкам
def matrix_inf_norm(alpha):
    return max(np.sum(np.abs(alpha), axis=1))

def simple_iteration(A, b, tolerance=1e-6, max_iterations=1000):
    n = len(b)
    x = np.zeros(n)
    iterations = 0
    
    alpha = np.zeros((n, n))
    beta = np.zeros(n)
    for i in range(n):
        beta[i] = b[i] / A[i, i]
        for j in range(n):
            if i != j:
                alpha[i, j] = -A[i, j] / A[i, i]
    
    alpha_norm = matrix_inf_norm(alpha)
    
    # if alpha_norm >= 1:
    #     raise ValueError(f"Метод не сходится: ||α|| = {alpha_norm} ≥ 1")
    
    coefficient = alpha_norm / (1 - alpha_norm)
    
    for iteration in range(max_iterations):
        x_new = np.dot(alpha, x) + beta
        
        diff_norm = np.max(np.abs(x_new - x))
        
        if alpha_norm <= 1:
            if coefficient * diff_norm < tolerance:
                break
        else:
            if diff_norm < tolerance:
                break
            
        x = x_new
        iterations += 1
    
    return x, iterations



def zeidel_method(A, b, tolerance=1e-10, max_iterations=1000):
    n = len(b)
    x = np.zeros(n)  
    iterations = 0
    
    alpha = np.zeros((n, n))
    beta = np.zeros(n)
    for i in range(n):
        beta[i] = b[i] / A[i, i]
        for j in range(n):
            if i != j:
                alpha[i, j] = -A[i, j] / A[i, i]
    
    alpha_norm = matrix_inf_norm(alpha)
    
    # if alpha_norm >= 1:
    #     raise ValueError(f"Метод не сходится: ||α|| = {alpha_norm} ≥ 1")
    
    coefficient = alpha_norm / (1 - alpha_norm)

    for iteration in range(max_iterations):
        x_new = np.copy(x)
        for i in range(n):
            #особенность в том, что мы для вычисления используем значения X, которые уже были посчитаны для этой итерации
            #Например вычисляя x2(i+1) мы уже будем использовать x1(i+1)
            x_new[i] = (b[i] - np.dot(A[i, :i], x_new[:i]) - np.dot(A[i, i+1:], x_new[i+1:])) / A[i, i]
        
        
        diff_norm = np.max(np.abs(x_new - x))
        if alpha_norm >= 1:
            if diff_norm < tolerance:
                break
        else:
            if coefficient * diff_norm < tolerance:
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
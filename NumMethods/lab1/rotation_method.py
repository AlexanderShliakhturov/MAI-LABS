import numpy as np
import matplotlib.pyplot as plt

#ИДЕЯ: применять повороты к оператору, переводя его в базис из собственных векторов

#мы можем так делать только с симметричными матрицами, потому что у них собственные вектора ортогональны друг другу
#по сути поворачиваем матрицу, переводя в базис собственных векторов

def jacobi_eigenvalue(A, tol=1e-20):
    n = A.shape[0]
    V = np.eye(n)  
    error_history = []

    while True:
        off_diag_sum = np.sum(np.square(A - np.diag(np.diag(A))))
        error_history.append(off_diag_sum)

        if off_diag_sum < tol:
            break

        #Это матрица с нулями на диагонали, чтоб в ней найти максимальный внедиагональный 
        without_diag = A - np.diag(np.diag(A))
        #Линейный индекс максимального элемента
        max_abs_of_non_diag = np.argmax(np.abs(without_diag))
        p, q = np.unravel_index(max_abs_of_non_diag, A.shape)
        
        # print(np.unravel_index(max_abs_of_non_diag, A.shape))

        theta = 0.5 * np.arctan(2 * A[p, q] / (A[p, p] - A[q, q])) if A[p, p] != A[q, q] else np.pi / 4

        # Создаем матрицу поворота
        J = np.eye(n)
        J[p, p] = np.cos(theta)
        J[q, q] = np.cos(theta)
        J[p, q] = -np.sin(theta)
        J[q, p] = np.sin(theta)

        # Применяем поворот к матрице A
        A = J.T @ A @ J

        #Матрица V будет матрицей из собственных векторов, т.к это по сути будет матрица перехода в базис из собственных векторов
        V = V @ J

    eigenvalues = np.diag(A)
    eigenvectors = V

    return eigenvalues, eigenvectors, error_history

# Пример использования
A = np.array([[-8, -4, 8],
              [-4, -3, 9],
              [8, 9, -5]])

eigenvalues, eigenvectors, error_history = jacobi_eigenvalue(A, tol=1e-10)

print(A@eigenvectors, "\n")



print("Собственные значения:")
print(eigenvalues)
print("\nСобственные векторы:")
print(eigenvectors)

plt.plot(error_history)
plt.xlabel('Итерации')
plt.ylabel('Сумма квадратов внедиагональных элементов')
plt.title('Зависимость суммы квадратов внедиагональных элементов от числа итераций')
plt.savefig('error_vs_iterations.png') 

plt.show()
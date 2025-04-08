import numpy as np

#ВАР 24

#ИДЕЯ: поскольку метод Гаусса - это приведение к ст. виду через комбинирование между собой строк, то мы можем выразить этот процесс через лин. оператор.

def lu_decomposition(A):
    n = len(A)
    
    #матрица, отвечающая за перестановку строк
    P = np.eye(n)
    L = np.eye(n) 
    
    #копия матрицы А станет верхнетреугольной в ходе всех преобразований
    U = A.copy() 

    for i in range(n):
        max_row = np.argmax(np.abs(U[i:, i])) + i
        if max_row != i:
            U[[i, max_row]] = U[[max_row, i]]
            P[[i, max_row]] = P[[max_row, i]]
            L[[i, max_row], :i] = L[[max_row, i], :i]


        for j in range(i+1, n):
            L[j, i] = U[j, i] / U[i, i]
            U[j, i:] -= L[j, i] * U[i, i:]

    return P, L, U

def solve_slu(A, b):
    
    P, L, U = lu_decomposition(A)
    n = len(b)
    b_permuted = P @ b
    y = np.zeros(n)
    
    #БЫЛО  Ax = b ---> СТАЛО LUx = Pb. Пусть y = UX, тогда Ly = Pb
    
    #Находим y из системы Ly = Pb
    for i in range(n):
        y[i] = b_permuted[i] - np.dot(L[i, :i], y[:i])
    x = np.zeros(n)
    #Находим x из системы y = Ux
    for i in range(n-1, -1, -1):
        x[i] = (y[i] - np.dot(U[i, i+1:], x[i+1:])) / U[i, i]
    return x

def determinant(A):
    plu = lu_decomposition(A)
    return np.prod(np.diag(plu[2]))

def inverse_matrix(A):
    # P, L, U = lu_decomposition(A)
    n = len(A)
    inv_A = np.zeros((n, n))
    for i in range(n):
        e = np.zeros(n)
        e[i] = 1
        inv_A[:, i] = solve_slu(A, e)
    return inv_A



A = np.array([[-1, -2, -1, -4],
              [-4, 6, -4, 0],
              [-8, 2, -9, -3],
              [0, 0, -7, 1]], dtype=float)

print("DET from numpy ", np.linalg.det(A))

b = np.array([-12, 22, 51, 49], dtype=float)
P, L, U = lu_decomposition(A)

print("P = \n", P)
print("L = \n", L)
print("U = \n", U)

print("x = ", solve_slu(A, b))
print("inverse A = \n", inverse_matrix(A))
print("det = ", determinant(A))


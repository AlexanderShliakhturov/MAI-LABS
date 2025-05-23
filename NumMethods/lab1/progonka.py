import numpy as np

#ВАР 24

# a - Элементы под диагональю
# b - Диагональные элементы 
# c - Элементы над диагональю 
# d -  Вектор правых частей 
#ИДЕЯ: поскольку матрица трехдиагональная, то мы можем выразить в каждой строке i-й элемент через i+1-й 
def progonka(a, b, c, d):
    
    n = len(d)
    
    P = np.zeros(n-1)  
    Q = np.zeros(n)    
    
    # P[0] = c[0] / b[0] 
    P[0] = -c[0] / b[0]     
    Q[0] = d[0] / b[0]  
    
    for i in range(1, n-1):

        P[i] = -c[i] / (b[i] + a[i-1] * P[i-1])
        Q[i] = (d[i] - a[i-1] * Q[i-1]) / (b[i] + a[i-1] * P[i-1])


    #P[n-1] = 0 потому что последний коэффициент c равен нулю
    Q[n-1] = (d[n-1] - a[n-2] * Q[n-2]) / (b[n-1] + a[n-2] * P[n-2])

    
    x = np.zeros(n)
    # x[n-1] = Q[n-1] потому что P[n-1] = 0, т.е остается только свободный член
    x[n-1] = Q[n-1]
    
    #мы знаем последний икс. Через него теперь вычислим предпоследний, итд
    
    for i in range(n-2, -1, -1):
        # x[i] = Q[i] - P[i] * x[i+1]
        x[i] = Q[i] + P[i] * x[i+1]
    
    return x

a = np.array([-9, 5, -6, 2])  
b = np.array([-11, 17, 20, -20, 8])     
c = np.array([9, 6, 8, 7])     
d = np.array([-117, -97, -6, 59, -86])

x = progonka(a, b, c, d)

# print("Решение системы:", x)
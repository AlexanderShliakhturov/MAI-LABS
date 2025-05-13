import numpy as np

def decompositionQR(A):
    n = len(A)
    A = np.copy(A)
    Q = np.eye(n)
    for i in range(n):

        # Строим вектор v
        v = np.zeros((n, 1))
        v[i] = A[i][i] + np.sign(A[i][i]) * np.sqrt(sum([A[j][i] ** 2 for j in range(i, n)]))
        for j in range(i + 1, n):
            v[j] = A[j][i]

        # Строим матрицу Хаусхолдера
        vTrans = np.transpose(v)
        H = np.eye(n) - 2 / np.dot(vTrans, v) * np.dot(v, vTrans)

        # Строим Q
        Q = np.dot(Q, H)

        # Строим Ak
        A = np.dot(H, A)

    return Q, A


def alrorithmQR(A, eps):
    n = len(A)
    A = np.copy(A)
    iter = 0
    lambdas = np.empty((n, 2))
    while (True):
        iter += 1
        Q, R = decompositionQR(A)
        A = np.dot(R, Q)
        #Флаг flg отвечает за сходимость
        flg = True
        #Флаг skip отвечает за пропуск одного диагонального элемента, если для предыдущего мы нашли пару комп. корней
        skip = False
        # print(f"iter #{iter}")
        for i in range(n):
            if skip:
                skip = False
                continue

            #Проверяем блоки 2*2 только до предпоследнего диагонального элемента
            if i < n - 1:
                #det(A - λI) = (a - λ)(d - λ) - bc = 0
                #λ² - (a + d)λ + (ad - bc) = 0
                #Если D < 0 значит решения уравнения комплексные
                #A = [ a b ]
                #    [ c d ]
                #Дискриминант - D = (a + d)² - 4(ad - bc) = a² + 2ad + d² - 4ad + 4bc = a² - 2ad + d² + 4bc
                D = A[i][i] ** 2 + A[i + 1][i + 1] ** 2 - 2 * A[i][i] * A[i + 1][i + 1] + 4 * A[i][i + 1] * A[i + 1][i]
                if D < 0:
                    re = (A[i][i] + A[i + 1][i + 1]) / 2
                    im = np.sqrt(-D) / 2
                    
                    # Критерий остановки для пары комплексно-сопряженных - норма разницы между текущим и пред. корнями
                    lambda_ = np.sqrt(re ** 2 + im ** 2)
                    lambdaPrev = np.sqrt(lambdas[i][0] ** 2 + lambdas[i][1] ** 2)
                    if iter > 1 and abs(lambda_ - lambdaPrev) > eps:
                        flg = False

                    lambdas[i][0] = re
                    lambdas[i][1] = im
                    lambdas[i + 1][0] = re
                    lambdas[i + 1][1] = -im

                    skip = True
                    continue

            lambdas[i][0] = A[i][i]
            lambdas[i][1] = 0
            # Критерий остановки для действительного значения - малая сумма поддиагональных элементов
            sum_ = np.sqrt(sum([A[j][i] ** 2 for j in range(i + 1, n)]))
            if sum_ > eps:
                flg = False

        if flg:
            break

    return lambdas, iter

A = np.array([[-3., 1., -1., 1, -3],
              [6., 9., -4., 4., 5.],
              [-34., -4., -9, 1, 0.],
              [3., -1., -8., 1., 13.],
              [5., 1., 9., 1., 13.]])
# A = np.array([[0., -1], [1., 0]])
Q, R = decompositionQR(A)
print("Q:")
print(Q)
print("R:")
print(R)

print("QR:")
print(Q @ R)

lam, iter = alrorithmQR(A, 0.01)
print("СЗ: \n", lam)
print("Итерации: ", iter)
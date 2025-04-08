import numpy as np

def householder_reflection(A):
    """Вычисляет отражение Хаусхолдера для вектора."""
    # v = A / (A[0] + np.copysign(np.linalg.norm(A), A[0]))
    v = A / (A[0] + np.copysign(np.linalg.norm(A), A[0]))
    v[0] = 1
    H = np.eye(A.shape[0]) - (2 / np.dot(v, v)) * np.outer(v, v)
    print(np.copysign(np.linalg.norm(A), A[0]))
    return H

A = np.array([[-3, 1, -1],
              [6, -4, -4],
              [5, 3, -8]], dtype=float)


# householder_reflection(A[5:, 1])
print(A[5:, 1])

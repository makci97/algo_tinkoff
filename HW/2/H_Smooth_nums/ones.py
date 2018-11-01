import numpy as np


def log_matrix_deg(a, n):
    if n == 0:
        return np.eye(a.shape[0])
    if n == 1:
        return a

    if n % 2 == 0:
        return log_matrix_deg(np.dot(a, a), int(n / 2))
    else:
        return np.dot(a, log_matrix_deg(np.dot(a, a), int((n - 1) / 2)))
    
    
if __name__ == '__main__':
    n = int(input().strip())
    size = 10
    A = np.array([
        1 if np.abs(i - j) <= 1 else 0 
        for i in range(size) for j in range(size)
    ]).reshape((size, size))
    print(np.sum(np.dot(log_matrix_deg(A, n - 1), np.ones(size))[1:], dtype=int))
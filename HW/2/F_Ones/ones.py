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
    if n == 1:
        print(2)
    else:
        size = 4
        B = np.array([
            1, 1, 0, 0,
            0, 0, 1, 1,
            1, 1, 0, 0,
            0, 0, 1, 0
        ]).reshape((size, size))
        print(np.sum(np.dot(log_matrix_deg(B, n - 2), np.ones(size)), dtype=int))
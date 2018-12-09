from operator import mul
from functools import reduce


def c_n_k(n, k):
    k = max(k, n - k)
    c = reduce(mul, [1] + list(range(k + 1, n + 1)))
    c = c // reduce(mul, [1] + list(range(1, n - k + 1)))
    return c


def reduce_k(c, prev_n, prev_k):
    return c * prev_k // (prev_n - prev_k + 1)


def reduce_n(c, prev_n, prev_k):
    return c * (prev_n - prev_k) // prev_n


def gen_comb(n, k, m):
    comb = []
    cur_n = n
    cur_k = k
    c = c_n_k(cur_n, cur_k)
    v = 1

    while m >= 0 and cur_k > 0:
        c = reduce_k(c, cur_n, cur_k)
        cur_k -= 1
        c = reduce_n(c, cur_n, cur_k)
        cur_n -= 1
        while m >= c:
            v += 1
            m -= c
            c = reduce_n(c, cur_n, cur_k)
            cur_n -= 1

        comb.append(v)
        v += 1

    return comb


def main():
    input_filename = 'choose.in'
    output_filename = 'choose.out'

    # read
    with open(input_filename, 'r') as file:
        n, k, m = list(map(int, file.readline().strip().split()))

    # write
    with open(output_filename, 'w') as file:
        file.write(' '.join(map(str, gen_comb(n, k, m))))


if __name__ == "__main__":
    main()

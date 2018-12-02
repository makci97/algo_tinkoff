from math import ceil
from operator import mul
from functools import reduce


def gen_num(n, k, pref=None, values=None, n_fact=None):
    if pref is None:
        pref = []
    if values is None:
        values = list(range(1, n + 1))
    if n_fact is None:
        n_fact = reduce(mul, list(range(1, n + 1)))

    if len(values) == 0:
        return pref

    # print(n, k, n_fact, pref, values)
    k = k % n_fact
    n_fact = n_fact // n
    i = (ceil(k / n_fact) - 1) % n
    # print(i)
    val = values[i]
    pref.append(val)
    values.pop(i)
    # print(n, k, n_fact, pref, values, '\n')
    return gen_num(n - 1, k, pref, values, n_fact)


def main():
    input_filename = 'bynumber.in'
    output_filename = 'bynumber.out'

    # read
    with open(input_filename, 'r') as file:
        n = int(file.readline().strip())
        k = int(file.readline().strip())

    # write
    with open(output_filename, 'w') as file:
        file.write(' '.join(map(str, gen_num(n, k))))


if __name__ == "__main__":
    main()

def find_idx(v, values):
    idx = 0
    while idx < len(values) and values[idx] < v:
        idx += 1
    return idx


def gen_num(perm):
    num = 1
    values = []
    n_fact = 1

    for v in perm[::-1]:
        idx = find_idx(v, values)
        values.insert(idx, v)
        num += idx * n_fact
        n_fact *= len(values)
    return num


def main():
    input_filename = 'perm.in'
    output_filename = 'perm.out'

    # read
    with open(input_filename, 'r') as file:
        n = int(file.readline().strip())
        perm = list(map(int, file.readline().strip().split()))

    # write
    with open(output_filename, 'w') as file:
        file.write(str(gen_num(perm)))


if __name__ == "__main__":
    main()

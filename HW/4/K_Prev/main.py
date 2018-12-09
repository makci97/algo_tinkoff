def find_idx(v, values):
    idx = len(values)
    while idx > 0 and values[idx - 1] < v:
        idx -= 1
    return idx


def gen_prev_perm(n, perm):
    values = []
    for i in range(n):
        v = perm[-1]
        perm.pop()

        idx = find_idx(v, values)
        values.insert(idx, v)
        if idx != max(0, len(values) - 1):
            break
    perm.append(values[(idx + 1) % n])
    perm.extend([v for v in values if v != values[(idx + 1) % n]])
    return perm


def main():
    input_filename = 'prev.in'
    output_filename = 'prev.out'

    # read
    with open(input_filename, 'r') as file:
        n = int(file.readline().strip())
        perm = list(map(int, file.readline().strip().split()))

    # write
    with open(output_filename, 'w') as file:
        file.write(' '.join(map(str, gen_prev_perm(n, perm))))


if __name__ == "__main__":
    main()

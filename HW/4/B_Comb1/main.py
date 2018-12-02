def gen_seq(n, k, pref=None):
    if pref is None:
        pref = []

    if n == 0:
        yield pref
    else:
        if n > k:
            pref.append(0)
            yield from gen_seq(n - 1, k, pref)
            pref.pop()

        if k > 0:
            pref.append(1)
            yield from gen_seq(n - 1, k - 1, pref)
            pref.pop()


def main():
    input_filename = 'comb1.in'
    output_filename = 'comb1.out'

    # read
    with open(input_filename, 'r') as file:
        n, k = map(int, file.readline().strip().split())

    # write
    with open(output_filename, 'w') as file:
        file.write('\n'.join(map(lambda seq: ' '.join(map(str, seq)), gen_seq(n, k))))


if __name__ == "__main__":
    main()

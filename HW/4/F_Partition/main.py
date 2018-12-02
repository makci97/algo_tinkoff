def gen_seq(n, pref=None, last_n=None):
    if pref is None:
        pref = []
    if last_n is None:
        last_n = n

    if n == 0:
        yield pref
    elif n > 0:
        for i in range(1, last_n + 1):
            pref.append(i)
            yield from gen_seq(n - i, pref, i)
            pref.pop()


def main():
    input_filename = 'partition.in'
    output_filename = 'partition.out'

    # read
    with open(input_filename, 'r') as file:
        n = int(file.readline().strip())

    # write
    with open(output_filename, 'w') as file:
        file.write('\n'.join(map(lambda seq: ' '.join(map(str, seq)), gen_seq(n))))


if __name__ == "__main__":
    main()

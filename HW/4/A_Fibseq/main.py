def gen_seq(n, pref=None, used=False):
    if pref is None:
        pref = []

    if n == 0:
        yield pref
    else:
        pref.append(0)
        yield from gen_seq(n - 1, pref, False)
        pref.pop()

        if not used:
            pref.append(1)
            yield from gen_seq(n - 1, pref, True)
            pref.pop()


def main():
    input_filename = 'fibseq.in'
    output_filename = 'fibseq.out'

    # read
    with open(input_filename, 'r') as file:
        n = int(file.readline().strip())

    # write
    with open(output_filename, 'w') as file:
        file.write('\n'.join(map(lambda seq: ' '.join(map(str, seq)), gen_seq(n))))


if __name__ == "__main__":
    main()

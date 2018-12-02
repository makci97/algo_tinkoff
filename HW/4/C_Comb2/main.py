def gen_descending_seq(n, k, pref=None, cur_min=None):
    if pref is None:
        pref = []
    if cur_min is None:
        cur_min = n + 1

    if k == 0:
        yield pref
    elif cur_min > k:
        for i in range(1, cur_min):
            pref.append(i)
            yield from gen_descending_seq(n, k - 1, pref, i)
            pref.pop()


def main():
    input_filename = 'comb2.in'
    output_filename = 'comb2.out'

    # read
    with open(input_filename, 'r') as file:
        k, n = map(int, file.readline().strip().split())

    # print('\n'.join(map(lambda seq: ' '.join(map(str, seq)), gen_ascending_seq(n, k))))

    # write
    with open(output_filename, 'w') as file:
        file.write('\n'.join(map(lambda seq: ' '.join(map(str, seq)), gen_descending_seq(n, k))))


if __name__ == "__main__":
    main()

def gen_brackets(n_open, n_close=0, pref=None):
    if pref is None:
        pref = []

    if n_open == 0 and n_close == 0:
        yield pref
    if n_open > 0:
        pref.append('(')
        yield from gen_brackets(n_open - 1, n_close + 1, pref)
        pref.pop()
    if n_close > 0:
        pref.append(')')
        yield from gen_brackets(n_open, n_close - 1, pref)
        pref.pop()


def main():
    input_filename = 'brackets.in'
    output_filename = 'brackets.out'

    # read
    with open(input_filename, 'r') as file:
        n = int(file.readline().strip())

    # write
    with open(output_filename, 'w') as file:
        file.write('\n'.join(map(lambda seq: ''.join(map(str, seq)), gen_brackets(n))))


if __name__ == "__main__":
    main()

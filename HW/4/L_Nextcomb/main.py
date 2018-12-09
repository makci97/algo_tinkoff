def gen_next_comb(n, k, comb):
    for i, v in enumerate(comb[::-1]):
        if v < n - i:
            for j in range(k - i - 1, k):
                v += 1
                if v > n:
                    return [0]
                comb[j] = v
            return comb
    return [0]


def main():
    input_filename = 'nextcomb.in'
    output_filename = 'nextcomb.out'

    # read
    with open(input_filename, 'r') as file:
        n, k = list(map(int, file.readline().strip().split()))
        comb = list(map(int, file.readline().strip().split()))

    # write
    with open(output_filename, 'w') as file:
        file.write(' '.join(map(str, gen_next_comb(n, k, comb))))


if __name__ == "__main__":
    main()

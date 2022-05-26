import time


def read_from_file(filename: str):
    with open(filename) as file:
        lines = file.readlines()
        lines = [line.rstrip().split(',') for line in lines]
    return (lines[0][0], [(lines[1][i], lines[2][i]) for i in range(len(lines[1]))])


def brute_force(size, item_count, item_list):
    result = {'kit': [], 'weight': 0, 'cost': 0}

    for i in range(1, 2 ** item_count):
        binary_map = list('{0:b}'.format(i).zfill(item_count))
        cost = weight = 0
        overflow = False
        for index, state in enumerate(binary_map):
            if state == '1':
                cost += item_list[index][0]
                weight += item_list[index][1]
                if weight > size:
                    overflow = True
                    break
        if not overflow and result['cost'] < cost:
            result.update({'kit': binary_map, 'cost': cost, 'weight': weight})
    return result


def main():
    sizes, item_list = read_from_file('plecak.txt')
    size, item_count = sizes.split(' ')

    print(brute_force(int(size), int(item_count),
                      [[int(x[0]), int(x[1])] for x in item_list]))


if __name__ == '__main__':
    start = time.time()
    main()
    end = time.time()
    print("Elapsed time:", end - start)

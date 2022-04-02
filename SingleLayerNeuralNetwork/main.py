import os.path
import sys
from os.path import normpath, basename

from net import Net
from utils import generate_train_set


def main():
    root = './data/'
    paths = ['/home/mmich/Desktop/test/sample_sv.txt', '/home/mmich/Desktop/test/sample_de.txt',
             '/home/mmich/Desktop/test/sample_nl.txt', '/home/mmich/Desktop/test/sample_pl.txt']

    net = Net(generate_train_set(root, ['de', 'nl', 'sv', 'pl', 'en']))
    net.train()

    for path in paths:
        print('analyzed file: ', path, end='')
        net.test_file(path)

    print('Enter text:')
    while True:
        print('>', end='')
        user_input = input()
        if user_input:
            net.test_user_input(user_input)
        else:
            break


if __name__ == '__main__':
    sys.exit(main())

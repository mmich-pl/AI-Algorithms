from random import shuffle

from perceptron import Perceptron
from sample import Sample
from utils import create_vector_from_file, create_vector_from_string


class Net:
    def __init__(self, input:dict):
        self.perceptrons = [Perceptron(len(input[key][0]), key) for key in input]
        self.train_list = [Sample(key, sample) for key in input for sample in input[key]]

    def train(self):
        for i in range(100):
            shuffle(self.train_list)
            for n in self.train_list:
                for p in self.perceptrons:
                    p.train(n, (1 if n.language == p.trained_for_language else 0))
        self.norlmalize_perceptrons()

    def norlmalize_perceptrons(self):
        for p in self.perceptrons:
            p.normalize_perceptron()
            print(p.trained_for_language, [round(i, 2) for i in p.weights])

    def test_file(self, test_file:str):
        v = create_vector_from_file(test_file)
        sample = Sample('Unknown', v)
        sample.normalize_sample()

        self.__test(sample)

    def __test(self, sample:Sample):
        max_score = -1
        language = ''
        for p in self.perceptrons:
            if p.calculate_net(sample) > max_score:
                max_score = p.calculate_net(sample)
                language = p.trained_for_language
        print(' recognized language: ', language)

    def test_user_input(self, test_string:str):
        v = create_vector_from_string(test_string)
        sample = Sample('Unknown', v)
        sample.normalize_sample()

        self.__test(sample)

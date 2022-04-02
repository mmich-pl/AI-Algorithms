import math
import random as rand

import numpy as np

from sample import Sample

class Perceptron:
    def __init__(self, dimensions: int, trained_for_language: str):
        self.weights = self.generate_weights(dimensions)
        self.alpha = 0.01
        self.theta = 1
        self.trained_for_language = trained_for_language

    def calculate_net(self, sample: Sample) -> float:
        return self.get_inner_product(sample.vector) - self.theta

    def get_inner_product(self, input_list: list) -> float:
        return np.inner(input_list, self.weights).sum()

    def update_weights(self, values: list, d: float):
        for i in range(len(self.weights)):
            self.weights[i] += int(values[i]) * self.alpha * d
        self.theta += -1 * self.alpha * d

    def generate_weights(self, dimensions: int):
        rand.seed(1)
        return [round(rand.uniform(-0.5, 0.5), 4) for _ in range(dimensions)]

    def train(self, sample: Sample, correct_answer: int):
        prediction = 1 if self.calculate_net(sample) >= 0 else 0
        if prediction != correct_answer:
            self.update_weights(sample.vector, correct_answer - prediction)

    def normalize_perceptron(self):
        sum_of_squares = sum(i ** 2 for i in self.weights)
        length = math.sqrt(sum_of_squares)

        self.weights = [(item / length) for item in self.weights]
import math

import numpy as np


class Sample:
    def __init__(self, language: str, vector: list):
        self.language = language
        self.vector = vector

    def normalize_sample(self):
        sum_of_squares = sum(i ** 2 for i in self.vector)
        length = math.sqrt(sum_of_squares)

        self.vector = [(item/length) for item in self.vector]


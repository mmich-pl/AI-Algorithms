import os
import string
from os.path import basename, normpath


def count_letter_occurence(input_string: str) -> dict:
    return dict((key, input_string.count(key)) for key in string.ascii_lowercase)


def merge_dictionaries(a: dict, b: dict) -> dict:
    return {x: a.get(x, 0) + b.get(x, 0) for x in sorted(set(a) | set(b))}


def create_vector_from_file(path: str) -> list:
    chars = {}
    with open(path, 'r') as file:
        for line in file:
            chars = merge_dictionaries(chars, count_letter_occurence(line))
    return [*chars.values()]


def create_vector_from_string(input: str) -> list:
    chars = count_letter_occurence(input)
    return [*chars.values()]


def generate_train_set(root: str, required_languages:list) -> dict:
    train_set = {}
    for (path, subdirs, files) in os.walk(root):
        key = basename(normpath(path))
        if key not in required_languages:
            continue
        for name in files:
            v = create_vector_from_file(os.path.join(path, name))
            if key in train_set:
                train_set[key].append(v)
            else:
                train_set[key] = [v]
    return train_set
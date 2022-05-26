from cgi import test
import numpy as np
import pandas as pd
from sklearn import datasets

# data preparation


def partition_data(df):
    atrributes = df.drop([df.columns[-1]], axis=1)
    answers = df[df.columns[-1]]
    return atrributes, answers


class Classificator:

    def __init__(self):
        self.attributes_heareds = list
        self.likelihoods = {}
        self.priors = {}
        self.evidence = {}

        self.train_atrributes = []
        self.train_answers = []
        self.train_size = int
        self.outcomes = []

    def fit(self, attributes, answers):
        self.attributes_heareds = list(attributes.columns)
        self.train_atrributes = attributes
        self.train_answers = answers
        self.train_size = len(self.train_answers)
        self.outcomes = np.unique(self.train_answers)

        for attr in self.attributes_heareds:
            self.likelihoods[attr] = {}
            self.evidence[attr] = {}

            for val in np.unique(self.train_atrributes[attr]):
                self.evidence[attr].update({val: 0})

                for outcome in np.unique(self.train_answers):
                    self.likelihoods[attr].update({val+'_'+outcome: 0})
                    self.priors.update({outcome: 0})

        self._calc_prior()
        self._calc_likelihoods()
        self._calc_evidence()

    def _calc_prior(self):
        for outcome in self.outcomes:
            outcome_count = sum(self.train_answers == outcome)
            self.priors[outcome] = outcome_count/self.train_size

    def _calc_likelihoods(self):
        for attr in self.attributes_heareds:
            possible_attributes = np.unique(self.train_atrributes[attr])
            for outcome in self.outcomes:
                outcome_count = sum(self.train_answers == outcome)
                likelihood = self.train_atrributes[attr][self.train_answers[self.train_answers == outcome]
                                                         .index.values.tolist()].value_counts().to_dict()

                for a in possible_attributes:
                    if likelihood.get(a) == None:
                        likelihood.get(a, 0)

                for val, count in likelihood.items():
                    self.likelihoods[attr][val + '_' + outcome] = count/outcome_count if count != 0 else 1 / (
                        outcome_count + len(np.unique(self.train_atrributes[attr])))

    def _calc_evidence(self):
        for attr in self.attributes_heareds:
            val = self.train_atrributes[attr].value_counts().to_dict()
            for v, count in val.items():
                self.evidence[attr][v] = count/self.train_size

    def predict(self, test_attributes):
        results = []
        test_attributes = np.array(test_attributes)

        for q in test_attributes:
            probability_outcome = {}
            for outcome in self.outcomes:
                prior = self.priors[outcome]
                likelihood = 1
                evidence = 1

                for attr, val in zip(self.attributes_heareds, q):
                    likelihood *= self.likelihoods[attr][val + '_' + outcome]
                    evidence *= self.evidence[attr][val]

                posterior = (likelihood * prior) / (evidence)
                probability_outcome[outcome] = posterior

            result = max(probability_outcome,
                         key=lambda x: probability_outcome[x])
            results.append(result)
        return results


# validation
def evaluate_algorithm(c: Classificator, n_folds, filename):
    folds = cross_validation_split(n_folds, filename)
    scores = list()
    for fold in folds:
        train_set = list(folds)
        train_set.remove(fold)
        train_set = sum(train_set, [])
        test_set = list()
        for row in fold:
            row_copy = list(row)
            test_set.append(row_copy)
            row_copy[-1] = None

        tuple = partition_data(pd.DataFrame(train_set))
        c.fit(tuple[0], tuple[1])

        predicted = c.predict(partition_data(pd.DataFrame(test_set))[0])

        actual = [row[-1] for row in fold]
        accuracy = accuracy_metric(actual, predicted)
        scores.append(accuracy)
    return scores


def cross_validation_split(n_folds, filename):
    dataset_split = list()
    df = pd.read_csv(filename)
    fold_size = int(len(df) / n_folds)
    for _ in range(n_folds):
        fold = list()
        fold = df.groupby(df.iloc[:, -1], group_keys=False) \
            .apply(lambda x: x.sample(frac=fold_size/len(df)))
        dataset_split.append(fold.values.tolist())
    return dataset_split


def accuracy_metric(actual, predicted):
    correct = 0
    for i in range(len(actual)):
        if actual[i] == predicted[i]:
            correct += 1
    return correct / float(len(actual)) * 100.0


def test_file(filename):
    test_set = pd.read_csv(filename)
    query = np.array(test_set.values.tolist())
    print("{}".format(c.predict(query)))


filename = 'weather_header.csv'

n_folds = 10
c = Classificator()

scores = evaluate_algorithm(c, n_folds, filename)

print('Scores: %s' % scores)
print('Mean Accuracy: %.3f%%' % (sum(scores)/float(len(scores))))

test_file('bayes_testset.csv')

print('Enter values divided by commas:')
while True:
    print('>', end='')
    user_input = input()
    if user_input:
        query = np.array([user_input.split(',')])
        print("{} ---> {}".format(query, c.predict(query)))
    else:
        break

from random import randrange
from csv import reader
from attr import attributes
from matplotlib.pyplot import axis
import numpy as np
import pandas as pd


def partition_data(df):
    atrributes = df.drop([df.columns[-1]], axis=1)
    answers = df[df.columns[-1]]
    return atrributes, answers


def split_sets(df, test_size=0.1):
    test_df = df.groupby(df.columns[-1], group_keys=False)\
        .apply(lambda x: x.sample(frac=test_size))
    train_df = df.drop(test_df.index)

    return partition_data(test_df), partition_data(train_df)


class Classificator:

    """
				likelihood * class prior 
	posterior = ------------------------
				    evidence
	"""

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
        """P(c) - prior class probability"""
        for outcome in self.outcomes:
            outcome_count = sum(self.train_answers == outcome)
            self.priors[outcome] = outcome_count/self.train_size

    def _calc_likelihoods(self):
        """ P(x|c) - Likelihood """
        for attr in self.attributes_heareds:
            for outcome in self.outcomes:
                outcome_count = sum(self.train_answers == outcome)
                likelihood = self.train_atrributes[attr][self.train_answers[self.train_answers == outcome]
                                                         .index.values.tolist()].value_counts().to_dict()

                for feat_val, count in likelihood.items():
                    self.likelihoods[attr][feat_val +
                                           '_' + outcome] = count/outcome_count

    def _calc_evidence(self):
        """ P(x) - Evidence """
        for attr in self.attributes_heareds:
            val = self.train_atrributes[attr].value_counts().to_dict()

            print(val)

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
                    likelihood *= self.likelihoods[attr][val]
                    evidence *= self.evidence[attr][val]

                posterior = (likelihood * prior) / (evidence)
                probability_outcome[outcome] = posterior
            result = max(probability_outcome,
                         key=lambda x: probability_outcome[x])
            results.append(result)
        return results


#     def getDecisionAttributes(self):
#         result = dict()

#         for row in self.dataset:
#             attr = row[-1]
#             result[attr] = 1 if attr not in result else result[attr]+1
#         return result

#     def get_possible_answers(self, attr):
#         return {row[attr] for row in self.dataset}

#     def create_fraction(self, input: str, attr: int, decision: str) -> float:
#         numerator = 0.0
#         denominator = self.answers[decision]

#         for row in self.dataset:
#             if row[attr] == input and row[-1] == decision:
#                 numerator += 1

#         return self.laplace(denominator, attr) if numerator == 0 else numerator/denominator

#     def naiveBayes(self, input: list, decision: str):
#         result = 1.0
#         for i in range(len(input)):
#             result = result * self.create_fraction(input[i], i, decision)

#         return result * self.answers[decision]/len(self.dataset)

#     def find_answer(self, testing_data: list):
#         a = []

#         for row in testing_data:
#             best_val = 0.0
#             for key in self.answers:
#                 val = self.naiveBayes(row, key)
#                 if val > best_val:
#                     best_val = val
#                     a.append(key)
#         return a

#     # validation
#     def evaluate_algorithm(self, n_folds):
#         folds = self.cross_validation_split(n_folds)
#         scores = list()
#         for fold in folds:
#             train_set = list(folds)
#             train_set.remove(fold)
#             train_set = sum(train_set, [])
#             test_set = list()
#             for row in fold:
#                 row_copy = list(row)
#                 test_set.append(row_copy)
#                 row_copy[-1] = None
#             predicted = self.find_answer(test_set)
#             actual = [row[-1] for row in fold]
#             accuracy = self.accuracy_metric(actual, predicted)
#             scores.append(accuracy)
#         return scores

#     def cross_validation_split(self, n_folds):
#         dataset_split = list()
#         fold_size = int(len(self.dataset) / n_folds)
#         for _ in range(n_folds):
#             fold = list()
#             fold = self.dataframe.groupby(self.dataframe.iloc[:, -1], group_keys=False) \
#                 .apply(lambda x: x.sample(frac=fold_size/len(self.dataset)))
#             dataset_split.append(fold.values.tolist())
#         return dataset_split

#     def accuracy_metric(self, actual, predicted):
#         correct = 0
#         for i in range(len(actual)):
#             if actual[i] == predicted[i]:
#                 correct += 1
#         return correct / float(len(actual)) * 100.0
filename = 'weather_header.csv'

# n_folds = 5
# c = Classificator(filename)
# scores = c.evaluate_algorithm(n_folds)
# print(c.find_answer([['slonecznie','tak','srednia','wysoka']]))

# print('Scores: %s' % scores)
# print('Mean Accuracy: %.3f%%' % (sum(scores)/float(len(scores))))

df = pd.read_csv(filename)
sets = [element for tupl in split_sets(df, test_size=0.10) for element in tupl]

c = Classificator()
c.fit(sets[2], sets[3])


# print("Test:")
# print(X_test)

from random import randrange
from csv import reader

class Classificator:

	def __init__(self, path:str):
		self.dataset = self.load_csv(path)
		self.answers = self.getDecisionAttributes()


	def load_csv(self, filename):
		with open(filename, 'r') as file:
			return [row for row in reader(file)]

	def getDecisionAttributes(self):
		result = dict()

		for row in self.dataset:
			attr = row[-1]
			result[attr] = 1 if attr not in result else result[attr]+1
		return result

	def get_possible_answers(self, attr):
		return {row[attr] for row in self.dataset}

	def laplace(self, denominator: float, attr: int) -> float:
		possibleAnswers = self.get_possible_answers(attr)
		return 1 / denominator + len(possibleAnswers)

	def create_fraction(self, input: str, attr: int, decision: str) -> float:
		numerator = 0.0
		denominator = self.answers[decision]

		for row in self.dataset:
			if row[attr] == input and row[-1] == decision:
				numerator += 1

		return self.laplace(denominator, attr) if numerator == 0 else numerator/denominator

	def naiveBayes(self, input: list, decision: str):
		result = 1.0
		for i in range(len(input)):
			result = result * self.create_fraction(input[i], i, decision)

		return result * self.answers[decision]/len(self.dataset)

	def find_answer(self, testing_data: list):
		a = []

		for row in testing_data:
			best_val = 0.0
			for key in self.answers:
				val = self.naiveBayes(row, key)
				if val > best_val:
					best_val = val
					a.append(key)
		return a

	# validation

	def evaluate_algorithm(self, n_folds):
		folds = self.cross_validation_split(n_folds)
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
			predicted = self.find_answer(test_set)
			actual = [row[-1] for row in fold]
			accuracy = self.accuracy_metric(actual, predicted)
			scores.append(accuracy)
		return scores

	def cross_validation_split(self, n_folds):
		dataset_split = list()
		dataset_copy = list(self.dataset)
		fold_size = int(len(self.dataset) / n_folds)
		for _ in range(n_folds):
			fold = list()
			while len(fold) < fold_size:
				index = randrange(len(dataset_copy))
				fold.append(dataset_copy.pop(index))
			dataset_split.append(fold)
		return dataset_split

	def accuracy_metric(self, actual, predicted):
		correct = 0
		for i in range(len(actual)):
			if actual[i] == predicted[i]:
				correct += 1
		return correct / float(len(actual)) * 100.0





filename = 'bayes_trainingset.csv'

n_folds = 5
c = Classificator(filename)
scores = c.evaluate_algorithm(n_folds)

print('Scores: %s' % scores)
print('Mean Accuracy: %.3f%%' % (sum(scores)/float(len(scores))))

import nltk
from nltk.tokenize import word_tokenize

class strainer:
	def __init__(self, _stopword):
		self.stopword = _stopword

	def read(self, filename):		
		fw  = open(filename,"r")		
		rw  = fw.read()
		w = word_tokenize(rw)
		
		return w

	def clear(self, filename):
		fsw = open(self.stopword,"r")
		rsw = fsw.read()
		sw = rsw.split()

		w = self.read(filename)
		for i in sw:
			w = list(filter(lambda x: x != i, w))

		return w

class statistics:
	def __init__(self, _ngram, _filename):
		self.ngram = _ngram
		self.mstrainer = strainer(_filename)
		self.pmi = []
		self.tupla = []

	def set_tupla(self, words):
		for i in range(0,len(words)-1):
			self.tupla.append((words[i], words[i+1]))

	def number_repeat(self, word, words):
		c = 0
		for i in words:
			if i == word:
				c+=1

		return c

	def number_sequence(self, word1, word2, words):
		c = 0
		for i in range(0,len(words)-1):
			if words[i]==word1 and words[i+1]==word2:
				c+=1

		return c

	def fpmi(self, filename):
		words = self.mstrainer.clear(filename)
		self.set_tupla(words);

		#for i in self.tupla:
			#n11 = self.number_sequence(i[0], i[1], words)
			#n12 = self.number_repeat(i[0], words)-n11
			#n12 = self.number_repeat(i[1], words)-n11

		print(len(self.tupla))
		print(len(words))


def main():
	tmp = statistics(2, "data/sw_spanish.dat")
	tmp.fpmi("data/txt_valid.dat")

if __name__ == "__main__": 	
    main()
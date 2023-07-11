import random

def generate_input():
  """Generates a random floating point input."""
  special_values = [float('NaN'), float('Infinity'), float('-Infinity')]
  boundary_values = [1.1754943508222875e-38, -1.1754943508222875e-38]
  random_values = [random.random() for _ in range(10)]

  #return random.choice([special_values, boundary_values, random_values])
  return random.choice([float('NaN'), float('Infinity'), float('-Infinity'),1.1754943508222875e-38, -1.1754943508222875e-38, random_values])

def main():
  """Generates a corpus of 1000 floating point inputs."""
  #corpus = []
  corpus_str=""
  for _ in range(1000):
    #corpus.append(generate_input())
    corpus_str = corpus_str + "," + str(generate_input())

  corpus_str = corpus_str [1:]
  with open('input.corpus', 'w') as f:
    f.writelines(corpus_str)

if __name__ == '__main__':
  main()
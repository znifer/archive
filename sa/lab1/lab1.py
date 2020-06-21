# This Python file uses the following encoding: utf-8
import random
import math
import numpy
from scipy.stats import norm
import matplotlib.pyplot as pyplot

n = 6
mx = 3
sigma = 0.5
sz = 1000
def getRandomNumbers(sz):
    result = []
    for i in range (0, sz):
        result.append(random.random())
    return result

def getGaussian(sz):
    result = []
    for i in range(0, sz):
        v = getRandomNumbers(n)
        x = sigma * math.sqrt(2) * (numpy.sum(v) - n / 2) + mx
        result.append(x)
    return result

if __name__ == "__main__":
    result = getGaussian(sz)
    min = numpy.min(result)
    max = numpy.max(result)     
    step = (abs(min) + max)/ 10
    a = numpy.arange(min, max, step)
    data = numpy.full_like(a, 0)
    x_axis = numpy.arange(min - 1, max + 1, 0.001)  
    pyplot.plot(x_axis, norm.pdf(x_axis, mx, sigma))
    pyplot.hist(result, density=True)
    pyplot.show()

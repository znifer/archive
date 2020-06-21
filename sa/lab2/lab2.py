# This Python file uses the following encoding: utf-8
import random
import math
import numpy
import scipy.integrate as integrate
import scipy.optimize as optimize
import matplotlib.pyplot as pyplot

sz = 10000
a = 1
b = 2
result = []
arr = []
def fx(x):
    return 4 * x**2 + 2 * x + 1

def gx(x):
    return (4 * x**2 + 2 * x + 1) / k

def prob_num(xi,v):
    s1 = integrate.quad(fx, a, xi)[0]
    return (s1/k - v)

    
if __name__ == "__main__":
    k = integrate.quad(fx, a, b)[0]
    for i in range(0, sz):
        arr.append(numpy.random.random_sample())
    
    for i in arr:
        def t(x):
            return prob_num(x,i)
        
        solve = optimize.fsolve(t, b)
        result.append(solve[0])
        numpy.round(solve, 3, solve)
    
    
    x_axis = numpy.linspace(a, b) 
    fig, ax = pyplot.subplots(1, 1)
    pyplot.plot(x_axis, numpy.apply_along_axis(gx, 0, x_axis))
    pyplot.hist(result, 20, density=True)
    pyplot.show()

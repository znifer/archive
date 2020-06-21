# This Python file uses the following encoding: utf-8
import random
import math
import numpy
import scipy.integrate as integrate
import scipy.optimize as optimize
import matplotlib.pyplot as pyplot

sz = 11

v = 5
sg = 0.2
k = 5
def fx(x):
    return math.exp(-x) + math.cos(2 * x)

def gx(i, x):
    return math.cos(i * x)

#v 4
#sg = 2
#k = 3
#def fx(x):
    #return math.log10(x**2)

#def gx(i, x):
    #return math.exp((i - 1) * x)

#v 22
#sg = 0.5
#k = 6
#def fx(x):
    #return x * math.sqrt(x)

#def gx(i, x):
    #return math.cos(i * x) + math.sin(i * x)

def zx(x, func):
    res = 0
    for i in range(0, k):
        res += a[i] * func(i, x)
    return res

if __name__ == "__main__":
    y_t = []
    v = []
    y = []
    K = []
    x = []
    Z = []
    for i in range (0, sz):
        y_t.append(fx(i + 1))
        x.append(i + 1)        
        K.append(numpy.zeros(sz))
        K[i][i] = sg * (i + 1) * 0.1
        if (random.randint(0, 1)):
            y.append(y_t[i] + K[i][i])
        else:
            y.append(y_t[i] - K[i][i])

    F = numpy.zeros((sz, k))
    for j in range(0, sz):
        for i in range(0, k):
            F[j][i] = gx(i, x[j])

    a = numpy.linalg.inv(F.transpose().dot(K).dot(F)).dot(F.transpose()).dot(K).dot(y)
    print(a)
    for i in x:
        Z.append(zx(i, gx))
    
    print("F(4.5) = ", fx(4.5))
    print("Z(4.5) = ", zx(4.5, gx))
    print("F(9) = ", fx(9.5))
    print("Z(9) = ", zx(9.5, gx))

    pyplot.scatter(x, y)
    pyplot.scatter(x, y_t)
    pyplot.plot(x, Z)
    pyplot.show()

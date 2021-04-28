import scipy.integrate as si
import matplotlib.pyplot as plt
import numpy as np
from math import *
import pylab
# Правая часть уравнения
def function(args, t):
    # Константы
    l = 1.2
    I = 0.5
    m1 = 5
    m2 = 1
    n = 2
    k1 = 20000
    k2 = 40000
    g = 9.81
    

    
    # Распаковываем набор переменных
    x, v, phi, omega = args
    Ax = l * sin(phi)
    Ay = l * cos(phi)
    Bx = -n + x
    By = l
    AB = sqrt((Bx - Ax)**2 + (By - Ay)**2)
    Aox = Ax
    Aoy = l
    AoB = sqrt ((Bx - Aox)**2 + (By - Aoy))
    cosa = ((Bx-Ax)*(Bx-Aox) + (By - Ay)*(By-Aoy))/(AB*AoB)
    cosb = (-Ay * (Bx - Ax) + Ax * (By-Ay))/(AB/l)

    Fypr1 = -x * k1
    Fypr2 = -(AB - n) * k2

    Fypr = Fypr1 - Fypr2
    
    Mypr = Fypr2 * cosb * l
    Mt = -m2 * g * l / 2 * sin(phi)
    return [
        v,
        (-k1 * x + k2 * (-x + l * phi))/m1,
        omega,
        #(-1/2 * l * m2 * g * phi + k2 * (x - l * phi) * l) / I
        (Mypr + Mt) / I  ]  


def main():
    # Задаем константы
    first = 0.0
    last = 0.2
    step = 0.0001 
    # Массив точек, по которым интегрируем
    x = np.arange(first, last, step)
    # Начальное условие, массив, каждый элемент которого - начальное значение параметра в точке first
    y0 = [0.1, 0.1, 0.5, 0.1]
    #
    solution = si.odeint(function, y0, x)
    print(solution[0])
    
    x_sol = solution[:, 0]
    v_sol = solution[:, 1]
    phi_sol = solution[:, 2]
    omega_sol = solution[:, 3]
    #plt.plot(x, x_sol)
    # plt.plot(x, v_sol)
    #plt.plot(x, phi_sol)
    # plt.plot(x, omega_sol)

    pylab.subplot(2, 2, 1)
    pylab.plot(x, x_sol)
    pylab.title("x")

    
    pylab.subplot(2, 2, 2)
    pylab.plot(x, v_sol)
    pylab.title("v")

    pylab.subplot(2, 2, 3)
    pylab.plot(x, phi_sol)
    pylab.title("phi")

    pylab.subplot(2, 2, 4)
    pylab.plot(x, omega_sol)
    pylab.title("omega")
    pylab.show()
    

    plt.show()

    

main()

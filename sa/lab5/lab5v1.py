from itertools import *
import numpy as np
import matplotlib.pyplot as plt
import math
import scipy 
import scipy.optimize as opt
import scipy.integrate as integrate
import lab5_regression

# To add a new cell, type '# %%'
# To add a new markdown cell, type '# %% [markdown]'
# %%
x_vectors = [
    (13.0, 11.0),
    (3.0, 7.0),
    (12.0, 18.0),
    (2.0, 11.0),
    (12.0, 3.0),
    (11.0, 6.0),
    (5.0, 7.0),
    (17.0, 12.0),
    (4.0, 8.0),
    (11.0, 2.0),
    (9.0, 17.0),
    (4.0, 14.0),
]

Y_vector = [
   337.2582443,
   63.3701193,
   515.5767566,
   132.0114992,
   198.5223412,
   202.0669770,
   95.8270967,
   503.0365417,
   96.0823941,
   183.3386634,
   410.8476550,
   231.4226067,
]

x_noise_check = (1.0, 12.0)

y_noise_check = [
   146.1908194,#142.4072056,
   149.6165511,#145.5690592,
   148.0149887,#144.0908624,
   150.5093942,#146.3931282,
   152.3339211,#148.0771151,
   152.8967778,#148.5966160,
   146.3115603,#142.5186460,
   146.3516791,#142.5556745,
   153.6590343,#149.3001572,
   151.1223078#146.9588302
]


# %%
# составные уравнения регрессии
def f_x1(x1, x2):
    return x1
f_x1.__name__ = "x₁"

def f_x2(x1, x2):
    return x2
f_x2.__name__ = "x₂"

def f_x1x1(x1, x2):
    return x1 ** 2
f_x1x1.__name__ = "x₁²"

def f_x1x2(x1, x2):
    return x1 * x2
f_x1x2.__name__ = "x₁x₂"

def f_x2x2(x1, x2):
    return x2 ** 2
f_x2x2.__name__ = "x₂²"

def f_x2x2x1(x1, x2):
    return x2 ** 2 *x1
f_x2x2x1.__name__ = "x₁x₂²"

def f_x1x1x2(x1, x2):
    return x1 ** 2 *x2
f_x1x1x2.__name__ = "x₁²x₂"

# возможные слагаемые уравнения регрессии
polynom_parts = [f_x1, f_x2, f_x1x2, f_x1x1, f_x2x2]


# %%
import lab5_regression

polynoms = lab5_regression.get_polynom_list(polynom_parts,3)
print('Список возможных полиномов')
for index,polynom in enumerate(polynoms,start=1):
    print('{}. {}'.format(index,' + '.join(lab5_regression.get_functions_labels(polynom))))


# %%
F_matrices = lab5_regression.get_all_F_matrices(polynoms,x_vectors)
a_vectors = lab5_regression.get_all_a_vectors(F_matrices,Y_vector)
best1_index,best2_index = lab5_regression.get_best_polynom(F_matrices,a_vectors,Y_vector)

print('Лучшие полиномы:')
print('R² через QR: ',' + '.join(lab5_regression.get_functions_labels(polynoms[best1_index])))
print('R² через Qstop: ',' + '.join(lab5_regression.get_functions_labels(polynoms[best2_index])))


# %%
import numpy as np
print('Дисперсия гауссовского шума по Y: ',np.var(y_noise_check))

# %% [markdown]
# ### Уравнение через $Q_R$

# %%
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

print(lab5_regression.get_regression_equation
(
    lab5_regression.get_functions_labels(polynoms[best1_index])
    ,a_vectors[best1_index])
)

x1_list,x2_list = [],[]
for i in x_vectors:
    x1_list.append(i[0])
    x2_list.append(i[1])

y_cap_vector = F_matrices[best1_index].dot(a_vectors[best1_index])

fig = plt.figure()
axes = Axes3D(fig)
axes.scatter(np.array(x1_list), np.array(x2_list), np.array(Y_vector))
axes.scatter(np.array(x1_list), np.array(x2_list), np.array(y_cap_vector))
plt.show()

# %% [markdown]
# ### Уравнение через $Q_{stop}$

# %%
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

print(lab5_regression.get_regression_equation
(
    lab5_regression.get_functions_labels(polynoms[best2_index])
    ,a_vectors[best2_index])
)

x1_list,x2_list = [],[]
for i in x_vectors:
    x1_list.append(i[0])
    x2_list.append(i[1])


y_cap_vector = F_matrices[best2_index].dot(a_vectors[best2_index])
fig = plt.figure()
axes = Axes3D(fig)
axes.scatter(np.array(x1_list), np.array(x2_list), np.array(Y_vector),label = 'Исходные данные')
axes.scatter(np.array(x1_list), np.array(x2_list), np.array(y_cap_vector),label = 'Полученные значения')
plt.show()


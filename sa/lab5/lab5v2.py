# To add a new cell, type '# %%'
# To add a new markdown cell, type '# %% [markdown]'
# %%
x_vectors = [
    (8.0, 12.0),
    (7.0, 4.0),
    (9.0, 11.0),
    (5.0, 9.0),
    (8.0, 8.0),
    (4.0, 6.0),
    (5.0, 11.0),
    (10.0, 17.0),
    (6.0, 11.0),
    (4.0, 9.0),
    (5.0, 16.0),
    (4.0, 7.0),
]

Y_vector = [
    434.6056050,
    99.4576048,
    426.5185028,
    219.8754453,
    261.1813246,
    113.2138322,
    293.0785722,
    811.3168444,
    325.0937345,
    209.3121888,
    506.5148699,
    140.8936827,
]

x_noise_check = (4.0, 8.0)

y_noise_check = [
    185.8041733,
    189.7014111,
    187.8794151,
    190.7171421,
    192.7927908,
    193.4331172,
    185.9415325,
    185.9871731,
    194.3002881,
    191.4144151,
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


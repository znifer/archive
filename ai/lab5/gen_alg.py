# This Python file uses the following encoding: utf-8
import random
from randomizer import Randomizer
from PyQt5.QtCore import qDebug
class Gen_alg:
    def __init__(self, n, iterations, r_count, crossing_prob):
        # Количество вершин графа
        self.n = n

        # Вероятность того, что при селекции будет выполнено скрещивание
        self.crossing_prob = crossing_prob

        # Мощность популяции
        self.r_count = r_count

        # Количество итераций алгоритма
        self.iterations = iterations

        # Популяция, т. е. набор решений задачи
        self.r = []
        #self.r.append([i for i in range(n - 1, 0 - 1, -1)])
        self.r.append([i for i in range(0, n)])

        # Инициализируем случайными величинами
        for i in range(1, n):
            self.r.append(Randomizer.swap_list_elements(self.r[i - 1], 5))

        if (n == 10):
            self.distances = [[0, 1, 2, 3, 4, 5, 6, 7, 8, 9],
                              [1, 0, 1, 2, 3, 4, 5, 6, 7, 8],
                              [2, 1, 0, 1, 2, 3, 4, 5, 6, 7],
                              [3, 2, 1, 0, 1, 2, 3, 4, 5, 6],
                              [4, 3, 2, 1, 0, 1, 2, 3, 4, 5],
                              [5, 4, 3, 2, 1, 0, 1, 2, 3, 4],
                              [6, 5, 4, 3, 2, 1, 0, 1, 2, 3],
                              [7, 6, 5, 4, 3, 2, 1, 0, 1, 2],
                              [8, 7, 6, 5, 4, 3, 2, 1, 0, 1],
                              [9, 8, 7, 6, 5, 4, 3, 2, 1, 0]]
        else:
            # Матрица расстояний между вершинами графа
            self.distances = [[0 for i in range(n)] for j in range(n)]
            # Граф неориентированный, поэтому d[i][j] = d[j][i]
            for i in range (0, n):
                for j in range (i + 1, n):
                    # Задаем случайное значение длины пути
                    r = random.randint(1, 50)
                    self.distances[i][j], self.distances[j][i] = r, r#int(r), int(r)

        # Здоровье популяции
        self.health = []
        # Вычисляем здоровье начальной популяции
        for el in self.r:
            self.health.append(self.get_health(el))

        # Позиции, с которых делали мутации
        self.mutation_pos = [1 for i in range(n)]

        # Лучшие решения за каждую итерацию
        self.best_solutions = []


    def perform(self):
        # Для каждой итерации
        for iteration in range(self.iterations):
            # Решаем, что будем делать - скрещивать или мутировать
            newr = []
            for k in range(self.r_count):
                if random.random() < self.crossing_prob:
                    # Скрещиваем
                    pos1, pos2 = self.get_crossing_els()

                    # И сохраняем результат
                    t = self.crossing(self.r[pos1], self.r[pos2])
                    newr.append(t.copy())

                else:
                    # Находим самого хромого
                    pos = self.get_mutating_el()
                    # И даем ему шанс стать еще и слепым
                    t = self.mutate(self.r[pos], self.mutation_pos[pos])
                    newr.append(t.copy())
                    self.mutation_pos[pos] += 1
                    # А если самый хромой не излечился за положенное число раз,
                    # обнуляем позицию сдвига
                    if self.mutation_pos[pos] >= self.n - 1:
                        self.mutation_pos[pos] = 1

            # Вычисляем здоровье каждого из популяции
            self.health.clear()
            self.r.clear()
            self.r = newr
            while (len(self.mutation_pos) < len(self.r)):
                self.mutation_pos.append(1)

            for el in self.r:
                self.health.append(self.get_health(el))

            self.save_best()

    def get_distances(self):
        return self.distances

    def get_best_solutions(self):
        return self.best_solutions

    def save_best(self):
        index = self.health.index(max(self.health))
        self.best_solutions.append(self.r[index].copy())

    def get_random_best_r(self):
        total_health = sum(self.health)
        probs = [h / total_health for h in self.health]
        prob = random.random()
        prob_sum = 0
        for i in range(len(probs)):
            prob_sum += probs[i]
            if prob < prob_sum:
                return i

    def get_crossing_els(self):
        i = self.get_random_best_r();
        j = i
        while (i == j):
            j = self.get_random_best_r()
        return i, j

    def get_mutating_el(self):
        reverse_health = [1 / h for h in self.health]
        total_health = sum(reverse_health)

        probs = [h / total_health for h in reverse_health]
        prob = random.random()
        prob_sum = 0
        for i in range(len(probs)):
            prob_sum += probs[i]
            if prob < prob_sum:
                return i

    def mutate(self, r, pos):
        const_part = r[:pos]
        changing_part = r[pos:]
        changing_part.reverse()
        return const_part + changing_part

    def crossing(self, r1, r2):
        cross_factor = 0.3
        free_r1 = set()
        free_r2 = set()
        while len(free_r1) < len(r1) * cross_factor:
            #qDebug('{}'.format( len(r1) * cross_factor))
            i = random.randint(0, len(r1) - 1)
            if i in free_r1:
                continue
            free_r1.add(i)
            free_r2.add(r2.index(r1[i]))


        new_r1 = [r2[free_r2.pop()] if i in free_r1 else r1[i] for i in range(len(r1))]
        return new_r1

    def get_distance(self, r):
        health = 0
        prev_pos = r[0]
        for i in range(1, len(r)):
            health += self.distances[prev_pos][r[i]]
        return health


    def get_health(self, r):
        health = 0
        prev_pos = r[0]
        for i in range(1, len(r)):
            health += self.distances[prev_pos][r[i]]

        # Поскольку решаем задачу максимизации, а в задаче про чувака из орифлейм речь
        # про минимальную стоимость пути, берем обратную величину от стоимости пути
        if health == 0:
            return 0.000000000000001
        return 1 / health

        # Или не переходим
        #return health

    def get_list_distances(self, r):
        prev_pos = r[0]
        dist = []
        for i in range(1, len(r)):
            dist.append(self.distances[prev_pos][r[i]])
        return dist

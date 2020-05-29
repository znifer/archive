import random
import math
import numpy
from scipy.special import factorial as fact

i = 3
j = 10 
k = 9

# На сервере есть n каналов передачи сообщений. Среднее время обработки сообщений tau. На сервер поступают сообщения в среднем количестве lmb сообщений в минуту. 
# Определить основные характеристики сервера (абсолютную пропускную способность, т.е. среднее число сообщений, обрабатываемых в единицу времени; 
# относительную пропускную способность, т.е. среднюю долю пришедших сообщений, обрабатываемых системой; вероятность отказа в обработке; среднее число занятых каналов), 
# если сообщение получает отказ при занятости всех каналов. Параметры варианта определяются по формулам: n=3+[(i+j)/8], lmb=1+i/4, tau=5/(5+j). 

n = 3 + ((i + j) // 8)          # Количество каналов передачи сообщений
lmb = 1 + i / 4                 # Количество сообщений в минуту
tau = 5 / (5 + j)               # Среднее время обработки сообщений
print("Дано:")
print ("i = {}, j = {}".format(i, j))
print("Количество каналов передачи n = {}, Сообщений в минуту λ = {},  Среднее время обработки сообщений τ = {}".format(n, lmb, tau))

mu = 1 / tau                  # Интенсивность потока обслуживания
ro = lmb / mu                 # Приведенная интенсивность потока
print("Интенсивность потока обслуживания μ = {}, Приведенная интенсивность потока ρ = {}".format(mu, ro))
P = []                        # Предельные вероятности
P.append(1 + ro)
for i in range (2, n + 1):
     P[0] += (ro ** i) / fact(i)
P[0] = P[0] ** -1

P.append(ro * P[0])
for i in range (2, n + 1):
     P.append((ro ** i) / fact(i) * P[0])
print("P = {}".format(P))

P_otk = (ro ** n) / fact(n) * P[0]    # Вероятность отказа, т. е. того, что заявка покинет СМО не обслуженной
Q = 1 - P_otk                                     # Относительная пропускная способность
A = lmb * Q                                       # Абсолютная пропускная способность  
k = 0                                             # Среднее число занятых каналов 
for i in range(0, n + 1):
     k += i * P[i]

print("Теоретические значения:")
print("Абсолютная пропускная способность: A = {}".format(A))
print("Относительная пропускная способность: Q = {}".format(Q))
print("Вероятность отказа в обработке: P_отк = {}".format(P_otk))
print("Среднее число занятых каналов: `k = {}".format(k))

# Возвращает номер свободного канала, иначе - -1
def isEmpty(channels):
     for i in range(0, n):
          if channels[i] == 0:
               return i
     return -1

# Обработка уже имеющихся сообщений
def messagesProcessing(channels, delta):
     for i in range (0, len(channels)):
          if (channels[i] > delta):
               channels[i] -= delta
          else:
               channels[i] = 0

# Полученные сообщения отправляем на обработку, если есть свободные каналы. 
def assignMessagesToChannels(messages, channels):
     while (isEmpty(channels) != -1 and len(messages) > 0):
          pos = isEmpty(channels)
          channels[pos] = messages.pop(0)
     #print(channels, messages)
     
channels = [] # Каналы связи
# 0, если не обрабатывается, иначе - сколько времени осталось обрабатывать
for i in range (0, n):
     channels.append(0)
maxTime = 100000         # Сколько всего будем работать
loadedChannels = 0       # Занятые каналы
unProcessedMessages = 0  # Необработанные сообщения
totalMessages = 0        # Всего сообщений
messages = []
delta = 0.1                      
averageTime = 0          # Среднее время
# Будем считать по десятой части минуты
for currentTime in range (0, int(maxTime / delta)):
     if (random.random() < 1 - math.exp(-1 * lmb * delta)):      # Если сообщение пришло
          messages.append(tau - 0.2 + random.random() / 2.5)     # Назначаем ему время обработки
          averageTime += messages[0]
          totalMessages += len(messages)                         
          assignMessagesToChannels(messages, channels)           # И назначаем свободному каналу это сообщение
          unProcessedMessages += len(messages)                   # А если сообщение не назначилось, то считаем его как необслуженное
          messages.clear()              
     loadedChannels += n - channels.count(0) 
     #print(channels)                    # Cчитаем, сколько имеем свободных каналов
     messagesProcessing(channels, delta)                         # Обрабатываем сообщение
loadedChannels = loadedChannels / (maxTime / delta)
averageTime = averageTime / totalMessages
print("Проверим теоретические значения на практике. Будем работать {} минут, при этом дельта тэ возьмем {} минуты".format(maxTime, delta))
print("Всего получено сообщений: {}, из них остались без внимания: {}".format(totalMessages, unProcessedMessages))
print("Среднее время обработки сообщения: {}".format(averageTime))
print("Относительная пропускная способность: Q = {}".format((totalMessages - unProcessedMessages) / totalMessages))
print("Абсолютная пропускная способность: А = {}".format((totalMessages - unProcessedMessages) / maxTime))
print("Вероятность отказа при обработке: P_отк = {}".format(unProcessedMessages / totalMessages))
print("Среднее число занятых каналов при этом составило: `k =  {}".format(loadedChannels))
from pyswip import Prolog

from service.search_key import search_key
# Загружаем словарь
from knowledge.dictionary1 import dictionary

prolog = Prolog()
# Загружаем базу знаний
prolog.consult("knowledge/task1.pl")

# Пройдемся по вопросам.
print("Какой журнал предоставляет информацию о современных технологиях тюнинга автомобилей?")
# Узнаем, какие журналы входят в отношение "современные технологии тюнинга автомобилей - часть Y"
query_X = '"{}"'.format(search_key(dictionary, "Современные технологии тюнинга автомобилей"))
query_Y = "Y"
query = 'part_of({X}, {Y}).'.format(X=query_X, Y=query_Y)
query_result = list(prolog.query(query))
for answer in query_result:
    for key, value in answer.items():
        print(dictionary[str(value, 'utf-8')])
print()
print("Какие журналы предназначены для мужчин?")
# Узнаем, какие журналы входят в отношение "для мужчин - часть Y"
query_X = '"{}"'.format(search_key(dictionary, "Мужчины"))
query_Y = "Y"
query = 'part_of({X}, {Y}).'.format(X=query_X, Y=query_Y)
query_result = list(prolog.query(query))
for answer in query_result:
    for key, value in answer.items():
        print(dictionary[str(value, 'utf-8')])
print()
print("Какие журналы стоят 100 рублей? ")
# Узнаем, какие журналы входят в отношение "100 руб. - часть Y"
query_X = '"{}"'.format(search_key(dictionary, "100 руб."))
query_Y = "Y"
query = 'part_of({X}, {Y}).'.format(X=query_X, Y=query_Y)
query_result = list(prolog.query(query))
for answer in query_result:
    for key, value in answer.items():
        print(dictionary[str(value, 'utf-8')])
print()
print("На какие журналы можно оформить подписку?")
# Узнаем, какие журналы входят в отношение "100 руб. - часть Y"
query_X = '"{}"'.format(search_key(dictionary, "Есть подписка"))
query_Y = "Y"
query = 'part_of({X}, {Y}).'.format(X=query_X, Y=query_Y)
query_result = list(prolog.query(query))
for answer in query_result:
    for key, value in answer.items():
        print(dictionary[str(value, 'utf-8')])

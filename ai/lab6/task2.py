from pyswip import Prolog

from service.search_key import search_key
# Загружаем словарь
from knowledge.dictionary2 import dictionary

prolog = Prolog()
# Загружаем базу знаний
prolog.consult("knowledge/task2.pl")

# Пройдемся по вопросам.
print("Кто является начальником отдела маркетинга?")
# Ищем начальника отдела и часть отдела маркетинга
query_X = "X"
query_Y = '"{}"'.format(search_key(dictionary, "Начальник отдела"))
query_Z = '"{}"'.format(search_key(dictionary, "Отдел маркетинга"))
query = 'to_be({X}, {Y}),part_of({X}, {Z}).'.format(X=query_X, Y=query_Y, Z=query_Z)
print(query)
query_result = list(prolog.query(query))
for answer in query_result:
    for key, value in answer.items():
        print(dictionary[str(value, 'utf-8')])
print()
print("Какие задания выполняет ООО «Созвездие»?")
# Ищем задания, которые являются частью предприятия Созвездие
query_X = "X"
query_Y = '"{}"'.format(search_key(dictionary, "Задание"))
query_Z = '"{}"'.format(search_key(dictionary, 'ООО "Созвездие"'))
query = 'to_be({X}, {Y}),part_of({X}, {Z}).'.format(X=query_X, Y=query_Y, Z=query_Z)
print(query)
query_result = list(prolog.query(query))
for answer in query_result:
    for key, value in answer.items():
        print(dictionary[str(value, 'utf-8')])
print()

print("Чем занимается Иванов И.И.?")
# Ищем сущность, являющуюся должностью, и Ивановым одновременно
query_X = '"{}"'.format(search_key(dictionary, "Иванов И.И."))
query_Y = "Y"
query_Z = '"{}"'.format(search_key(dictionary, "Должность"))
query = 'to_be({X}, {Y}), to_be({Y}, {Z}).'.format(X=query_X, Y=query_Y, Z=query_Z)
print(query)
query_result = list(prolog.query(query))
for answer in query_result:
    for key, value in answer.items():
        print(dictionary[str(value, 'utf-8')])
print()

print("Какие сроки выполнения заданы для разработки Интернет - браузера?")
# Ищем сущность, являющуюся сроком, и частью браузера
query_X = "X"
query_Y = '"{}"'.format(search_key(dictionary, "Браузер"))
query_Z = '"{}"'.format(search_key(dictionary, "Срок выполнения"))
query = 'part_of({X}, {Y}), to_be({X}, {Z}).'.format(X=query_X, Y=query_Y, Z=query_Z)
print(query)
query_result = list(prolog.query(query))
for answer in query_result:
    for key, value in answer.items():
        print(dictionary[str(value, 'utf-8')])
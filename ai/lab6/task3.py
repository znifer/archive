from pyswip import Prolog

from service.search_key import search_key
import knowledge.dictionary3 as dct
prolog = Prolog()
prolog.consult("knowledge/task3.pl")


def to_swi_param(param):
    for key, val in dct.dictionary.items():
        if val.lower() == param.lower():
            return key
    return None


def print_result(query_result):
    if query_result is not None:
        for answer in query_result:
            for key, value in answer.items():
                print(dct.dictionary[str(value, 'utf-8')])
        print()


def parse(msg):
    curr_client = ""
    curr_seller = ""

    for client in dct.clients:
        if msg.__contains__(client):
            curr_client = client

    for seller in dct.sellers:
        if msg.__contains__(seller):
            curr_seller = seller
    if msg.__contains__("машина"):

        if curr_client != "":
            curr_client = to_swi_param(curr_client)
            query = "part_of(X, \"{}\")".format(curr_client)
            return list(prolog.query(query))
        print("Вопросы у вас странные какие то. Давайте еще раз попробуем?")

    if msg.__contains__("купил") and not msg.__contains__("Кто"):

        if curr_client != "":
            curr_client = to_swi_param(curr_client + " купил")
            query = "part_of(X, \"{}\")".format(curr_client)
            return list(prolog.query(query))[:3]
        print("Вопросы у вас странные какие то. Давайте еще раз попробуем?")
    
    if msg.__contains__("продал"):
        if curr_seller != "":
            curr_seller = to_swi_param(curr_seller)
            query = "part_of(\"{}\", Y), part_of(X, Y).".format(curr_seller)

            l = list(prolog.query(query))
            res = []
            for el in l:
                if str(el["X"]) != "b'{}'".format(curr_seller):
                    res.append({"X": el["X"]})
            return res
        print("Вопросы у вас странные какие то. Давайте еще раз попробуем?")

    if msg.__contains__("Кто купил"):
        curr_product = ""
        for product in dct.products:
            if msg.__contains__(product):
                curr_product = product

        if curr_product != "":
            curr_product = to_swi_param(curr_product)
            query = "part_of(\"{}\", X)".format(curr_product)
            return list(prolog.query(query))
        print("Вопросы у вас странные какие то. Давайте еще раз попробуем?")
    print("Не понял. Можно на русском?")

print("Задавайте ваши вопросы! Если не понравится - выходить на кнопку 0")
inp = ""
while (inp != "0"):
    inp = input()
    print_result(parse(inp))
print("Ну и не очень то и хотелось...")

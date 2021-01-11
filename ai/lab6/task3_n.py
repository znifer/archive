from pyswip import Prolog

from service.search_key import search_key
import knowledge.dictionary3_n as dct
prolog = Prolog()
prolog.consult("knowledge/task3_n.pl")


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
    msg = msg.lower()

    cur_project = ""
    for pr in dct.projects:
        if pr.lower() in msg:
            cur_project = pr

    cur_emp = ""
    for emp in dct.emps:
        if emp.lower() in msg:
            cur_emp = emp

    cur_lang = ""
    for lang in dct.langs:
        if lang.lower() in msg:
            cur_lang = lang

    print(cur_lang)

    if "как дела на проекте" in msg:
        cur_project = to_swi_param(cur_project)
        query = "part_of(X, \"{}\").".format(cur_project)
        return list(prolog.query(query))

    if "какие сроки сдачи" in msg:
        cur_emp = to_swi_param(cur_emp)
        query = "part_of(X, Y), to_be(X, \"deadline\"), part_of(\"{}\", Y).".format(
            cur_emp)
        return list(prolog.query(query))

    if ("над каким проектом работает") in msg:
        cur_emp = to_swi_param(cur_emp)
        query = "part_of(\"{}\", X).".format(cur_emp)
        return list(prolog.query(query))

    if "на языке" in msg:
        cur_lang = to_swi_param(cur_lang)
        query = "part_of(\"{}\", X).".format(cur_lang)
        return list(prolog.query(query))

    print("Не понял. Можно на русском?")


print_result(parse("Какие сроки сдачи у Петрова?"))
print_result(parse("Как дела на проекте Космическая катапульта?"))
print_result(parse("Над каким проектом работает Сидоров?"))
print_result(parse("Какой проект написан на языке java? м сука?"))


exit(0)


print("Вопросы?")
inp = input()
print_result(parse(inp))
while (inp != "0"):
    inp = input()
    print_result(parse(inp))
print("Ну и не очень то и хотелось...")

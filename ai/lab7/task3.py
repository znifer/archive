from task3_frames import *

studwords = ["Балабанов", "Быков", "Звягинцев"]
teachwords = ["Иванов", "Петров"]


def search(where, what, label):
    res = []
    for item in where:
        if str(item.get_value(label)) == what:
            res.append(item)
    return res


def print_marks(list):
    for el in list:
        print("Оценку {}".format(el.mark.__str__()))


def print_students(list):
    for el in list:
        print("Студенту с фамилией {}".format(el.student.__str__()))


def print_teachers(list):
    for el in list:
        print("Преподаватель с фамилией {}".format(el.teacher.__str__()))


def parse(str, teachers, students, gets):
    words = str.split(" ")
    cur_student = None
    cur_teacher = None
    cur_mark = None
    search_pos = [True, True, True]

    for word in words:
        if word.__contains__("?"):
            word = word[:len(word) - 1]

        for sw in studwords:
            if word.startswith(sw):
                cur_student = sw
                search_pos[0] = False

        for tw in teachwords:
            if word.startswith(tw):
                cur_teacher = tw
                search_pos[1] = False

        if word.isnumeric():
            cur_mark = int(word)
            search_pos[2] = False

    if not search_pos[0] and not search_pos[1]:
        s1 = search(gets, cur_teacher, "Преподаватель")
        s2 = search(gets, cur_student, "Студент")
        res = list(set(s1) & set(s2))
        print_marks(res)
        return

    if not search_pos[0] and not search_pos[2]:
        s1 = search(gets, "{}".format(cur_mark), "Оценка")
        s2 = search(gets, cur_student, "Студент")
        res = list(set(s1) & set(s2))
        print_teachers(res)
        return

    if not search_pos[1] and not search_pos[2]:
        s1 = search(gets, cur_teacher, "Преподаватель")
        s2 = search(gets, "{}".format(cur_mark), "Оценка")
        res = list(set(s1) & set(s2))
        print_students(res)
        return

    if not search_pos[0]:
        res = search(gets, cur_student, "Студент")
        print_marks(res)

    if not search_pos[1]:
        res = search(gets, cur_teacher, "Преподаватель")
        print_marks(res)


teachers = [Teacher() for _ in range(2)]
teachers[0].set_data("Иванов")
teachers[1].set_data("Петров")

students = [Student() for _ in range(3)]
students[0].set_data("Балабанов")
students[1].set_data("Быков")
students[2].set_data("Звягинцев")

marks = [Mark() for _ in range(4)]
marks[0].set_data(2)
marks[1].set_data(3)
marks[2].set_data(4)
marks[3].set_data(5)

gets = [Get() for _ in range(6)]
gets[0].set_data(teachers[0], students[0], marks[2])
gets[1].set_data(teachers[0], students[1], marks[3])
gets[2].set_data(teachers[0], students[2], marks[3])
gets[3].set_data(teachers[1], students[0], marks[2])
gets[4].set_data(teachers[1], students[1], marks[3])
gets[5].set_data(teachers[1], students[2], marks[0])

print("Какую оценку поставил Иванов Быкову?")
parse("Какую оценку поставил Иванов Быкову?", teachers, students, gets)
print("Какие оценки поставили Звягинцеву?")
parse("Какие оценки поставили Звягинцеву?", teachers, students, gets)
print("Какие оценки поставил Петров?")
parse("Какие оценки поставил Петров?", teachers, students, gets)
print("Кому Иванов поставил 5?")
parse("Кому Иванов поставил 5?", teachers, students, gets)
print("Кто поставил Балабанову 4?")
parse("Кто поставил Балабанову 4?", teachers, students, gets)

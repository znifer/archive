from Frame import Frame

class Human(Frame):
    def __init__(self):
        self.name = "Человек"


class Teacher(Human):
    def __init__(self):
        self.name = "Преподаватель"
        self.fio = ""

    def set_data(self, fio):
        self.fio = fio

    def __str__(self):
        return "{}".format(self.fio)


class Student(Human):
    def __init__(self):
        self.name = "Студент"
        self.fio = ""

    def set_data(self, fio):
        self.fio = fio

    def __str__(self):
        return "{}".format(self.fio)


class Mark(Frame):
    def __init__(self):
        self.name = "Оценка"
        self.value = 0

    def set_data(self, value):
        self.value = value

    def __str__(self):
        return "{}".format(self.value)


class Get(Frame):
    def __init__(self):
        self.name = "Получать"
        self.teacher = None
        self.student = None
        self.mark = None

        self.attrs = [
            ("mark", "Оценка"),
            ("student", "Студент"),
            ("teacher", "Преподаватель"),
        ]

    def set_data(self, teacher, student, mark):
        self.teacher = teacher
        self.student = student
        self.mark = mark

    def __str__(self):
        return "{} {} получил {}, а поставил {} {}\n".format(
            self.student.name,
            self.student.fio,
            self.mark.value,
            self.teacher.name,
            self.teacher.fio
        )

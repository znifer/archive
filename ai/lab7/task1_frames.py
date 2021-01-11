from Frame import Frame

class Journal(Frame):
    def __init__(self):
        self.name = "Журнал"
        self.target = None
        self.title = ""
        self.cost = 0
        self.pages = 0
        self.info = ""
        self.subscription = None

        self.attrs = [
            ("name", "Журнал"),
            ("target", "Целевая аудитория"),
            ("title", "Название"),
            ("cost", "Стоимость"),
            ("pages", "Количество страниц"),
            ("info", "Информация"),
            ("subscription", "Подписка"),
        ]


    def set_data(self, title, target, cost, pages, info, subscription):
        self.target = target
        self.title = title
        self.cost = cost
        self.pages = pages
        self.info = info
        self.subscription = subscription

    def __str__(self):
        return "{} {} {}".format(self.name, self.title, self.info)


class Target(Frame):
    def __init__(self):
        self.name = "Целевая аудитория"
        self.who = ""

    def set_data(self, who):
        self.who = who

    def __str__(self):
        return "{}: {}".format(self.name, self.who)

class Subscription(Frame):
    def __init__(self):
        self.name = "Подписка"
        self.available = ""

    def set_data(self, available):
        self.available = available


from Frame import Frame


class Vehicle(Frame):
    def __init__(self):
        self.name = "Транспорт"
        self.vname = ""
        self.tranporting_type = None
        self.capacity = 0
        self.weapon = None
        self.protection = None

        self.attrs = [
            ("name", ""),
            ("vname", "Наименование"),
            ("tranporting_type", "Способ передвижения"),
            ("capacity", "Вместимость"),
            ("weapon", "Вооружение"),
            ("protection", "Защита")
        ]

    def set_data(self, vname, transporting_type, capacity, weapon, protection):
        self.vname = vname
        self.tranporting_type = transporting_type
        self.capacity = capacity
        self.weapon = weapon
        self.protection = protection

    def __str__(self):
        return self.vname

class TransporingType(Frame):
    def __init__(self):
        self.name = "Способ передвижения"
        self.type = ""

    def set_data(self, type):
        self.type = type

    def __str__(self):
        return self.type

class Weapon(Frame):
    def __init__(self):
        self.name = "Вооружение"
        self.type = ""
        self.caliber = ""

    def set_data(self, type, caliber):
        self.type = type
        self.caliber = caliber

    def __str__(self):
        if self.caliber != "":
            return "{} {}".format(self.type, self.caliber)
        return self.type

class Protection(Frame):
    def __init__(self):
        self.name = "Защита"
        self.type = ""

    def set_data(self, type):
        self.type = type

    def __str__(self):
        return self.type
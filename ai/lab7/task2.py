from task2_frames import *

def search(where, what, label):
    res = []
    for item in where:
        if str(item.get_value(label)) == what:
            res.append(item)
    return res

def search_by_num(where, what, label):
    res = []
    for item in where:
        if item.get_value(label) > what:
            res.append(item)
    return res

def search_except(where, what, label):
    res = []
    for item in where:
        if not str(item.get_value(label)) == what:
            res.append(item)
    return res

transporting_types = [TransporingType() for _ in range(3)]

transporting_types[0].set_data("Гусеницы")
transporting_types[1].set_data("Вертолет")
transporting_types[2].set_data("Колеса")

weapons = [Weapon() for _ in range(4)]

weapons[0].set_data("Пушка", "100 мм")
weapons[1].set_data("Пушка", "30 мм")
weapons[2].set_data("Пулемет", "14,5 мм")
weapons[3].set_data("Нет", "")

protections = [Protection() for _ in range(3)]

protections[0].set_data("Броня")
protections[1].set_data("Сталь")
protections[2].set_data("Нет")

vehicles = [Vehicle() for _ in range(4)]

vehicles[0].set_data("БМП-3", transporting_types[0], 7, weapons[0], protections[0])
vehicles[1].set_data("Ми-24", transporting_types[1], 7, weapons[1], protections[1])
vehicles[2].set_data("БТР-50Б", transporting_types[2], 7, weapons[2], protections[0])
vehicles[3].set_data("Ми-8", transporting_types[1], 7, weapons[3], protections[2])

print("Вертолет, способный перевозить не менее 6 человек десанта над полем "
      "боя без поддержки наземных средств")
q = search(vehicles, "Вертолет", "Способ передвижения")
q = search_by_num(q, 6, "Вместимость")
q = search_except(q, "Нет", "Вооружение")
print(*q)

print("Наземное средство доставки не менее 6 десантников в тыл противника "
      "при активном противодействии бронетанковых войск противника")

q = search_by_num(vehicles, 6, "Вместимость")
q = search_except(q, "Нет", "Защита")
q = search_except(q, "Нет", "Вооружение")
print(*q)

print("Средство доставки не менее 6 человек десанта в тыл противника при наличии "
      "противодействия противника.")

q = search_by_num(vehicles, 6, "Вместимость")
q = search_except(q, "Нет", "Защита")
print(*q)

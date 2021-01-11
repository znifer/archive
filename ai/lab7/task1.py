from task1_frames import *

def search(where, what, label):
    res = []
    for item in where:
        t = item.get_value(label)
        if type(t) == type([]):
            res.append(item)
        else:
            if t == what:
                res.append(item)
    for el in res:
        print(el)
    print()

subscr = Subscription()
subscr.set_data("Да")
no_subscr = Subscription()
no_subscr.set_data("Нет")

man_target = Target()
man_target.set_data("Мужчины")
antiman_target = Target()
antiman_target.set_data("Женщины")
both = [man_target, antiman_target]

journals = [Journal() for _ in range(6)]
journals[0].set_data("Тюнинг", man_target, 140, 170, "про тюнинг", no_subscr)
journals[1].set_data("Мода", antiman_target, 90, 90, "про моду", no_subscr)
journals[2].set_data("Игры", both, 65, 60, "про игры", no_subscr)
journals[3].set_data("Рукоделие", antiman_target, 45, 50, "про рукоделие", subscr)
journals[4].set_data("Фотография", both, 100, 95, "про фотографию", subscr)
journals[5].set_data("Кино и музыка", both, 30, 30, "про кино и музыку", no_subscr)

print("Какой журнал предоставляет информацию о современных технологиях тюнинга автомобилей?")
search(journals, "про тюнинг", "Информация")
print("Какие журналы предназначены для мужчин?")
search(journals, man_target, "Целевая аудитория")
print("Какие журналы стоят 100 рублей?")
search(journals, 100, "Стоимость")
print("На какие журналы можно оформить подписку?")
search(journals, subscr, "Подписка")
print("Найти все журналы издательства")
search(journals, "Журнал", "Журнал")
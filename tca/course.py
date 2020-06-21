def f(t1, x1, x2, x3):
    z1 = not x1 and not x2
    u1 = not t1 and z1
    u2 = not t1 and x1
    u3 = x1 and not x3
    u4 = not t1 and x2
    u5 = t1 and not x3
    u6 = t1 and x1
    u7 = t1

    w1 = u3 or u5
    w2 = u1 or u6
    w3 = w1 or w2

    y1 = u2 or w1
    y2 = u7 or w3
    y3 = w2
    f = u2 or u4
    print("Триггер: {}, Выходы: {} {} {}".format(int(f), int(y1), int(y2), int(y3)))
    return f, y1, y2, y3

t1 = 0

print("Введите входы х1, х2, х3: ")
x1 = int(input('x1 = '))
x2 = int(input('x2 = '))
x3 = int(input('x3 = '))

while x1 == 0 or x1 == 1 or x2 == 0 or x2 == 1 or x3 == 0 or x3 == 1:
    t1, x1, x2, x3 = f(t1, x1, x2, x3) 
    print("Введите входы х1, х2, х3: ")
    x1 = int(input('x1 = '))
    x2 = int(input('x2 = '))
    x3 = int(input('x3 = '))

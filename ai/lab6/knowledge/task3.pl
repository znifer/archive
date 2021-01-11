is_a("sidorov", "client").
is_a("putin", "client").

is_a("moskvich 412", "car").
is_a("tavria", "car").

is_a("baton", "product").
is_a("benzin", "product").

is_a("ivanov", "seller").
is_a("petrov", "seller").

is_a("1", "amount").
is_a("2", "amount").
is_a("3", "amount").

is_a("100rub", "cost").
is_a("200rub", "cost").
is_a("300rub", "cost").

is_a("putin`s products", "sell").
is_a("sidorov`s products", "sell").

to_be(X,Y) :- is_a(X,Y).
to_be(X,Y) :- is_a(Z,Y),to_be(X,Z).

part_of("moskvich 412", "putin").
part_of("tavria", "sidorov").

part_of("baton", "putin`s products").
part_of("1", "putin`s products").
part_of("100rub", "putin`s products").
part_of("ivanov", "putin`s products").
part_of("putin", "putin`s products").

part_of("benzin", "sidorov`s products").
part_of("3", "sidorov`s products").
part_of("200rub", "sidorov`s products").
part_of("petrov", "sidorov`s products").
part_of("sidorov", "sidorov`s products").

part_of(X,Y) :- to_be(Y,Z),part_of(X,Z).
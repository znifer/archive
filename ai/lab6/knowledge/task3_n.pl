is_a("10.10.2021", "deadline").
is_a("11.11.2021", "deadline").

is_a("planing", "stage").
is_a("developing", "stage").
is_a("supporting", "stage").

is_a("petrov", "employee").
is_a("sidorov", "employee").

is_a("other apps", "subj").
is_a("mobile apps", "subj").

is_a("space catapult", "name").
is_a("mobile app for migrants", "name").

is_a("java", "lang").
is_a("python", "lang").
is_a("js", "lang").

to_be(X,Y) :- is_a(X,Y).
to_be(X,Y) :- is_a(Z,Y),to_be(X,Z).

part_of("10.10.2021", "space catapult").
part_of("planing", "space catapult").
part_of("petrov", "space catapult").
part_of("other apps", "space catapult").
part_of("java", "space catapult").

part_of("11.11.2021", "mobile app for migrants").
part_of("developing", "mobile app for migrants").
part_of("sidorov", "mobile app for migrants").
part_of("js", "mobile app for migrants").
part_of("mobile app", "mobile app for migrants").

part_of(X,Y) :- to_be(Y,Z),part_of(X,Z).
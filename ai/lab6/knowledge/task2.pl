is_a("coding", "bureau").
is_a("tasking", "bureau").
is_a("supporting", "bureau").

is_a("developing", "department").
is_a("marketing", "department").

is_a("director", "position").
is_a("department director", "position").
is_a("bureau director", "position").

is_a("ivanov", "employee").
is_a("petrov", "employee").
is_a("sidorov", "employee").
is_a("kernigan", "employee").
is_a("gates", "employee").
is_a("yamada", "employee").

is_a("marketing step", "step").
is_a("coding step", "step").
is_a("tasking step", "step").
is_a("supporting step", "step").

is_a("ivanov", "director").
is_a("petrov", "department director").
is_a("sidorov", "bureau director").
is_a("kernigan", "bureau director").
is_a("gates", "bureau director").
is_a("yamada", "department director").

is_a("step 1", "tasking step").
is_a("step 2", "coding step").
is_a("step 3", "marketing step").
is_a("step 4", "supporting step").

is_a("browser", "task").
is_a("editor", "task").

is_a("OOO SOZVEZDIE", "company").

is_a("06.01.2021", "date").
is_a("31.12.2020", "date").

to_be(X,Y) :- is_a(X,Y).
to_be(X,Y) :- is_a(Z,Y),to_be(X,Z).

part_of("ivanov", "company").
part_of("petrov", "company").
part_of("sidorov", "company").
part_of("kernigan", "company").
part_of("gates", "company").
part_of("yamada", "company").

part_of("petrov", "developing").
part_of("sidorov", "tasking").
part_of("kernigan", "coding").
part_of("yamada", "marketing").

part_of("sidorov", "step 1").
part_of("kernigan", "step 2").
part_of("yamada", "step 3").
part_of("gates", "step 4").

part_of("browser", "OOO SOZVEZDIE").
part_of("editor", "OOO SOZVEZDIE").

part_of("step 2", "browser").
part_of("step 3", "editor").

part_of("06.01.2021", "browser").
part_of("31.12.2020", "editor").

part_of(X,Y) :- to_be(Y,Z),part_of(X,Z).
a_is_b("autotuning", "label").
a_is_b("fashion", "label").
a_is_b("games", "label").
a_is_b("craft", "label").
a_is_b("photo", "label").
a_is_b("movies", "label").

a_is_b("man", "target").
a_is_b("woman", "target").

a_is_b("140rub", "price").
a_is_b("90rub", "price").
a_is_b("65rub", "price").
a_is_b("45rub", "price").
a_is_b("100rub", "price").
a_is_b("30rub", "price").

a_is_b("170", "pages").
a_is_b("90", "pages").
a_is_b("60", "pages").
a_is_b("50", "pages").
a_is_b("95", "pages").
a_is_b("30", "pages").

a_is_b("autotuning_info", "info").
a_is_b("fashion_info", "info").
a_is_b("games_info", "info").
a_is_b("craft_info", "info").
a_is_b("photo_info", "info").
a_is_b("movies_info", "info").

a_is_b("No", "Subscription").
a_is_b("Yes", "Subscription").

part_of("man", "autotuning").
part_of("140rub", "autotuning").
part_of("170", "autotuning").
part_of("autotuning_info", "autotuning").
part_of("No", "autotuning").

part_of("woman", "fashion").
part_of("90rub", "fashion").
part_of("90", "fashion").
part_of("fashion_info", "fashion").
part_of("Yes", "fashion").

part_of("woman", "games").
part_of("man", "games").
part_of("65rub", "games").
part_of("60", "games").
part_of("games_info", "games").
part_of("No", "games").

part_of("woman", "craft").
part_of("45rub", "craft").
part_of("50", "craft").
part_of("craft_info", "craft").
part_of("No", "craft").

part_of("woman", "photo").
part_of("man", "photo").
part_of("100rub", "photo").
part_of("95", "photo").
part_of("photo_info", "photo").
part_of("Yes", "photo").

part_of("woman", "movies").
part_of("man", "movies").
part_of("30rub", "movies").
part_of("30", "movies").
part_of("movies_info", "movies").
part_of("Yes", "movies").

is_a(X,Y) :- a_is_b(X,Y).
is_part(X,Y) :- part_of(X,Y).

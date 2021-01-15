package ru.bstu.iitus.vt41.kid.cw.repositories;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;
import ru.bstu.iitus.vt41.kid.cw.models.Genre;

@Repository
public interface GenreRepository extends JpaRepository<Genre, Long> {

}

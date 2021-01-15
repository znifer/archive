package ru.bstu.iitus.povtas.vt41.cars.repositories;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;
import ru.bstu.iitus.povtas.vt41.cars.models.Review;

@Repository
public interface ReviewRepository extends JpaRepository<Review, Long> {

}

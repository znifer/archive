package ru.bstu.iitus.povtas.vt41.cars.repositories;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;
import ru.bstu.iitus.povtas.vt41.cars.models.Dealer;

@Repository
public interface DealerRepository extends JpaRepository<Dealer, Long> {

}

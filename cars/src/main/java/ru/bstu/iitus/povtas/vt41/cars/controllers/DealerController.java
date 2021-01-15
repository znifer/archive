package ru.bstu.iitus.povtas.vt41.cars.controllers;

import com.fasterxml.jackson.annotation.OptBoolean;
import org.springframework.web.bind.annotation.*;
import ru.bstu.iitus.povtas.vt41.cars.models.Dealer;
import ru.bstu.iitus.povtas.vt41.cars.repositories.DealerRepository;

import java.util.List;
import java.util.Optional;

@RestController
public class DealerController {
    private DealerRepository repo;

    DealerController(DealerRepository repo) {
        this.repo = repo;
    }
    @GetMapping("/dealers")
    List<Dealer> getAll() {
        return repo.findAll();
    }
    @GetMapping("/dealers/{id}")
    Optional<Dealer> getOne(@PathVariable Long id) {
        return repo.findById(id);
    }
    @PostMapping("/dealers")
    Dealer newDealer(@RequestBody Dealer dealer) {
        return repo.save(dealer);
    }
}

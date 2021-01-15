package ru.bstu.iitus.povtas.vt41.cars.controllers;

import org.springframework.web.bind.annotation.*;
import ru.bstu.iitus.povtas.vt41.cars.models.Auto;
import ru.bstu.iitus.povtas.vt41.cars.repositories.AutoRepository;

import java.util.List;
import java.util.Optional;

@RestController
public class AutoController {
    private final AutoRepository repo;

    public AutoController(AutoRepository repo) {
        this.repo = repo;
    }
    @GetMapping("/autos")
    List<Auto> getAll(@RequestParam(required = false) String name) {
        if (name == null){
            return repo.findAll();
        }
        return repo.findAutoByName(name);
    }

    @GetMapping("/autos/{id}")
    Optional<Auto> getOne(@PathVariable Long id) {
        return repo.findById(id);
    }
    @PostMapping("/autos")
    Auto newAuto(@RequestBody Auto auto) {
        return repo.save(auto);
    }
}

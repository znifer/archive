package ru.bstu.iitus.povtas.vt41.cars.controllers;

import org.springframework.web.bind.annotation.*;
import ru.bstu.iitus.povtas.vt41.cars.models.Manufacturer;
import ru.bstu.iitus.povtas.vt41.cars.repositories.ManufacturerRepository;

import java.lang.management.ManagementFactory;
import java.util.List;
import java.util.Optional;

@RestController
public class ManufacturerController {
    private ManufacturerRepository repo;

    ManufacturerController(ManufacturerRepository repo) {
        this.repo = repo;
    }
    @GetMapping("/manufacturers")
    List<Manufacturer> getAll() {
        return repo.findAll();
    }
    @GetMapping("/manufacturers/{id}")
    Optional<Manufacturer> getOne(@PathVariable Long id) {
        return repo.findById(id);
    }
    @PostMapping("/manufacturers")
    Manufacturer newManufacturer(@RequestBody Manufacturer manufacturer) {
        return repo.save(manufacturer);
    }
}

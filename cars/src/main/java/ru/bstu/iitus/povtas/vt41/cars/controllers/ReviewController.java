package ru.bstu.iitus.povtas.vt41.cars.controllers;

import org.springframework.web.bind.annotation.*;
import ru.bstu.iitus.povtas.vt41.cars.models.Manufacturer;
import ru.bstu.iitus.povtas.vt41.cars.models.Review;
import ru.bstu.iitus.povtas.vt41.cars.repositories.ReviewRepository;

import java.util.List;
import java.util.Optional;

@RestController
public class ReviewController {
    private ReviewRepository repo;

    ReviewController(ReviewRepository repo) {
        this.repo = repo;
    }
    @GetMapping("/reviews")
    List<Review> getAll() {
        return repo.findAll();
    }
    @GetMapping("/reviews/{id}")
    Optional<Review> getOne(@PathVariable Long id) {
        return repo.findById(id);
    }
    @PostMapping("/reviews")
    Review newReview(@RequestBody Review review) {
        return repo.save(review);
    }
}

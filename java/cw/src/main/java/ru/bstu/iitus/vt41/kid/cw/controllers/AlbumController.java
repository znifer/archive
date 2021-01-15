package ru.bstu.iitus.vt41.kid.cw.controllers;

import org.springframework.web.bind.annotation.*;
import ru.bstu.iitus.vt41.kid.cw.models.Album;
import ru.bstu.iitus.vt41.kid.cw.repositories.AlbumRepository;

import java.util.List;
import java.util.Optional;

@CrossOrigin(origins = "*")
@RestController
public class AlbumController {
    private final AlbumRepository repository;

    AlbumController(AlbumRepository repository) {
        this.repository = repository;
    }


    @GetMapping("/albums")
    List<Album> all(@RequestParam(required = false) String title) {
        if (title == null) {
            return repository.findAll();
        }
        return  repository.findAlbumByTitle(title);
    }

    @PostMapping("/albums")
    Album newAlbum(@RequestBody Album newAlbum){
        return repository.save(newAlbum);
    }

    @GetMapping("/albums/{id}")
    Optional<Album> one(@PathVariable Long id){
        return repository.findById(id);
    }
}

package ru.bstu.iitus.povtas.vt41.cars.models;

import lombok.Data;

import javax.persistence.*;
import java.util.List;

@Data
@Entity
public class Dealer {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;
    private String name;
    private String address;
    @OneToMany
    List<Auto> autos;

    Dealer () {}
}

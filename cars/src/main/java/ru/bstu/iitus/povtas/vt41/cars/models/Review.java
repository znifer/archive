package ru.bstu.iitus.povtas.vt41.cars.models;

import lombok.Data;

import javax.persistence.*;

@Data
@Entity
public class Review {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;
    private String text;

    @OneToOne
    private Auto auto;

    Review () {}
}

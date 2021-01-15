package ru.bstu.iitus.povtas.vt41.cars.models;

import lombok.Data;

import javax.persistence.*;

@Data
@Entity
public class Auto {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;
    private String name;
    private String type;
    private String equipment;
    private String price;
    private String color;
    private String engine;

    @OneToOne
    Manufacturer manufacturer;

    Auto () {}

}

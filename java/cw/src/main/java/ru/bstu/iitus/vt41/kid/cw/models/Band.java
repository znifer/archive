package ru.bstu.iitus.vt41.kid.cw.models;

import lombok.*;

import javax.persistence.*;
import java.time.LocalDate;
import java.util.List;

@Getter
@Setter
@EqualsAndHashCode
@ToString
@Entity
@AllArgsConstructor
public final class Band {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;
    private String name;
    private String description;
    private LocalDate created;
    private LocalDate ended;
    private String logo;
    private Integer rating;


    public Band() {

    }
}
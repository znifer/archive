package ru.bstu.iitus.vt41.kid.cw.models;

import lombok.*;

import javax.persistence.*;

@Getter
@Setter
@EqualsAndHashCode
@ToString
@Entity
@AllArgsConstructor
public final class Track {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    @Column(name = "track_id")
    private long id;
    private String title;
    private String duration;
    private Integer rating;

    @ManyToOne
    @JoinColumn(name="album", referencedColumnName = "album_id")
    private Album album;

    public Track() {

    }
}

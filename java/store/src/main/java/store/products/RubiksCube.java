package store.products;

import lombok.ToString;
import store.utils.Inputters;

import java.util.Scanner;

@ToString(callSuper = true, includeFieldNames = true)
public class RubiksCube extends Toy {
    public void init(Scanner sc) {
        String newName = Inputters.getString(sc);
        while (!newName.matches("^(Кубик )(?:[a-zA-Zа-яА-Я0-9]+)*$")) {
            System.out.println("Немедленно прекратите и введите нормально! Название продукта должно начинаться с 'Кубик ...'");
            newName = Inputters.getString(sc);
        }
        setName(newName);
        System.out.println("Введите стоимость");
        setCost(Inputters.getInteger(sc));
    }
}
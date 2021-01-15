package store.products;

import lombok.ToString;
import store.utils.Inputters;

import java.util.Scanner;

@ToString(callSuper = true, includeFieldNames = true)
public class Cheese extends MilkProduct {
    public void init(Scanner sc) {
        System.out.println("Введите наименование");
        String newName = Inputters.getString(sc);
        while (!newName.matches("^(Сыр )(?:[a-zA-Zа-яА-Я0-9]+)*$")) {
            System.out.println("Немедленно прекратите и введите нормально! Название продукта должно начинаться с 'Сыр ...'");
            newName = Inputters.getString(sc);
        }
        setName(newName);
        System.out.println("Введите стоимость");
        setCost(Inputters.getInteger(sc));
        System.out.println("Введите вес продукта");
        setWeight(Inputters.getInteger(sc));
    }
}
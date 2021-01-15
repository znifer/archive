package store.products;

import lombok.Getter;
import lombok.Setter;
import lombok.ToString;

import java.util.Scanner;

@Getter
@Setter
@ToString(includeFieldNames = true)
public abstract class Product implements Comparable<Product> {
    private String name;
    private Integer cost;

    public abstract void init(Scanner sc);      // считывание параметров с консоли

    public abstract boolean canBuy(int money);  // определяет, можно ли купить товар за имеющуюся сумму

    public int compareTo(Product p) {
        Integer cost1 = this.getCost();
        Integer cost2 = p.getCost();
        if (cost1 == cost2) return 0;
        if (cost1 > cost2)
            return 1;
        return -1;
    }
}
package store.products;

import lombok.Getter;
import lombok.Setter;
import lombok.ToString;

@Getter
@Setter
@ToString(callSuper = true, includeFieldNames = true)
public abstract class MilkProduct extends Product {
    private Integer weight;

    public boolean canBuy(int money) {
        return money > getCost() * getWeight();
    }
}
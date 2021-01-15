package store.products;

import lombok.ToString;

@ToString(callSuper = true, includeFieldNames = true)
public abstract class Tech extends Product {
    public boolean canBuy(int money) {
        return money > getCost();
    }

}
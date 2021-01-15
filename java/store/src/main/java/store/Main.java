package store;

import store.products.Product;
import store.utils.InputException;
import store.utils.Inputters;
import store.utils.ProductUtilities;

import java.util.ArrayList;
import java.util.Scanner;


public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        ArrayList<Product> products = new ArrayList<>();

        System.out.println("Введите количество товаров:");
        int n = Inputters.getInteger(sc);
        for (int i = 0; i < n; i++) {
            Product p = null;
            try {
                p = ProductUtilities.inputProduct(sc);
            } catch (InputException ex) {
                System.out.println(ex + " Повторите ввод.");

            } finally {
                products.add(p);
            }
        }
        System.out.println("Щас найдем самый дешевый товар!");
        ProductUtilities.printCheapest(products);
    }
}


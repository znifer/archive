package store.utils;

import lombok.experimental.UtilityClass;

import java.util.InputMismatchException;
import java.util.Scanner;

@UtilityClass
public class Inputters {
    public static String getString(Scanner sc) {
        String result = "";
        while (result == "") {
            try {
                result = sc.nextLine();
            } catch (InputMismatchException ex) {
                System.out.println("Вы как-то не так вводите, прекратите и введите нормально!");
            }
        }
        return result;
    }

    public static Integer getInteger(Scanner sc) {
        int result = -1;
        while (result == -1) {
            try {
                result = sc.nextInt();
            } catch (InputMismatchException ex) {
                System.out.println("Вы как-то не так вводите, прекратите и введите нормально!");
                sc.nextLine();
            }
        }
        return result;
    }
}

package store.utils;

import java.io.IOException;

public class InputException extends IOException {
    public InputException(String errorMessage) {
        super(errorMessage);
    }
}

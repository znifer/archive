package com.example.lab3;

import java.util.ArrayList;
import java.util.Arrays;

public class QuestionContent {
    private static ArrayList<Question> items = new ArrayList<Question>(Arrays.asList(
            new Question(1, R.string.label1, R.string.text1, R.string.ac1, R.drawable.pic1, R.string.fulltext1),
            new Question(2, R.string.label2, R.string.text2, R.string.ac2, R.drawable.pic2, R.string.fulltext2),
            new Question(3, R.string.label3, R.string.text3, R.string.ac3, R.drawable.pic3, R.string.fulltext3),
            new Question(4, R.string.label4, R.string.text4, R.string.ac4, R.drawable.pic4, R.string.fulltext4),
            new Question(5, R.string.label5, R.string.text5, R.string.ac5, R.drawable.pic5, R.string.fulltext5),
            new Question(6, R.string.label6, R.string.text6, R.string.ac6, R.drawable.pic6, R.string.fulltext6),
            new Question(7, R.string.label7, R.string.text7, R.string.ac7, R.drawable.pic7, R.string.fulltext7),
            new Question(8, R.string.label8, R.string.text8, R.string.ac8, R.drawable.pic8, R.string.fulltext8),
            new Question(9, R.string.label9, R.string.text9, R.string.ac9, R.drawable.pic9, R.string.fulltext9),
            new Question(10, R.string.label10, R.string.text10, R.string.ac10, R.drawable.pic10, R.string.fulltext10))
    );

    public static ArrayList<Question> getContent() {
        return items;
    }

    public static Question getElement(int id) {return items.get(id);}
}

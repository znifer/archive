package com.example.lab2;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.RecyclerView;

import android.os.Bundle;
import android.util.Log;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;
import java.util.List;
import java.util.ListIterator;

public class MainActivity extends AppCompatActivity {

    private List<Question> questionList = new ArrayList<>();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        loadQuestions();
        RecyclerView rv = (RecyclerView) findViewById(R.id.recyclerview);
        QuestionAdapter adapter = new QuestionAdapter(this, questionList);
        rv.setAdapter(adapter);
    }

    private void loadQuestions() {
        Log.w("loading data", "loading data");
        questionList.add(new Question(R.string.label1, R.string.text1, R.string.ac1, R.drawable.pic1));
        questionList.add(new Question(R.string.label2, R.string.text2, R.string.ac2, R.drawable.pic2));
        questionList.add(new Question(R.string.label3, R.string.text3, R.string.ac3, R.drawable.pic3));
        questionList.add(new Question(R.string.label4, R.string.text4, R.string.ac4, R.drawable.pic4));
        questionList.add(new Question(R.string.label5, R.string.text5, R.string.ac5, R.drawable.pic5));
        questionList.add(new Question(R.string.label6, R.string.text6, R.string.ac6, R.drawable.pic6));
        questionList.add(new Question(R.string.label7, R.string.text7, R.string.ac7, R.drawable.pic7));
        questionList.add(new Question(R.string.label8, R.string.text8, R.string.ac8, R.drawable.pic8));
        questionList.add(new Question(R.string.label9, R.string.text9, R.string.ac9, R.drawable.pic9));
        questionList.add(new Question(R.string.label10, R.string.text10, R.string.ac10, R.drawable.pic10));
    }
}
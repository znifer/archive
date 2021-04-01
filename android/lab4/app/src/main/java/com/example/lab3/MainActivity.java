package com.example.lab3;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;

public class MainActivity extends AppCompatActivity implements QuestionAdapter.OnClickListener{
    private QuestionAdapter.OnClickListener listener;
    QuestionList list;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        listener = new QuestionAdapter.OnClickListener() {
            @Override
            public void onClick(int position) {
                QuestionFragment f = new QuestionFragment(position);
                getSupportFragmentManager().beginTransaction().replace(R.id.question_list_container, f).addToBackStack(null).commit();
            }
        };

        list = new QuestionList(listener);
        getSupportFragmentManager().beginTransaction().replace(R.id.question_list_container, list).commit();
        setContentView(R.layout.activity_main);
    }

    @Override
    public void onClick(int position) {}
}
package com.example.lab3;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;

import java.util.zip.Inflater;

public class MainActivity extends AppCompatActivity implements QuestionAdapter.OnClickListener{
    private QuestionAdapter.OnClickListener listener;
    QuestionList list;
    QuestionFragment f;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        listener = new QuestionAdapter.OnClickListener() {
            @Override
            public void onClick(int position) {
                f = new QuestionFragment(position);
                getSupportFragmentManager().beginTransaction().replace(R.id.question_list_container, f).addToBackStack(null).commit();
            }
        };

        if (savedInstanceState == null) {
            list = new QuestionList(listener);
            getSupportFragmentManager().beginTransaction().replace(R.id.question_list_container, list).commit();
        }




        setContentView(R.layout.activity_main);
    }

    @Override
    public void onClick(int position) {}
}
package com.example.lab3;

import android.content.Context;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;


public class QuestionFragment extends Fragment {
    private int id;
    private Question q;

    public QuestionFragment () {
        this.id = 1;
        this.q = QuestionContent.getElement(id);
    }

    public QuestionFragment(int id) {
        this.id = id;
        this.q = QuestionContent.getElement(id);
    }

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_layout, container, false);
        TextView title = view.findViewById(R.id.title);
        ImageView imageView = (ImageView)view.findViewById(R.id.image);
        TextView textView = (TextView) view.findViewById(R.id.text);
        TextView answersCountView = (TextView) view.findViewById(R.id.answers_count);
        TextView fulltextView = (TextView) view.findViewById(R.id.text_full);

        imageView.setImageResource(q.getImage());
        title.setText(q.getTitle());
        textView.setText(q.getText());
        answersCountView.setText(q.getAnswers_count());
        fulltextView.setText(q.getFull_text());
        return view;
    }
}
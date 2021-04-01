package com.example.lab3;

import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.recyclerview.widget.RecyclerView;

public class QuestionList extends Fragment {

    QuestionAdapter.OnClickListener listener;

    private RecyclerView recyclerView;

    public QuestionList () {}

    public QuestionList(QuestionAdapter.OnClickListener listener) {
        this.listener = listener;
    }

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.list_fragment_layout, container, false);
        recyclerView = view.findViewById(R.id.recyclerview);
        QuestionAdapter adapter = new QuestionAdapter(QuestionContent.getContent(), listener);
        recyclerView.setAdapter(adapter);
        return view;
    }
}

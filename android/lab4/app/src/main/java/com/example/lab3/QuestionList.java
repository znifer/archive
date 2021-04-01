package com.example.lab3;

import android.content.Context;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.recyclerview.widget.RecyclerView;

import com.fasterxml.jackson.databind.ObjectMapper;

import org.jetbrains.annotations.NotNull;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.Response;

public class QuestionList extends Fragment {
    QuestionAdapter.OnClickListener listener;
    private RecyclerView recyclerView;
    private OkHttpClient client;
    QuestionAdapter adapter;
    ArrayList<Question> items;

    public QuestionList(QuestionAdapter.OnClickListener listener) {
        this.listener = listener;
        this.client = new OkHttpClient();
        try {
            this.run("http://10.0.2.2:8000/all");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.list_fragment_layout, container, false);
        recyclerView = view.findViewById(R.id.recyclerview);
        adapter = new QuestionAdapter(items, listener);
        recyclerView.setAdapter(adapter);
        return view;
    }

    public void run(String url) throws IOException {
        Request r = new Request.Builder().url(url).build();

        client.newCall(r).enqueue(new Callback() {
            @Override
            public void onFailure(@NotNull Call call, @NotNull IOException e) {
                e.printStackTrace();
            }

            @Override
            public void onResponse(@NotNull Call call, @NotNull Response response) throws IOException {
                ObjectMapper mapper = new ObjectMapper();
                String res = response.body().string();
                items = mapper.readValue(res, mapper.getTypeFactory().constructCollectionType(List.class, Question.class));
                adapter = new QuestionAdapter(items, listener);
                recyclerView.setAdapter(adapter);
            }
        });
    }

}

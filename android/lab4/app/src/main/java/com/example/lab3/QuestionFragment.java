package com.example.lab3;

import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import com.fasterxml.jackson.databind.ObjectMapper;

import org.jetbrains.annotations.NotNull;

import java.io.IOException;
import java.util.Map;

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.Response;


public class QuestionFragment extends Fragment {
    private int id;
    private Question q;
    private OkHttpClient client;

    public QuestionFragment () {
        this.id = 0;
    }

    public QuestionFragment(int id){
        this.id = id;
        this.client = new OkHttpClient();
        q = new Question();
    }

    public void runAsync(String url, View view) throws IOException {
        Request r = new Request.Builder().url(url).build();

        client.newCall(r).enqueue(new Callback() {
            @Override
            public void onFailure(@NotNull Call call, @NotNull IOException e) {
                e.printStackTrace();
            }

            @Override
            public void onResponse(@NotNull Call call, @NotNull Response response) throws IOException {
                ObjectMapper mapper = new ObjectMapper();
                q = mapper.readValue(response.body().string(), Question.class);

                TextView title = view.findViewById(R.id.title);
                ImageView imageView = (ImageView)view.findViewById(R.id.image);
                TextView textView = (TextView) view.findViewById(R.id.text);
                TextView answersCountView = (TextView) view.findViewById(R.id.answers_count);
                TextView fulltextView = (TextView) view.findViewById(R.id.text_full);

                new ImageLoader(imageView).execute(q.getImage());
                title.setText(q.getTitle());
                textView.setText(q.getText());
                answersCountView.setText(q.getAnswers_count());
                fulltextView.setText(q.getFull_text());
            }
        });
    }


    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_layout, container, false);

        try {
            this.runAsync("http://10.0.2.2:8000/item/"+id, view);
        } catch (IOException e) {
            e.printStackTrace();
        }
        return view;
    }
}
package com.example.lab3;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import java.util.List;

public class QuestionAdapter extends RecyclerView.Adapter<QuestionAdapter.ViewHolder> {

    private final LayoutInflater inflater;
    private final List<Question> questions;

    QuestionAdapter(Context context, List<Question> questions) {
        this.questions = questions;
        this.inflater = LayoutInflater.from(context);
    }

    @NonNull
    @Override
    public ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = inflater.inflate(R.layout.recyclerview_item, parent, false);
        return  new ViewHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull ViewHolder holder, int position) {
        Question q = questions.get(position);
        holder.imageView.setImageResource(q.getImage());
        holder.titleView.setText(q.getTitle());
        holder.textView.setText(q.getText());
        holder.answersCountView.setText(q.getAnswers_count());
    }

    @Override
    public int getItemCount() {
        return questions.size();
    }

    public static class ViewHolder extends RecyclerView.ViewHolder {
        final ImageView imageView;
        final TextView titleView, textView, answersCountView;
        ViewHolder(View view){
            super(view);
            imageView = (ImageView)view.findViewById(R.id.image);
            titleView = (TextView) view.findViewById(R.id.title);
            textView = (TextView) view.findViewById(R.id.text);
            answersCountView = (TextView) view.findViewById(R.id.answers_count);
        }
    }
}

package com.example.lab3;

import android.net.Uri;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.RecyclerView;

import java.util.List;

public class QuestionAdapter extends RecyclerView.Adapter<QuestionAdapter.ViewHolder> {

    private final List<Question> questions;
    private OnClickListener listener;

    QuestionAdapter(List<Question> questions, OnClickListener listener) {
        this.questions = questions;
        this.listener = listener;
    }

    @NonNull
    @Override
    public ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.recyclerview_item, null);
        return new ViewHolder(view, listener);
    }

    @Override
    public void onBindViewHolder(@NonNull ViewHolder holder, int position) {
        Question q = questions.get(position);
        holder.titleView.setText(q.getTitle());
        holder.textView.setText(q.getText());
        holder.answersCountView.setText(q.getAnswers_count());
        new ImageLoader(holder.imageView).execute(q.getImage());
    }

    @Override
    public int getItemCount() {
        if (questions == null) return 0;
        return questions.size();
    }

    public static class ViewHolder extends RecyclerView.ViewHolder {
        final ImageView imageView;
        final TextView titleView, textView, answersCountView;
        private OnClickListener listener;

        ViewHolder(View view, OnClickListener listener) {
            super(view);
            this.listener = listener;
            imageView = (ImageView) view.findViewById(R.id.image);
            titleView = (TextView) view.findViewById(R.id.title);
            textView = (TextView) view.findViewById(R.id.text);
            answersCountView = (TextView) view.findViewById(R.id.answers_count);

            view.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    listener.onClick(getAdapterPosition());
                }
            });
        }
    }

    public interface OnClickListener {
        void onClick(int position);
    }
}

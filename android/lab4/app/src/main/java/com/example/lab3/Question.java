package com.example.lab3;

import android.graphics.Bitmap;
import androidx.annotation.NonNull;

public class Question {
    private String title;
    private String text;
    private String answers_count;
    private String image;
    private int id;
    private String full_text;
    public Question () {}

    public Question(int id, String title, String text, String answers_count, String image, String full_text) {
        this.id = id;
        this.title = title;
        this.text = text;
        this.answers_count = answers_count;
        this.image = image;
        this.full_text = full_text;
    }

    public int getId() {
        return id;
    }

    public String getTitle() {
        return title;
    }

    public String getText() {
        return text;
    }

    public String getAnswers_count() {
        return answers_count;
    }

    public String getImage() {
        return image;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public void setText(String text) {
        this.text = text;
    }

    public void setAnswers_count(String answers_count) {
        this.answers_count = answers_count;
    }

    public void setImage(String image) {
        this.image = image;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getFull_text() {
        return full_text;
    }

    public void setFull_text(String full_text) {
        this.full_text = full_text;
    }

    @NonNull
    @Override
    public String toString() {
        return this.title;
    }
}

package com.example.lab3;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.AsyncTask;
import android.widget.ImageView;

import java.io.InputStream;

public class ImageLoader extends AsyncTask<String, Void, Bitmap> {

    private ImageView imageView;

    public ImageLoader (ImageView imageView) {
        this.imageView = imageView;
    }

    @Override
    protected Bitmap doInBackground(String... strings) {
        String url = strings[0];
        Bitmap map = null;
        try{
            InputStream s = new java.net.URL(url).openStream();
            map = BitmapFactory.decodeStream(s);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return map;
    }

    protected void onPostExecute(Bitmap result) {
        imageView.setImageBitmap(result);
    }
}

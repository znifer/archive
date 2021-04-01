package com.example.lab1t1

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log

class DetailActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_detail)
    }
    override fun onStart() {
        super.onStart()
        Log.w("DetailActivity", "DetailActivity onStart() called")
    }

    override fun onResume() {
        super.onResume()
        Log.w("DetailActivity", "DetailActivity onResume() called")
    }

    override fun onRestart() {
        super.onRestart()
        Log.w("DetailActivity", "DetailActivity onRestart() called")
    }

    override fun onPause() {
        super.onPause()
        Log.w("DetailActivity", "DetailActivity onPause() called")
    }

    override fun onStop() {
        super.onStop()
        Log.w("DetailActivity", "DetailActivity onStop() called")
    }

    override fun onDestroy() {
        super.onDestroy()
        Log.w("DetailActivity", "DetailActivity onDestroy() called")
    }
}
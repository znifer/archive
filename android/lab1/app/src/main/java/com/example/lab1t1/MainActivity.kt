package com.example.lab1t1

import android.content.Intent
import android.net.Uri
import android.os.Bundle
import android.util.Log
import android.widget.Button
import androidx.appcompat.app.AppCompatActivity

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val toDetailActivityButton: Button = findViewById(R.id.button2)

        val toUriButton: Button = findViewById(R.id.button3)

        toDetailActivityButton.setOnClickListener {
            startActivity(Intent(this, DetailActivity::class.java))
        }

        toUriButton.setOnClickListener {
            startActivity(Intent(Intent.ACTION_VIEW, Uri.parse("https://github.com/znifer")))
        }

    }

    override fun onStart() {
        super.onStart()
        Log.w("MainActivity", "MainActivity onStart() called")
    }

    override fun onResume() {
        super.onResume()
        Log.w("MainActivity", "MainActivity onResume() called")
    }

    override fun onRestart() {
        super.onRestart()
        Log.w("MainActivity", "MainActivity onRestart() called")
    }

    override fun onPause() {
        super.onPause()
        Log.w("MainActivity", "MainActivity onPause() called")
    }

    override fun onStop() {
        super.onStop()
        Log.w("MainActivity", "MainActivity onStop() called")
    }

    override fun onDestroy() {
        super.onDestroy()
        Log.w("MainActivity", "MainActivity onDestroy() called")
    }
}
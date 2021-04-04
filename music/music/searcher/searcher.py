import requests
from fastapi import FastAPI
import json
app = FastAPI()

#в item_id вводим имя
@app.get("/{item_id}")
async def get_songs(item_id: str):
    song_resp = requests.get(
        'http://ws.audioscrobbler.com/2.0/?method=track.search&track='+ item_id + '&api_key=fff670dc3c7f1b019ac5c1ae930e4ce4&format=json&limit=1')
  
    songs = song_resp.json()['results']['trackmatches']['track'][0]['url']

    return songs
import requests
from fastapi import FastAPI

app = FastAPI()


@app.get('/')
async def get_songs():
    song_resp = requests.get(
        'http://ws.audioscrobbler.com/2.0/?method=chart.gettoptracks&api_key=fff670dc3c7f1b019ac5c1ae930e4ce4&format=json')
    songs = song_resp.json()['tracks']['track']
    newSongs = []
    for song in songs:
        # print(song)
        newSongs.append(
            {
                'name': song['name'],
                'artist': song['artist']['name'],
                'playcount': song['playcount'],
                'listeners': song['listeners'],
                'url': song['url']
            }
        )

    return newSongs
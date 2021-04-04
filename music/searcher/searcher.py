import requests
from fastapi import FastAPI
from starlette.responses import Response

app = FastAPI()


@app.get("/search/")
async def get_songs(name: str):

    song_resp = requests.get(
        'http://ws.audioscrobbler.com/2.0/?method=track.search&track={}&api_key=fff670dc3c7f1b019ac5c1ae930e4ce4&format=json&limit=1'.format(name))

    try:
        song = song_resp.json()['results']['trackmatches']['track'][0]['url']
    except:
        return Response(status_code=400)
    return song

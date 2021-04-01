import uvicorn
from fastapi import FastAPI

app = FastAPI()

data = [
    {
        "id": 0,
        "title": "title1",
        "answers_count": "10",
        "image": "https://picsum.photos/200/200",
        "text": "some text",
        "full_text": "some more text"
    },
    {
        "id": 1,
        "title": "title2",
        "answers_count": "10",
        "image": "https://picsum.photos/200/200",
        "text": "some text",
        "full_text": "some more text"
    },
    {
        "id": 2,
        "title": "title3",
        "answers_count": "10",
        "image": "https://picsum.photos/200/200",
        "text": "some text",
        "full_text": "some more text"
    },
]


@app.get("/all")
async def root():
    return data


@app.get("/item/{id}")
async def item(id: int):
    return data[id]

if __name__ == "__main__":
    uvicorn.run(app, host="0.0.0.0", port=8000)

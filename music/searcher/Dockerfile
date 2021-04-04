FROM python:3.9.2-slim-buster

WORKDIR /searcher
COPY ./req.txt /searcher
RUN pip install -r req.txt
COPY ./ /searcher/
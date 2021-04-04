FROM python:3.9.2-slim-buster

WORKDIR /fetcher
COPY ./req.txt /fetcher
RUN pip install -r req.txt
COPY ./ /fetcher/
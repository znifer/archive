FROM python:3.9.2-slim-buster
ENV PYTHONUNBUFFERED=1
WORKDIR /storage
COPY ./req.txt /storage
RUN pip install -r req.txt
COPY ./ /storage/
ENTRYPOINT ./run.sh
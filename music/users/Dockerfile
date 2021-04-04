FROM python:3.9.2-slim-buster
ENV PYTHONUNBUFFERED=1
WORKDIR /users
COPY ./req.txt /users
RUN pip install -r req.txt
COPY ./ /users/
ENTRYPOINT ./run.sh
from rest_framework import viewsets
from rest_framework.response import Response
from django.core.exceptions import ObjectDoesNotExist
from .serializers import *
from .models import *
import requests


class SongViewSet(viewsets.ModelViewSet):
    queryset = Song.objects.all()
    serializer_class = SongSerializer


class fetchSongs(viewsets.ViewSet):

    def list(self, request):
        resp = requests.get('http://fetcher:8000')
        for song in resp.json():
            try:
                Song.objects.get(
                    name=song['name'],
                    artist=song['artist'],
                    playcount=song['playcount'],
                    listeners=song['listeners'],
                    url=song['url']
                )
            except ObjectDoesNotExist:
                Song.objects.create(
                    name=song['name'],
                    artist=song['artist'],
                    playcount=song['playcount'],
                    listeners=song['listeners'],
                    url=song['url']
                )
        return Response(status=200, data={'Получилось': 'Песенки успешно подтянулись'})

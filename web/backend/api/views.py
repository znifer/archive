from django_filters.rest_framework import DjangoFilterBackend
from rest_framework import viewsets
from rest_framework.permissions import IsAuthenticated
from rest_framework import filters
from .serializers import *
from .models import *


class BandViewSet(viewsets.ModelViewSet):
    queryset = Band.objects.all()
    serializer_class = BandSerializer


class TrackViewSet(viewsets.ModelViewSet):
    queryset = Track.objects.all()
    serializer_class = TrackSerializer


class AlbumViewSet(viewsets.ModelViewSet):
    queryset = Album.objects.all()
    filter_backends = (filters.SearchFilter,)
    search_fields = ['title']

    def get_serializer_class(self):
        if self.action == 'list':
            return AlbumSerializer
        return DetailAlbumSerializer


class UserPreferenceViewSet(viewsets.ModelViewSet):
    serializer_class = UserPreferenceSerializer
    # Отдаем только аутентифицированному пользователю
    permission_classes = [IsAuthenticated]
    # Все, что его интересует
    def get_queryset(self):
        return UserPreference.objects.filter(user=self.request.user)


class GenreViewSet(viewsets.ModelViewSet):
    queryset = Genre.objects.all()
    serializer_class = GenreSerializer


class PersonViewSet(viewsets.ModelViewSet):
    queryset = Person.objects.all()
    serializer_class = PersonSerializer


class TopAlbumViewSet(viewsets.ModelViewSet):
    queryset = Album.objects.order_by('-rating')[:6]
    serializer_class = AlbumSerializer

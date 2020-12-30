from rest_framework import serializers
from .models import *

class TrackSerializer(serializers.ModelSerializer):
    class Meta:
        model = Track
        fields = '__all__'


class ShortBandSerializer(serializers.ModelSerializer):
    class Meta:
        model = Band
        fields = [
            'id',
            'name'
        ]


class ShortGenreSerializer(serializers.ModelSerializer):
    class Meta:
        model = Genre
        fields = [
            'name'
        ]


class AlbumSerializer(serializers.ModelSerializer):
    class Meta:
        model = Album
        fields = [
            'id',
        ]
        depth = 1

class BandSerializer(serializers.ModelSerializer):
    created = serializers.DateField(format='%Y')
    ended = serializers.DateField(format='%Y')
    albums = AlbumSerializer(many=True)
    class Meta:
        model = Band
        fields = [
            'id',
            'name',
            'description',
            'created',
            'ended',
            'logo',
            'rating',
            'members',
            'albums'
        ]
        depth = 1

class DetailAlbumSerializer(serializers.ModelSerializer):
    band = ShortBandSerializer()
    genres = ShortGenreSerializer(many=True)
    tracks = TrackSerializer
    release_date = serializers.DateField(format='%Y')
    class Meta:
        model = Album
        fields = [
            'id',
            'title',
            'release_date',
            'cover',
            'rating',
            'band',
            'genres',
            'tracks'
        ]
        depth = 1


class UserPreferenceSerializer(serializers.ModelSerializer):
    # Отдавать данные пользователя поприкольнее?
    class Meta:
        model = UserPreference
        fields = [
            'user',
            'bands',
            'albums',
            'tracks'
        ]


class GenreSerializer(serializers.ModelSerializer):
    class Meta:
        model = Genre
        fields = '__all__'


class PersonSerializer(serializers.ModelSerializer):
    class Meta:
        model = Person
        fields = '__all__'

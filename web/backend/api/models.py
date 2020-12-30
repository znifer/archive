from django.db import models
from django.contrib.auth.models import User
from django.conf import settings


class Person(models.Model):
    name = models.CharField(max_length=255)


class Band(models.Model):
    name = models.CharField(max_length=255)
    description = models.CharField(max_length=10000)
    created = models.DateField()
    ended = models.DateField(blank=True, null=True)
    logo = models.ImageField(upload_to=settings.MEDIA_ROOT)
    members = models.ManyToManyField(
        'Person'
    )
    rating = models.IntegerField()

    def __str__(self):
        return "Исполнитель: {}".format(self.name)


class Album(models.Model):
    title = models.CharField(max_length=255)
    release_date = models.DateField()
    cover = models.ImageField(upload_to=settings.MEDIA_ROOT)
    rating = models.IntegerField()
    band = models.ForeignKey(
        'Band',
        on_delete=models.CASCADE,
        related_name='albums'
    )
    genres = models.ManyToManyField(
        'Genre'
    )

    def __str__(self):
        return "Альбом: {}".format(self.title)


class Genre(models.Model):
    name = models.CharField(max_length=255)


class Track(models.Model):
    title = models.CharField(max_length=255)
    duration = models.CharField(max_length=255)
    rating = models.IntegerField()
    album = models.ForeignKey(
        'Album',
        on_delete=models.CASCADE,
        related_name='tracks'
    )

    def __str__(self):
        return "{} - {}".format(self.title, self.duration)


class UserPreference(models.Model):
    user = models.ForeignKey(
        User,
        on_delete=models.CASCADE
    )
    bands = models.ManyToManyField(
        'Band',
        blank=True,
        null=True
    )
    albums = models.ManyToManyField(
        Album,
        blank=True,
        null=True
    )
    tracks = models.ManyToManyField(
        Track,
        blank=True,
        null=True
    )

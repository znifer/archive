from django.db import models

class Song(models.Model):
    name = models.CharField(max_length=100)
    artist = models.CharField(max_length=100)
    playcount = models.IntegerField()
    listeners = models.IntegerField()
    url = models.CharField(max_length=200)

    def __str__(self):
        return '{} - {}'.format(self.artist, self.name)
from django.contrib import admin
from django.urls import path, include
from rest_framework import routers
from .views import *

router = routers.DefaultRouter()

router.register(r'song', SongViewSet, basename='song')
router.register(r'fetch_songs', fetchSongs, basename='fetch_songs')

urlpatterns = [
    path('admin/', admin.site.urls),
    path('', include(router.urls)),
]

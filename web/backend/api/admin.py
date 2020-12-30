from django.contrib import admin
from .models import *

admin.site.register(Track)
admin.site.register(Album)
admin.site.register(Band)
admin.site.register(Person)
admin.site.register(Genre)
admin.site.register(UserPreference)
from django.contrib.auth.models import User
from rest_framework import serializers


class UserLoginSerializer(serializers.HyperlinkedModelSerializer):
    class Meta:
        model = User
        fields = ['username', 'password', 'email']

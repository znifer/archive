from django.shortcuts import render
from django.http import HttpResponse
from django_filters.rest_framework import DjangoFilterBackend
import json

from django.contrib.auth.models import User
from rest_framework import viewsets
from rest_framework.response import Response

from api.serializers import BlogUserSerializer, CommentSerializer, PostSerializer, ContentSerializer
from logic.models import Post, BlogUser, Comment, PostPiece


class ContentViewSet(viewsets.ModelViewSet):
    queryset = PostPiece.objects.all()
    serializer_class = ContentSerializer


class PostViewSet(viewsets.ModelViewSet):
    queryset = Post.objects.all()
    serializer_class = PostSerializer

    filter_backends = [DjangoFilterBackend,]
    filter_fields = ['user',] 

class BlogUserViewSet(viewsets.ModelViewSet):
    queryset = BlogUser.objects.all()
    serializer_class = BlogUserSerializer


class CommentViewSet(viewsets.ModelViewSet):
    queryset = Comment.objects.all()
    serializer_class = CommentSerializer


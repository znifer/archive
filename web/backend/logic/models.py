from django.contrib.auth.models import User
from django.db import models


class BlogUser(User):
    profile_pic = models.ImageField(upload_to="profile_images", null=True)


class Post(models.Model):
    user = models.ForeignKey(BlogUser, on_delete=models.CASCADE)
    creation_time = models.DateTimeField(auto_now_add=True)


class PostPiece(models.Model):
    order = models.IntegerField()
    parent = models.ForeignKey(Post, on_delete=models.CASCADE)
    description = models.CharField(max_length=200)
    image_data = models.ImageField(upload_to="posts_images", null=True)
    text_data = models.CharField(max_length=1000, null=True)
    code_data = models.CharField(max_length=1000, null=True)


class Comment(models.Model):
    user = models.ForeignKey(BlogUser, on_delete=models.CASCADE)
    post = models.ForeignKey(Post, on_delete=models.CASCADE)
    content = models.CharField(max_length=1000)
    creation_time = models.DateTimeField(auto_now_add=True)

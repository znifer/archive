from django.contrib import admin
from django.urls import path

from rest_framework.routers import DefaultRouter
from rest_framework_simplejwt.views import TokenObtainPairView, TokenRefreshView

from rest_framework import permissions
from drf_yasg.views import get_schema_view
from drf_yasg import openapi

from .views import *

router = DefaultRouter()

router.register(r'bands', BandViewSet, basename='Artist')
router.register(r'top_albums', TopAlbumViewSet, basename='Album')
router.register(r'albums', AlbumViewSet, basename='Album')
router.register(r'tracks', TrackViewSet, basename='Track')
router.register(r'genres', GenreViewSet, basename='Genre')
router.register(r'persons', PersonViewSet, basename='Person')
router.register(r'user_preferences', UserPreferenceViewSet,
                basename='UserPreference')

schema_view = get_schema_view(
    openapi.Info(
        title="Snippets API",
        default_version='v1',
        description="Test description",
        license=openapi.License(name="BSD License"),
    ),
    public=True,
    permission_classes=(permissions.AllowAny,),
)

urlpatterns = [
    path('token/', 
         TokenObtainPairView.as_view(), 
         name='token_obtain_pair'),
    path('token/refresh/', 
         TokenRefreshView.as_view(), 
         name='token_refresh'),
    
    path('swagger(P<format>\.json|\.yaml)',
         schema_view.without_ui(cache_timeout=0), name='schema-json'),
    path('swagger/', 
         schema_view.with_ui('swagger', cache_timeout=0), 
         name='schema-swagger-ui'),
    path('redoc/', schema_view.with_ui('redoc', cache_timeout=0),
         name='schema-redoc'),
]

urlpatterns += router.urls

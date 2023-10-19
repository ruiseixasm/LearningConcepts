"""Defines URL patterns for users"""

from django.urls import path, include

from . import views # v.2

app_name = 'users'
urlpatterns = [
    # Include default auth urls.
    path('', include('django.contrib.auth.urls')),
    # Registration page.
    path('register/', views.register, name='register'), # v.2
]
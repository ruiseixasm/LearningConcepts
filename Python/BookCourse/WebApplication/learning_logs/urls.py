"""Defines URL patterns for learning_logs."""

from django.urls import path
from . import views

app_name = 'learning_logs'
urlpatterns = [
    # Home page
    path('', views.index, name='index'), # v.1
    # Page that shows all topics.
    path('topics/', views.topics, name='topics'), # v.2
    # Detail page for a single topic.
    path('topics/<int:topic_id>/', views.topic, name='topic'), # v.3
    # Page for adding a new topic
    path('new_topic/', views.new_topic, name='new_topic'), # v.4
    # Page for adding a new entry
    path('new_entry/<int:topic_id>/', views.new_entry, name='new_entry'), # v.5
    # Page for editing an entry.
    path('edit_entry/<int:entry_id>/', views.edit_entry, name='edit_entry'), # v.6
]
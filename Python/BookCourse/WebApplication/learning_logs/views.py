from django.shortcuts import render
from .models import Topic # v.2

# Create your views here.
def index(request): # v.1
    """The home page for Learning Log."""
    return render(request, 'learning_logs/index.html')

def topics(request): # v.2
    """Show all topics."""
    topics = Topic.objects.order_by('date_added')
    context = {'topics': topics}
    return render(request, 'learning_logs/topics.html', context)

def topic(request, topic_id): # v.3
    """Show a single topic and all its entries."""
    topic = Topic.objects.get(id=topic_id)
    entries = topic.entry_set.order_by('-date_added')
    context = {'topic': topic, 'entries': entries}
    return render(request, 'learning_logs/topic.html', context)
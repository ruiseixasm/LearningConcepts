from django.db import models
from django.contrib.auth.models import User # v.3

# Create your models here.
class Topic(models.Model): # v.1
    """A topic the user is learning about."""
    text = models.CharField(max_length=200)
    date_added = models.DateTimeField(auto_now_add=True)
    owner = models.ForeignKey(User, on_delete=models.CASCADE) # v.3

    def __str__(self):
        """Return a string representation of the model."""
        return self.text
    
class Entry(models.Model): # v.2
    """Something specific learned about a topic."""
    topic = models.ForeignKey(Topic, on_delete=models.CASCADE)
    text = models.TextField()
    date_added = models.DateTimeField(auto_now_add=True)

    class Meta:
        verbose_name_plural = 'entries'

    def __str__(self):
        """Return a string representaion of the model."""
        return f"{self.text[:50]}..."
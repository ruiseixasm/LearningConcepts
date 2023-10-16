from django.contrib import admin

# Register your models here.
from .models import Topic, Entry # v.1 v.2

admin.site.register(Topic) # v.1
admin.site.register(Entry) # v.2
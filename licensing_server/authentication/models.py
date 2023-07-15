from django.db import models
from django.contrib.auth.models import AbstractUser


class User(AbstractUser):
    email = models.EmailField(unique=True, blank=False)
    phone_number = models.CharField(max_length=15, blank=False, unique=True, default='')
    first_name = models.CharField(max_length=150, blank=False)
    last_name = models.CharField(max_length=150, blank=False)

    REQUIRED_FIELDS = ['first_name', 'last_name', 'phone_number', 'email']

# Create your models here.

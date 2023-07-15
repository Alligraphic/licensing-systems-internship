from django.db import models
from django.contrib.auth import get_user_model

User = get_user_model()


class License(models.Model):
    product_name = models.CharField(max_length=100, blank=False)
    serial_number = models.CharField(max_length=100, blank=False, unique=True)
    valid = models.BooleanField(default=True)
    valid_until = models.DateTimeField(blank=False)

    def __str__(self):
        return f'{self.product_name} - {self.serial_number}'


class UserLicense(models.Model):
    user = models.ForeignKey(User, on_delete=models.CASCADE)
    license = models.ForeignKey(License, on_delete=models.CASCADE)

    def __str__(self):
        return f'{self.user} - {self.license}'

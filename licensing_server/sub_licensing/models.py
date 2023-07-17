from django.db import models
from django.contrib.auth import get_user_model

User = get_user_model()


class Plan(models.Model):
    name = models.CharField(max_length=100, blank=False)
    price = models.DecimalField(max_digits=10, decimal_places=2, blank=False)
    length_days = models.IntegerField(blank=False)

    def __str__(self):
        return f'{self.name} - {self.price}'


class Subscription(models.Model):
    user = models.ForeignKey(User, on_delete=models.CASCADE)
    plan = models.ForeignKey(Plan, on_delete=models.CASCADE)
    activation_date = models.DateField(auto_now_add=True)

    def __str__(self):
        return f'{self.user} - {self.plan}'

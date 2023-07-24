from django.db import models
from django.contrib.auth import get_user_model

User = get_user_model()


class Key(models.Model):
    is_active = models.BooleanField(default=True)
    user = models.ForeignKey(User, on_delete=models.CASCADE, null=True)
    key_seed = models.CharField(max_length=32, null=True)

    @property
    def key(self):
        lower_alpha = 'abcdefghijklmnopqrstuvwxyz'
        upper_alpha = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
        numbers = '0123456789'
        
        seed = int(self.key_seed)

        key = ''
        for i in range(0, 32):
            if i % 3 == 0:
                key += upper_alpha[seed % 26]
            elif i % 3 == 1:
                key += lower_alpha[seed % 26]
            else:
                key += numbers[seed % 10]
            seed = seed >> 1

        return key

    def __str__(self):
        return self.key

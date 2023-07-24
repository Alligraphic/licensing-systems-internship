from django.db.models.signals import post_save
from django.dispatch import receiver

from . import models
from key_licensing.models import Key


def pad(text):
    padding_length = 8 - (len(text) % 8)
    if padding_length == 8:
        padding_length = 0
    padding = text * (padding_length // len(text) + 1)

    return padding[:8]


@receiver(post_save, sender=models.User)
def create_key(sender, instance, created, **kwargs):
    if created:
        seed = pad(str(instance.id))
        Key.objects.create(user=instance, key_seed=seed)

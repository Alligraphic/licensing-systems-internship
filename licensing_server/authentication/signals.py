from django.db.models.signals import post_save
from django.dispatch import receiver

from . import models
from key_licensing.models import Key


def pad(text):
    padding_length = 32 - (len(text) % 32)
    if padding_length == 32:
        padding_length = 0
    loop_length = padding_length // len(text) + 1

    padding = ''
    for i in range(0, loop_length):
        padding += str(int(text) + i)

    return padding[:32]


@receiver(post_save, sender=models.User)
def create_key(sender, instance, created, **kwargs):
    if created:
        seed = pad(str(instance.id))
        Key.objects.create(user=instance, key_seed=seed)

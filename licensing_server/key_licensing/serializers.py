from rest_framework import serializers
from django.contrib.auth import authenticate

from . import models


class KeySerializer(serializers.ModelSerializer):
    class Meta:
        model = models.Key
        fields = ('is_active', 'key')


class GetKeySerializer(serializers.Serializer):
    def update(self, instance, validated_data):
        pass

    def create(self, validated_data):
        pass

    username = serializers.CharField(max_length=255)
    password = serializers.CharField(
        label="Password",
        style={'input_type': 'password'},
        trim_whitespace=False,
        max_length=128,
        write_only=True
    )

    def validate(self, data):
        username = data.get('username')
        password = data.get('password')

        if username and password:
            user = authenticate(username=username, password=password)
            if not user:
                msg = ('Unable to log in with provided credentials.',)
                raise serializers.ValidationError(msg, code='authorization')
        else:
            msg = ('Must include "username" and "password".',)
            raise serializers.ValidationError(msg, code='authorization')

        key = models.Key.objects.get(user=user)

        data = {
            'is_valid': key.is_active,
            'username': username,
            'key': key.key
        }

        return data

    class Meta:
        model = models.Key

        fields = ('username', 'password')
        read_only_fields = ('key',)

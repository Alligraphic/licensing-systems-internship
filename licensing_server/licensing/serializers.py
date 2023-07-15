from rest_framework import serializers
from . import models


class LicenseSerializer(serializers.ModelSerializer):
    class Meta:
        model = models.License
        fields = ['id', 'product_name', 'serial_number', 'valid', 'valid_until']


class CheckLicenseSerializer(serializers.ModelSerializer):
    class Meta:
        model = models.License
        fields = ['serial_number']

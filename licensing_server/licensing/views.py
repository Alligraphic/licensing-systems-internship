from rest_framework.viewsets import ModelViewSet, ViewSet
from rest_framework.views import APIView
from rest_framework.response import Response
from rest_framework import status

from . import serializers
from . import models


class CheckLicense(ViewSet):
    serializer_class = serializers.CheckLicenseSerializer

    def create(self, request, *args, **kwargs):
        serial_number = self.request.data.get('serial_number')
        if not serial_number:
            return Response({'error': 'serial_number is required'}, status=status.HTTP_400_BAD_REQUEST)
        try:
            license_obj = models.License.objects.get(serial_number=serial_number)
            print(license_obj.serial_number)
        except models.License.DoesNotExist:
            return Response({'error': 'License not found'}, status=status.HTTP_404_NOT_FOUND)

        if license_obj.valid:
            return Response({'message': 'License is valid'}, status=status.HTTP_200_OK)
        else:
            return Response({'error': 'License is not valid'}, status=status.HTTP_400_BAD_REQUEST)


class LicenseViewSet(ModelViewSet):
    serializer_class = serializers.LicenseSerializer
    queryset = models.License.objects.all()

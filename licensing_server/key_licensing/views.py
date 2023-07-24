from rest_framework.response import Response
from rest_framework.viewsets import ModelViewSet, ViewSet
from rest_framework.permissions import IsAuthenticated
from rest_framework import status

from . import serializers
from . import models


class KeyViewSet(ModelViewSet):
    serializer_class = serializers.KeySerializer
    queryset = models.Key.objects.all()
    permission_classes = [IsAuthenticated]

    http_method_names = ['get']


class GetKeyViewSet(ViewSet):
    serializer_class = serializers.GetKeySerializer

    def create(self, request, *args, **kwargs):
        serializer = self.serializer_class(data=self.request.data)
        serializer.is_valid(raise_exception=True)
        return Response(serializer.validated_data, status=status.HTTP_200_OK)

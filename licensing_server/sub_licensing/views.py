from rest_framework.response import Response
from rest_framework.viewsets import ModelViewSet, ViewSet
from rest_framework.permissions import IsAuthenticated
from rest_framework import status

from . import serializers
from . import models
from .signature import sign_string, private_key_path

import os


class PlanViewSet(ModelViewSet):
    serializer_class = serializers.PlanSerializer
    queryset = models.Plan.objects.all()


class SubscriptionViewSet(ModelViewSet):
    serializer_class = serializers.SubscriptionSerializer
    permission_classes = [IsAuthenticated]

    def get_queryset(self):
        return models.Subscription.objects.filter(user=self.request.user)

    def perform_create(self, serializer):
        serializer.save(user=self.request.user)


class SubscriptionCheckViewSet(ViewSet):
    serializer_class = serializers.SubscriptionCheckSerializer

    def create(self, request, *args, **kwargs):
        serializer = self.serializer_class(data=self.request.data)
        serializer.is_valid(raise_exception=True)
        return Response(serializer.validated_data, status=status.HTTP_200_OK)


class SubscriptionSignatureViewSet(ViewSet):
    serializer_class = serializers.SubscriptionCheckSerializer

    def create(self, request, *args, **kwargs):
        serializer = self.serializer_class(data=self.request.data)
        serializer.is_valid(raise_exception=True)
        data = serializer.validated_data

        print(os.getcwd())

        signature = sign_string(data['sub_status'], private_key_path)
        data['signature'] = signature.hex()
        return Response(data, status=status.HTTP_200_OK)


class VerifySignatureViewSet(ViewSet):
    serializer_class = serializers.VerifySignatureSerializer

    def create(self, request, *args, **kwargs):
        serializer = self.serializer_class(data=self.request.data)
        serializer.is_valid(raise_exception=True)
        data = serializer.validated_data

        return Response(data, status=status.HTTP_200_OK)

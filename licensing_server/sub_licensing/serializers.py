import datetime

from django.contrib.auth import authenticate
from rest_framework import serializers
from . import models


class PlanSerializer(serializers.ModelSerializer):
    class Meta:
        model = models.Plan
        fields = '__all__'


class SubscriptionSerializer(serializers.ModelSerializer):
    plan_details = serializers.SerializerMethodField()

    @staticmethod
    def get_plan_details(obj):
        return PlanSerializer(obj.plan).data

    class Meta:
        model = models.Subscription
        fields = '__all__'
        read_only_fields = ('user', 'activation_date', 'plan_details')


class SubscriptionCheckSerializer(serializers.Serializer):
    def create(self, validated_data):
        pass

    def update(self, instance, validated_data):
        pass

    is_valid = serializers.SerializerMethodField()

    @staticmethod
    def get_is_valid(obj):
        now = datetime.datetime.now().date()
        return obj.activation_date + datetime.timedelta(days=obj.plan.length_days) >= now

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

        subscriptions = models.Subscription.objects.filter(user=user).all()

        is_valid = False
        for subscription in subscriptions:
            is_valid = is_valid or self.get_is_valid(subscription)

        data = {'is_valid': is_valid}

        return data

    class Meta:
        model = models.Subscription

        fields = ('email', 'password')
        read_only_fields = ('is_valid',)


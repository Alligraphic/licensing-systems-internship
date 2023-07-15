from django.urls import path
from rest_framework import routers
from . import views

router = routers.DefaultRouter()
router.register(r'licenses', views.LicenseViewSet, basename='licenses')
router.register(r'check', views.CheckLicense, basename='check-license')

urlpatterns = router.urls

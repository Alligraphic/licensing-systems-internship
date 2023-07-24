from rest_framework import routers
from . import views

router = routers.DefaultRouter()

router.register('keys', views.KeyViewSet, basename='keys')
router.register('get_key', views.GetKeyViewSet, basename='get_key')

urlpatterns = router.urls

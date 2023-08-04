from rest_framework import routers
from . import views

router = routers.DefaultRouter()

router.register('plans', views.PlanViewSet, 'plans')
router.register('subscriptions', views.SubscriptionViewSet, 'subscriptions')
router.register('check', views.SubscriptionCheckViewSet, 'subscription-check')
router.register('sign-check', views.SubscriptionSignatureViewSet, 'subscription-signature')
router.register('verify-sign', views.VerifySignatureViewSet, 'verify-signature')

urlpatterns = router.urls

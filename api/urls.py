from django.urls import path
from .views import listarCriarSensor
from rest_framework import routers

router = routers.SimpleRouter()

router.register('sensor', listarCriarSensor, basename='sensor')

urlpatterns = []+router.urls
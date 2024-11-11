from django.shortcuts import render
from rest_framework import viewsets
from .serializer import sensorSerializer
from .models import sensor
from rest_framework.response import Response
from rest_framework import status

class listarCriarSensor(viewsets.ModelViewSet):
    serializer_class = sensorSerializer
    queryset = sensor.objects.all()
from rest_framework import serializers
from .models import sensor

class sensorSerializer(serializers.ModelSerializer):
    class Meta:
        model = sensor
        fields = ['tipo', 'dados', 'id', 'data']
        read_only_fields = ['id', 'data']
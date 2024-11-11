from django.db import models

class sensor(models.Model):
    id = models.IntegerField(primary_key=True)
    tipo = models.CharField(max_length=255)
    dados = models.CharField(max_length=255)
    data = models.DateTimeField(auto_now_add=True)
    


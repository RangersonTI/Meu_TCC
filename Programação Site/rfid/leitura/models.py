from django.db import models

# Create your models here.

class Rfid(models.Model):
    id = models.AutoField(primary_key=True)
    rfid = models.CharField(max_length=16)
from django.db import models
class User(models.Model):
    email = models.CharField(max_length=30)
    first_name = models.CharField(max_length=50)
    last_name = models.CharField(max_length=50)
    phone_number = models.CharField(max_length=50)

class MedicProfile(models.Model):
    badge_number = models.CharField(max_length=50)
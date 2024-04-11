from django.db import models
from django.contrib.auth.models import UserManager, AbstractBaseUser, PermissionsMixin

class Activity(models.TextChoices):
    WALK = 'WALK', 'Walking'
    RUN = 'RUN', 'Running'
    JOG = 'JOG', 'Jogging'
    CYCLE = 'CYCLE', 'Cycling'
    SEDENTARY = 'SEDENTARY', 'Sedentary'

class Recommandation(models.Model):
    activity_type = models.CharField(choices=Activity.choices)
    days_duration = models.IntegerField()
    note = models.CharField(max_length=200)
    start_date = models.DateField()

class HealthWarning(models.Model):
    message = models.CharField(max_length=200)
    min_value = models.FloatField()
    max_value = models.FloatField()
    activity_type = models.CharField(choices=Activity.choices)

class SensorData(models.Model):
    class SensorType(models.TextChoices):
        TEMPERATURE = 'TMP', 'Temperature'
        HUMIDITY = 'HUM', 'Humidity'
        BPM = 'BPM', 'Beats Per Minute'

    type = models.CharField(max_length=3, choices=SensorType.choices)
    value = models.FloatField()
    date = models.DateField(auto_now_add=True)
    
class Address(models.Model):
    country = models.CharField(max_length=100)
    city = models.CharField(max_length=100)
    street = models.CharField(max_length=100)
    street_number = models.IntegerField()

class MedicProfile(models.Model):
    badge_number = models.CharField(max_length=10, blank=True, null=True)

    def get_medic_badge_number(self):
        return self.badge_number
    
class PacientProfile(models.Model):
    cnp = models.CharField(max_length=13, blank=True, null=True)
    age = models.IntegerField(blank=True, null=True)
    profession = models.CharField(max_length=100, blank=True, null=True)
    work_place = models.CharField(max_length=100, blank=True, null=True)
    allergies = models.CharField(max_length=200, blank=True, null=True)
    sensor_data = models.ManyToManyField(SensorData, blank=True, null=True)
    address = models.OneToOneField(Address, blank=True, null=True, on_delete=models.CASCADE)
    health_warnings = models.ManyToManyField(HealthWarning, blank=True, null=True)
    activity_type = models.CharField(choices=Activity.choices, blank=True, null=True)
    recommandations = models.ManyToManyField(Recommandation, blank=True, null=True)

class CustomUserManager(UserManager):
    def _create_user(self, email, password, **extra_fields):
        if not email:
            raise ValueError('The given email must be set')
        
        email = self.normalize_email(email)
        user = self.model(email=email, **extra_fields)

        user.set_password(password)
        user.save(using=self._db)

        return user
    
    def create_user(self, email=None, password=None, **extra_fields):
        extra_fields.setdefault('is_staff', False)
        extra_fields.setdefault('is_superuser', False)

        return self._create_user(email, password, **extra_fields)
    
    def create_superuser(self, email=None, password=None, **extra_fields):
        extra_fields.setdefault('is_staff', True)
        extra_fields.setdefault('is_superuser', True)

        return self._create_user(email, password, **extra_fields)
    
class User(AbstractBaseUser, PermissionsMixin):
    email = models.EmailField(blank=True, default='', unique=True)
    first_name = models.CharField(max_length=100, blank=True, default='')
    last_name = models.CharField(max_length=100, blank=True, default='')
    phone_number = models.CharField(max_length=100, blank=True, default='')

    medic_profile = models.OneToOneField(MedicProfile, on_delete=models.CASCADE, null=True, blank=True)

    is_active = models.BooleanField(default=True)
    is_staff = models.BooleanField(default=False)
    is_superuser = models.BooleanField(default=False)

    date_joined = models.DateTimeField(auto_now_add=True)
    last_login = models.DateTimeField(blank=True, null=True)

    objects = CustomUserManager()

    USERNAME_FIELD = 'email'
    EMAIL_FIELD = 'email'
    REQUIRED_FIELDS = []

    class Meta:
        verbose_name = 'User'
        verbose_name_plural = 'Users'

    def get_user_email(self):
        return self.email
    
    def get_user_full_name(self):
        return self.first_name +'' + self.last_name
    
    def get_user_phone_number(self):
        return self.phone_number
    
    def get_user_medic_profile(self):
        return self.medic_profile
    
    def get_user_id(self):
        return self.id

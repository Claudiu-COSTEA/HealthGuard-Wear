# from django.contrib.auth.models import User
from rest_framework import serializers
from .models import User, MedicProfile

class UserSerializer(serializers.ModelSerializer):
    class Meta:
        model = User
        fields = ["id", "email", "first_name", "last_name", "phone_number", "password", "medic_profile"]
        extra_kwargs = {"password": {"write_only": True}}

    def create(self, validated_data):
        user = User.objects.create_user(**validated_data)                               
        return user
    
class MedicProfileSerializer(serializers.ModelSerializer):
    class Meta:
        model = MedicProfile
        fields = ["id", "badge_number"]

    def create(self, validated_data):
        medic_profle = MedicProfile.objects.create(**validated_data)
        return medic_profle
    

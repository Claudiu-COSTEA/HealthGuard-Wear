from django.shortcuts import render
# from django.contrib.auth.models import User
from .models import User, MedicProfile, PacientProfile
from rest_framework import generics
from .serializers import UserSerializer, MedicProfileSerializer, PacientProfileSerializer
from rest_framework.permissions import IsAuthenticated, AllowAny

class CreateUserView(generics.CreateAPIView):
    queryset = User.objects.all()
    serializer_class = UserSerializer
    permission_classes = [AllowAny]

class ListUsersView(generics.ListAPIView):
    queryset = User.objects.all()
    serializer_class = UserSerializer
    permission_classes = [AllowAny]

class UpdateUserView(generics.RetrieveUpdateDestroyAPIView):
    queryset = User.objects.all()
    serializer_class = UserSerializer
    permission_classes = [AllowAny]
    lookup_field = 'pk'

class CreateMedicProfileView(generics.CreateAPIView):
    queryset = MedicProfile.objects.all()
    serializer_class = MedicProfileSerializer
    permission_classes = [AllowAny]

class CreatePacientProfileView(generics.CreateAPIView):
    queryset = PacientProfile.objects.all()
    serializer_class = PacientProfileSerializer
    permission_classes = [AllowAny]
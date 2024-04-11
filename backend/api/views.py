from django.shortcuts import render
# from django.contrib.auth.models import User
from .models import User, MedicProfile
from rest_framework import generics
from .serializers import UserSerializer, MedicProfileSerializer
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
# HealthGuard-Wear

## Server

### Prerequisites to install
1. python3.10+
2. pip
3. psql
4. npm

### How to run? [Backend server]
- In project root path:
```
>> python3 -m venv env
>> source env/bin/activate [linux]
>> ./env/Scripts/activate [windows] 
```

- In `/backend` path:
```
>> pip install -r requirements.txt
>> python manage.py runserver
```
  
- Visit [localhost:8000](http://localhost:8000/)

### How to run? [React Frontend server]
- In `/frontend` path:
```
>> npm run dev
```

- Visit [localhost:5173](http://localhost:5173/)

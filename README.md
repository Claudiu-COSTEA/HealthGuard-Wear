# HealthGuard-Wear

### Prerequisites to install
1. node v20.12.1
2. npm
3. python v3.10+
4. pip
5. psql

### How to run? [Django Backend server]
- In project root path:

Run this only the first time:
```
python3 -m venv env
```
Run this everytime:
  - linux
    ```
    source env/bin/activate
    ```
  - windows
    ```
    ./env/Scripts/activate
    ```

- In `/backend` path:

Run this only the first time:
```
pip install -r requirements.txt
```
Run this everytime:
```
python manage.py runserver
```
  
- Visit [localhost:8000](http://localhost:8000/)

### How to run? [React Frontend server]
- In `/frontend` path:

Run this only the first time:
```
npm install
```
Run this everytime:
```
npm run dev
```

- Visit [localhost:5173](http://localhost:5173/)

import paho.mqtt.publish as publish

# Definim adresa serverului MQTT și portul
mqtt_server = "mqtt.example.com"  # Adresa serverului MQTT de pe Heroku
port = 1883  # Portul implicit pentru MQTT

# Definim numele subiectului pentru comunicare
topic = "cloud_topic"

# Mesajul pe care dorim să îl trimitem către serverul MQTT de pe Heroku
message = "Mesaj către serverul Heroku de la clientul local"

# Publicăm mesajul către serverul MQTT de pe Heroku
publish.single(topic, message, hostname=mqtt_server, port=port)

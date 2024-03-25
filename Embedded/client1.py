import paho.mqtt.client as mqtt

# Definim brokerul MQTT și portul
broker_address = "mqtt.eclipseprojects.io"
port = 1883

# Definim numele subiectului pentru comunicare
topic = "test"

# Creăm un client MQTT
client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)

# Conectăm clientul la broker
client.connect(broker_address, port)

# Publicăm un mesaj pe subiect
client.publish(topic, "Ce faci baaa ?")

# Deconectăm clientul de la broker
client.disconnect()

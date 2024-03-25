import paho.mqtt.client as mqtt

# Definim brokerul MQTT și portul
broker_address = "mqtt.eclipseprojects.io"
port = 1883

# Definim numele subiectului pentru comunicare
topic = "test"

# Callback-ul care se apelează atunci când primim un mesaj
def on_message(client, userdata, message):
    print("Mesaj primit: ", str(message.payload.decode("utf-8")))

# Creăm un client MQTT
client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)

# Setăm callback-ul pentru primirea mesajelor
client.on_message = on_message

# Conectăm clientul la broker
client.connect(broker_address, port)

# Ne abonăm la subiectul definit
client.subscribe(topic)

# Pornim bucla de gestionare a evenimentelor MQTT
client.loop_forever()

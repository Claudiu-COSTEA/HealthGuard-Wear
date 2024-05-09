import paho.mqtt.client as mqtt

# Define callback functions
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected to MQTT Broker!")
        # Subscribe to a topic when connected
        client.subscribe("test/topic")
    else:
        print("Failed to connect, return code %d\n", rc)

def on_message(client, userdata, message):
    print("Received message on topic {}: {}".format(message.topic, message.payload.decode()))

def on_disconnect(client, userdata, rc):
    print("Disconnected from MQTT Broker")

# Create an MQTT client instance
client = mqtt.Client()

# Assign callback functions
client.on_connect = on_connect
client.on_message = on_message
client.on_disconnect = on_disconnect

# Connect to the Mosquitto broker
client.connect("test.mosquitto.org", 1883)

# Run the loop forever to receive messages
client.loop_forever()

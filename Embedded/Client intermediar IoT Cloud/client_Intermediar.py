import paho.mqtt.client as mqtt
import requests
from requests.auth import HTTPBasicAuth

# Definim brokerul MQTT și portul
broker_address = "test.mosquitto.org"
port = 1883

# Define the GraphQL endpoint URL
#graphql_url = 'https://healthguard-api.fly.dev/api/graphql'
graphql_url = 'http://localhost:4000/api/graphql'

# Define your username and password for Basic Authentication
username = 'admin'
password = 'admin'

# Definim numele subiectului pentru comunicare
topic = "Valori"

OK = False

# Callback-ul care se apelează atunci când primim un mesaj
def on_message(client, userdata, message):
    global OK  # Ensure we can modify the global OK variable
    
    valori = str(message.payload.decode("utf-8"))
    parts = valori.split("-")
    print(parts)

    id_utilizator = 3  # First part as an integer
    temperatura = float(parts[2])  # Second part as a float
    umiditate = float(parts[3])  # Third part as a float
    puls = float(parts[1])  # Fourth part as an integer

    ecg_valori = parts[0].split()
    vector = [int(x) for x in ecg_valori]  # Remaining parts as integers in a list

    print("ID utilizator:", id_utilizator)
    print("Temperatura:", temperatura)
    print("Umiditate:", umiditate)
    print("Puls:", puls)
    print("ECG:", vector)
    OK = True

    # Define your GraphQL mutation query with variables
    mutation_query = '''
    mutation AddSensorData($id: ID!, $bpm: Float!, $temperature: Float!, $humidity: Float!, $ecg: [Float!]){
    addSensorDataToPacient(input: {userId: $id, bpm: $bpm, temperature: $temperature, humidity: $humidity, ecg: $ecg})
    {
    id,
    pacientProfile {
      sensorData {type, date, value},
    }
  }
}
    '''
    # Define the input data for the mutation
    input_data = {
        "userId": id_utilizator,
        "bpm": puls,
        "temperature": temperatura,
        "humidity": umiditate,
        "ecg": vector
    }

    if OK:
        # Send the GraphQL mutation as a POST request with Basic Authentication
        response = requests.post(
            graphql_url,'',
            json={'query': mutation_query, 'variables': {"id": id_utilizator, "bpm": puls, "temperature": temperatura, "humidity": umiditate, "ecg":vector}},
            auth=HTTPBasicAuth(username, password)
        )
        OK = False

        # Check if the request was successful
        if response.status_code == 200:
            print("Message sent successfully.")
            #print(response.content)
        else:
            print(f"Failed to send message. Status code: {response.status_code}, Response: {response.text}")
            #print(response.content)

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

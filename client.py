import paho.mqtt.client as mqtt
import requests

# Definim brokerul MQTT și portul
broker_address = "test.mosquitto.org"
port = 1883

# Define the GraphQL endpoint URL
graphql_url = 'https://healthguard-api.fly.dev/api/graphql'

# Definim numele subiectului pentru comunicare
topic = "Valori"

OK = False

# Callback-ul care se apelează atunci când primim un mesaj
def on_message(client, userdata, message):
   
    valori = str(message.payload.decode("utf-8"))
    #print (valori)
    parts = valori.split("-")
    print(parts)

    id_utilizator = 1  # First part as an integer
    temperatura = float(parts[2])  # Second part as a float
    umiditate = float(parts[3])  # Third part as an integer
    puls = int(parts[1])  # Fourth part as an integer

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
    mutation AddSensorData($input: SensorDataInput!) {
    addSensorDataToPacient(input: $input) {
        id,
        email,
        firstName,
        lastName,
        phoneNumber,
        pacientProfile {
        id,
        cnp,
        age,
        address {
            country,
            city,
            street,
            streetNumber
        },
        sensorData {
            type,
            value,
            date
        }
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
    if OK is True:
        # Send the GraphQL mutation as a POST request
        response = requests.post(graphql_url, json={'query': mutation_query, 'variables': {'input': input_data}})
        OK = False

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

#include <DHT.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define AD8232_PIN A0
#define DHTPIN 2
#define DHTTYPE DHT11
#define MSG_BUFFER_SIZE	(150)
#define MSG_SEC	(50)

DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "LinksysB019";
const char* password = "wm83y3fby4";
const char* mqtt_server = "test.mosquitto.org";

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long previousMillis5 = 0; 
unsigned long previousMillis30 = 0;  
unsigned long previousMillis60 = 0;  

const long interval = 1000;  

typedef struct Date{

 int ecgValori[20];
 int puls;
 float temperatura;
 float umiditate;
}Date;

Date date;


char msg[MSG_SEC];
char msg1[MSG_BUFFER_SIZE];
float valoriTemp = 0;
int numarValoriTemp = 0;
float valoriUmid = 0;
int numarValoriUmid = 0;

void getEcgPuls() {
  int numar_pulsuri = 0;
  int val_puls = 0;

  if ((digitalRead(4) == 1) || (digitalRead(0) == 1)) {
    Serial.println('!');
  } else {
    unsigned long startTime = millis(); 
    unsigned long duration = 10000;

    while (millis() - startTime < duration && numar_pulsuri < 20) {
      date.ecgValori[numar_pulsuri] = analogRead(AD8232_PIN);
      numar_pulsuri++;
    }

    numar_pulsuri = 0;
  }
  delay(10);
}


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  pinMode(BUILTIN_LED, OUTPUT);

  pinMode(4, INPUT);
  pinMode(0, INPUT);
  setup_wifi();
  dht.begin();

  
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis5 >= interval * 2 ) {
    
   // date.ecgValoare = analogRead(AD8232_PIN);
    float temperature = dht.readTemperature();
    date.temperatura = dht.readTemperature();
    float humidity = dht.readHumidity();
    date.umiditate = dht.readHumidity();

    previousMillis5 = currentMillis;
  }

  if (currentMillis - previousMillis30 >= interval * 5) {
   
    getEcgPuls();
    int ecgValue = analogRead(AD8232_PIN);

    previousMillis30 = currentMillis;
  }

  if (currentMillis - previousMillis60 >= interval * 10) {
    
    strcat(msg1, "1");
    strcat(msg1, " - ");
    char msgE[6];
    for(int i = 0; i < 20; i++)
    {
      //Serial.println(date.ecgValori[i]);
       itoa(date.ecgValori[i], msgE, 6);
       strcat(msg1, msgE);
       strcat(msg1, " ");
    }

    snprintf (msg, 50, "- %d - %.2f - %.2f", date.puls,date.temperatura, date.umiditate);

    Serial.println();

    strcat(msg1, msg);
    Serial.print("Publish message: ");
    Serial.println(msg1);
    client.publish("Valori", msg1);

    strcpy(msg1, "");
    previousMillis60 = currentMillis;
  }

  delay(1000);
  
}
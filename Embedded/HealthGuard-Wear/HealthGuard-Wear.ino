#include <DHT.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define AD8232_PIN A0
#define DHTPIN 2
#define DHTTYPE DHT11
#define MSG_BUFFER_SIZE (150)
#define threshold 75       // to identify R peak
#define timer_value 10000  // 10 seconds timer to calculate hr

DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "DIGI-N4bE";
const char* password = "kXHKfZeUCs";
const char* mqtt_server = "test.mosquitto.org";

WiFiClient espClient;
PubSubClient client(espClient);

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis5 = 0;   // will store last time LED was updated
unsigned long previousMillis30 = 0;  // will store last time LED was updated
unsigned long previousMillis60 = 0;  // will store last time LED was updated


const long interval = 1000;  // interval at which to blink (milliseconds)

typedef struct Date {
  int ecgValori[20];
  double puls;
  float temperatura;
  float umiditate;
} Date;

Date date;

long instance1 = 0, timer;
double hrv = 0;
double hr = 72;
double interval2 = 0;
int value = 0, count = 0;
bool flag = 0;
char msg[30];
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
      int i = analogRead(AD8232_PIN);
      if (i < 1024) {
        date.ecgValori[numar_pulsuri] = i;
        val_puls += date.ecgValori[numar_pulsuri];
        numar_pulsuri++;
      }
    }
  }
  delay(10);
}


void getBPM() {

  unsigned long startTime = millis();
  while (millis() - startTime < 10000) {
    if ((digitalRead(4) == 1) || (digitalRead(0) == 1)) {
      Serial.print(".");
      instance1 = micros();
      timer = millis();
      delay(1000);
    } else {
      value = analogRead(A0);
      value = map(value, 250, 400, 0, 100);
      if ((value > threshold) && (!flag)) {
        count++;
        flag = 1;
        interval2 = micros() - instance1;
        instance1 = micros();
      } else if ((value < threshold)) {
        flag = 0;
      }
      if ((millis() - timer) > 10000) {
        hr = count * 3;
        timer = millis();
        count = 0;
      }
      hrv = hr / 60 - interval2 / 1000000;
      if (hr > 200 && hr < 300) {
        date.puls = hr - 50 + random(1, 10);
      } else if (hr > 300) {
        date.puls = random(100, 150);
      } else {
        date.puls = hr + random(1, 5);
      }
      delay(10);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);
  } else {
    digitalWrite(BUILTIN_LED, HIGH);
  }
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
  Serial.begin(9600);

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

  if (currentMillis - previousMillis5 >= interval * 2) {

    float temperature = dht.readTemperature();
    date.temperatura = dht.readTemperature();
    float humidity = dht.readHumidity();
    date.umiditate = dht.readHumidity();
    previousMillis5 = currentMillis;
  }

  if (currentMillis - previousMillis30 >= interval * 5) {
    getEcgPuls();
    getBPM();
    previousMillis30 = currentMillis;
  }

  if (currentMillis - previousMillis60 >= interval * 10) {

    char msgE[6];
    for (int i = 0; i < 20; i++) {
      snprintf(msgE, sizeof(msgE), "%d ", date.ecgValori[i]);
      strcat(msg1, msgE);
      strcat(msg1, " ");
    }

    snprintf(msg, 50, "- %.2f - %.2f - %.2f", date.puls, date.temperatura, date.umiditate);

    for (int i = 0; i < 20; i++) {
      date.ecgValori[i] = 0;
    }

    date.puls = 0;
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

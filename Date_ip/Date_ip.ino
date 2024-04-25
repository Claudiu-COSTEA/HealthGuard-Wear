#include <DHT.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "LinksysB019";
const char* password = "wm83y3fby4";
const char* mqtt_server = "test.mosquitto.org";

#define MSG_BUFFER_SIZE	(50)
#define DHTPIN 2 //defines what digital pin is used by sensor
#define DHTTYPE DHT11 //tells the arduino that we are using a dht11 and not a dht22

WiFiClient espClient;
PubSubClient client(espClient);

char msg[MSG_BUFFER_SIZE];
float valoriTemp = 0;
int numarValoriTemp = 0;
float valoriUmid = 0;
int numarValoriUmid = 0;

int iduser = 1111;

volatile bool flag30s = false; // Variabilă pentru a indica întreruperea la 30 de secunde
volatile bool flag5s = false; // Variabilă pentru a indica întreruperea la 5 secunde
volatile bool flag60s = false; // Variabilă pentru a indica întreruperea la 60 de secunde

typedef struct {

  String ecg[30];
  int puls;
  float temperatura;
  int umiditate;
}Date;

Date date;

void getEcgPuls(){

if((digitalRead(4) == 1)||(digitalRead(0) == 1))
{
  Serial.println('!');
}
else
{

    unsigned long startTime = millis(); // Momentul de start al buclei
    unsigned long duration = 10000;     // Durata de așteptare în milisecunde (10 secunde)
    int i = 0;

    while (millis() - startTime < duration) {
      date.ecg[i] = String(analogRead(A0));
      i++;
}

date.ecg[i] = '\0';
date.puls = 0;

}
delay(10);
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
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

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // // Switch on the LED if an 1 was received as first character
  // if ((char)payload[0] == '1') {
  //   digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
  //   // but actually the LED is on; this is because
  //   // it is active low on the ESP-01)
  // } else {
  //   digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  // }

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

void setup() {
  //pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  pinMode(4, INPUT);
  pinMode(0, INPUT);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

   // Configurare temporizator Timer1 pentru întrerupere la fiecare 30 de secunde
TCCR1A = 0; // Configurare Timer1 în modul normal
TCCR1B = (1 << WGM12) | (1 << CS11) | (1 << CS10); // Prescaler 64, CTC mode
OCR1A = 46875; // Valoare pentru declanșarea întreruperii la fiecare 30 de secunde
TIMSK1 |= (1 << OCIE1A); // Activează întreruperea la comparație cu OCR1A

// Configurare temporizator Timer2 pentru întrerupere la fiecare 5 secunde
TCCR2A = 0; // Configurare Timer2 în modul normal
TCCR2B = (1 << CS22); // Prescaler 64
OCR2A = 156; // Valoare pentru declanșarea întreruperii la fiecare 5 secunde
TIMSK2 |= (1 << OCIE2A); // Activează întreruperea la comparație cu OCR2A

// Configurare temporizator Timer3 pentru întrerupere la fiecare 60 de secunde
TCCR3A = 0; // Configurare Timer3 în modul normal
TCCR3B = (1 << WGM32) | (1 << CS32) | (1 << CS30); // Prescaler 1024, CTC mode
OCR3A = 46875; // Valoare pentru declanșarea întreruperii la fiecare 60 de secunde
TIMSK3 |= (1 << OCIE3A); // Activează întreruperea la comparație cu OCR3A

}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();


  if (flag30s) {
    Serial.println("Intrerupere la 30 de secunde!");
    flag30s = false; // Resetează flag-ul
  }
  
  if (flag5s) {
    Serial.println("Intrerupere la 5 secunde!");
    flag5s = false; // Resetează flag-ul
  }
  
  if (flag60s) {
    Serial.println("Intrerupere la 60 de secunde!");
    flag60s = false; // Resetează flag-ul
  }
}


// Funcția de întrerupere pentru temporizatorul Timer1 (30 de secunde)
ISR(TIMER1_COMPA_vect) {
  flag30s = true; // Setează flag-ul pentru a indica întreruperea la 30 de secunde
  getEcgPuls();
}

// Funcția de întrerupere pentru temporizatorul Timer2 (5 secunde)
ISR(TIMER2_COMPA_vect) {
  flag5s = true; // Setează flag-ul pentru a indica întreruperea la 5 secunde
  valoriTemp+=dht.readTemperature();
  numarValoriTemp++;
  valoriUmid+=(int)dht.readHumidity();
  umarValoriUmid++;
}

// Funcția de întrerupere pentru temporizatorul Timer3 (60 de secunde)
ISR(TIMER3_COMPA_vect) {
  flag60s = true; // Setează flag-ul pentru a indica întreruperea la 60 de secunde
  date.temperatura = float(valoriTemp/numarValoriTemp);
  date.umiditate = float(valoriUmid/numarValoriUmid);

  snprintf(msg, MSG_BUFFER_SIZE, "%d-%.2f-%d-%d-%s", 1111, date.temperatura, date.umiditate, date.puls, date.ecg);

  Serial.print("Publish message: ");
  Serial.println(msg);
  client.publish("Valori", msg);
}

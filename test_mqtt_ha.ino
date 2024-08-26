#include <ESP8266WiFi.h>
#include <Wire.h>
#include <PubSubClient.h>
#define ouverture_pin 14
#define ouverturepieton_pin 12
#define fermeture_pin 13
//****************** CONFIGURATION ******************
#define wifi_ssid "Livebox-32C0"
#define wifi_password "JcVVqjJrUrviKTMGaG"
//#define wifi_ssid1 "Freebox-38B461"
//#define wifi_password1 "cordi-transmutat9-dimidiis-famino"

#define mqtt_server "90.19.66.96" 
#define mqtt_user "MQTT_BOT"
#define mqtt_password "WZfe5kmZptP5Dun"


#define temperature_topic "/portail"
//****************** CONFIGURATION ******************

WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0;
float temp = 0.0;

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    Serial.println("ouverture pieton");
    digitalWrite(ouverturepieton_pin, HIGH);
    digitalWrite(LED_BUILTIN, LOW);
    client.publish(temperature_topic, String(0).c_str(), true);
    delay(500);
    digitalWrite(ouverturepieton_pin, LOW); 
    digitalWrite(LED_BUILTIN, HIGH); 
  }
  else if ((char)payload[0] == '2') {
    Serial.print("ouverture");
    digitalWrite(ouverture_pin, HIGH);
    digitalWrite(LED_BUILTIN, LOW);
    client.publish(temperature_topic, String(0).c_str(), true);
    delay(500);
    digitalWrite(ouverture_pin, LOW); 
    digitalWrite(LED_BUILTIN, HIGH); 
  }
  else if ((char)payload[0] == '3') {
    Serial.print("fermeture");
    digitalWrite(fermeture_pin, HIGH);
    digitalWrite(LED_BUILTIN, LOW);
    client.publish(temperature_topic, String(0).c_str(), true);
    delay(500);
    digitalWrite(fermeture_pin, LOW); 
    digitalWrite(LED_BUILTIN, HIGH); 
  }
  
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(ouverturepieton_pin, OUTPUT);
  pinMode(ouverture_pin, OUTPUT);
  pinMode(fermeture_pin, OUTPUT);
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void setup_wifi() {
  delay(10);
  // Connect to a WiFi network
  Serial.println();
  Serial.print("Connecting Wi-Fi...");
  Serial.println(wifi_ssid);

  WiFi.begin(wifi_ssid, wifi_password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Connected:");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Connecting MQTT...");
    // Attempt to connect

    if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
      Serial.println("connected");
      client.subscribe("/portail");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 5000) { // publish frequency
     lastMsg = now;
  }
}

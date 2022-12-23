#include <WiFi.h>
#include <PubSubClient.h>
#include "DHTesp.h"
#include <ThingsBoard.h>

//ThingsBoardES

//DHT22
const int DHT_PIN = 15;

// WiFi
const char *ssid = "Wokwi-GUEST"; // Enter your WiFi name
const char *password = "";  // Enter WiFi password

// MQTT Broker
const char *mqtt_broker = "broker.emqx.io";
const char *topic = "esp32/test/ahmadjaelani";
const char *mqtt_username = "emqx";
const char *mqtt_password = "public";
const int mqtt_port = 1883;
char buffer[10];
char buffer2[10];

#define TOKEN "p8naRCywPXbzidxyPsqa ";

WiFiClient espClient;
PubSubClient client(espClient);
DHTesp dhtSensor;
ThingsBoard tb(espClient);

void setup() {
 // Set software serial baud to 115200;
 Serial.begin(115200);
 // connecting to a WiFi network
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.println("Connecting to WiFi..");
 }
 Serial.println("Connected to the WiFi network");
 //connecting to a mqtt broker
 client.setServer(mqtt_broker, mqtt_port);
 client.setCallback(callback);
 while (!client.connected()) {
     String client_id = "esp32-client-";
     client_id += String(WiFi.macAddress());
     Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
     if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
         Serial.println("Public emqx mqtt broker connected");
     } else {
         Serial.print("failed with state ");
         Serial.print(client.state());
         delay(2000);
     }
 }
 dhtSensor.setup(DHT_PIN, DHTesp::DHT22);
 // publish and subscribe
 client.publish(topic, "Hi EMQX I'm ESP32 from ahmad jaelani ^^");
 client.subscribe(topic);

}

void callback(char *topic, byte *payload, unsigned int length) {
 Serial.print("Message arrived in topic: ");
 Serial.println(topic);
 Serial.print("Message:");
 for (int i = 0; i < length; i++) {
     Serial.print((char) payload[i]);
 }
 Serial.println();
 Serial.println("-----------------------");
}

void loop() {
 
  TempAndHumidity  data = dhtSensor.getTempAndHumidity();
  //client.publish(topic, "Hi EMQX I'm ESP32 from ahmad jaelani ^^");
  sprintf(buffer,"%.2f",data.temperature);
    client.publish(topic, buffer);
  //client.publish(topic,("Humidity: " + String(data.humidity, 1) + "%"));
  delay(1500);
  client.loop();
}
///// Libraries Needed
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266httpUpdate.h>
#include <PubSubClient.h>

// #define DEBUG

//// Timer for Outlet
unsigned long previousMillis = 0;
const long interval = 1800000;  //// 1800000 = 30 Minutes; 300000 = 5 Minutes; 60000 = 1 Minute
boolean autoOutlet1 = false;

//// Timers for LEDs
boolean starLights = false;
boolean nightLight = false;
unsigned long starPreviousMillis = 0;
const long starInterval = 1200000;  //// 1200000 = 20 Minutes; 300000 = 5 Minutes; 60000 = 1 Minute
unsigned long nightPreviousMillis = 0;
const long nightInterval = 3600000; //// 3600000 = 60 Minutes; 300000 = 5 Minutes; 60000 = 1 Minute

//// Setup Outlet State(s)
int outlet1 = 0;
int outlet2 = 0;

//// Setup PWM State(s)
int ledChannelOne = 0;
int ledChannelTwo = 0;
int ledChannelThree = 0;
int ledChannelFour  = 0;
boolean ledChannelOneState = false;
boolean ledChannelTwoState = false;
boolean ledChannelThreeState = false;
boolean ledChannelFourState = false;

//// Setup Update State
int checkForUpdate = 0;

//// WiFi Configuration
char myhostname[] = "##########"; /// Device Name for ESP8266
const char* ssid = "##########"; /// Local Wireless SSID
const char* password = "##########"; /// Local Wireless Password
WiFiClient espClient;

//// Setup MQTT Messaging
const char* mqtt_server = "##########"; /// MQTT Server FQDN address
const char* ver = "##########"; /// Version Control for device
PubSubClient client(espClient);
long lastReconnectAttempt = 0;
unsigned long mqttPreviousMillis = 1;
const long publishInterval = 2000;

//// Setup Controller
void setup() {
  //// Setup Serial Montioring
  #ifdef DEBUG
  Serial.begin(115200);
  while (!Serial){
  }
  #endif
  outletSetup();
  ledSetup();
  beginNetwork();
  setupMQTT();
  lastReconnectAttempt = 0;
}

//// Main Loop
void loop() {
  mqttCheckConnection();
  client.loop();
  mqttPublish();
  ledStatePublish(); 
  if (autoOutlet1 == true) {
    autoOutlet1Control();
  } 
  if (starLights == true) {
    starLightsControl();
  }
  if (nightLight == true) {
    nightLightControl(); 
  }
}  

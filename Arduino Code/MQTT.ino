void setupMQTT(){
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

boolean reconnect() {
  if (client.connect("#########")) { /// Name your MQTT Client, all need to be unique
    // Once connected, publish an announcement...
    client.publish("test/status", "Online");
    client.publish("test/status", ver);
    // ... and resubscribe
      client.subscribe("test/ledChannel1");
        client.loop();
      client.subscribe("test/ledChannel2");
        client.loop();
      client.subscribe("test/ledChannel3");
        client.loop();
      client.subscribe("test/ledChannel4");
        client.loop();
      client.subscribe("test/outlet1");
        client.loop();
      client.subscribe("test/outlet2");
        client.loop();
      client.subscribe("test/autoOutlet1");
        client.loop();
      client.subscribe("test/starLights");
        client.loop();
      client.subscribe("test/nightLight");
        client.loop();
      client.subscribe("test/update");
        client.loop();
  }
  return client.connected();
}

void callback(char* topic, byte* payload, unsigned int length) {
  if(strcmp(topic, "test/ledChannel1") == 0) {
    #ifdef DEBUG  
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    #endif
    String value = "";
    for (int i = 0; i < length; i++) {
      #ifdef DEBUG
      Serial.print((char)payload[i]);
      #endif
      value += (char)payload[i]; 
    }
    if(value.toInt() != ledChannelOne){
      ledChannelOneState = true;
    }    
    ledChannelOne = value.toInt();
    leds();
    #ifdef DEBUG
    Serial.println();
    #endif
  }

  if(strcmp(topic, "test/ledChannel2") == 0) {
    #ifdef DEBUG
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    #endif
    String value = "";
    for (int i = 0; i < length; i++) {
      #ifdef DEBUG
      Serial.print((char)payload[i]);
      #endif
      value += (char)payload[i]; 
    }
    if(value.toInt() != ledChannelTwo){
      ledChannelTwoState = true;
    }      
    ledChannelTwo = value.toInt(); 
    leds();
    #ifdef DEBUG
    Serial.println();
    #endif    
  }    

  if(strcmp(topic, "test/ledChannel3") == 0) {
    #ifdef DEBUG
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    #endif
    String value = "";
    for (int i = 0; i < length; i++) {
      #ifdef DEBUG
      Serial.print((char)payload[i]);
      #endif
      value += (char)payload[i]; 
    }
    if(value.toInt() != ledChannelThree){
      ledChannelThreeState = true;
    }    
    ledChannelThree = value.toInt();
    leds(); 
    #ifdef DEBUG
    Serial.println();
    #endif  
  }

  if(strcmp(topic, "test/ledChannel4") == 0) {
    #ifdef DEBUG
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    #endif
    String value = "";
    for (int i = 0; i < length; i++) {
      #ifdef DEBUG
      Serial.print((char)payload[i]);
      #endif
      value += (char)payload[i]; 
    }
    if(value.toInt() != ledChannelFour){
      ledChannelFourState = true;
    }    
    ledChannelFour = value.toInt();
    leds();
    #ifdef DEBUG
    Serial.println();
    #endif    
  }

  if(strcmp(topic, "test/outlet1") == 0) {
    #ifdef DEBUG
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    #endif
    String value = "";
    for (int i = 0; i < length; i++) {
      #ifdef DEBUG
      Serial.print((char)payload[i]);
      #endif
      value += (char)payload[i]; 
    }
    outlet1 = value.toInt();
    outletPort1(); 
    #ifdef DEBUG
    Serial.println();
    #endif
  }

  if(strcmp(topic, "test/outlet2") == 0) {
    #ifdef DEBUG
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    #endif
    String value = "";
    for (int i = 0; i < length; i++) {
      #ifdef DEBUG
      Serial.print((char)payload[i]);
      #endif
      value += (char)payload[i]; 
    }
    outlet2 = value.toInt();
    outletPort2();
    #ifdef DEBUG 
    Serial.println();
    #endif
  }

  if(strcmp(topic, "test/update") == 0) {
    #ifdef DEBUG
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    #endif
    String value = "";
    for (int i = 0; i < length; i++) {
      #ifdef DEBUG
      Serial.print((char)payload[i]);
      #endif
      value += (char)payload[i]; 
    }
    checkForUpdate = value.toInt();
    espUpdate();
    #ifdef DEBUG
    Serial.println();
    #endif
  }

  if(strcmp(topic, "test/autoOutlet1") == 0) {
    #ifdef DEBUG
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    #endif
    String value = "";
    for (int i = 0; i < length; i++) {
      #ifdef DEBUG
      Serial.print((char)payload[i]);
      #endif
      value += (char)payload[i]; 
    }
  if(value.toInt() == 0){
    outlet1 = value.toInt();
    outletPort1();
    autoOutlet1 = false;
  }
  if(value.toInt() == 1){
    previousMillis = millis();
    outlet1 = value.toInt();
    outletPort1();
    autoOutlet1 = true;
  }
  #ifdef DEBUG
  Serial.println();
  #endif
  }  

  if(strcmp(topic, "test/starLights") == 0) {
    #ifdef DEBUG
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    #endif
    String value = "";
    for (int i = 0; i < length; i++) {
      #ifdef DEBUG
      Serial.print((char)payload[i]);
      #endif
      value += (char)payload[i]; 
   }
  if(value.toInt() == 0){
    ledChannelOne = 0;
    ledChannelTwo = 0;
    ledChannelThree = 0;
    leds();
    ledChannelOneState = true;
    ledChannelTwoState = true;
    ledChannelThreeState = true;
    starLights = false;
    }
  if(value.toInt() == 1){
    starPreviousMillis = millis();
    ledChannelOne = 255;
    ledChannelTwo = 100;
    ledChannelThree = 10;
    leds();
    ledChannelOneState = true;
    ledChannelTwoState = true;
    ledChannelThreeState = true;
    starLights = true;    
    }
    #ifdef DEBUG
    Serial.println();
    #endif
  }

  if(strcmp(topic, "test/nightLight") == 0) {
    #ifdef DEBUG
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    #endif
    String value = "";
    for (int i = 0; i < length; i++) {
      #ifdef DEBUG
      Serial.print((char)payload[i]);
      #endif
      value += (char)payload[i]; 
    }
  if(value.toInt() == 0){
    ledChannelFour = 0;
    leds();
    nightLight = false;
    ledChannelFourState = true;   
    }
  if(value.toInt() == 1){
    nightPreviousMillis = millis();
    ledChannelFour = 500;
    leds();
    nightLight = true;
    ledChannelFourState = true;      
    }
  #ifdef DEBUG
  Serial.println();
  #endif
  }    
}

void mqttCheckConnection() {
  if (!client.connected()) {
    long now = millis();
    if (now - lastReconnectAttempt > 5000) {
      lastReconnectAttempt = now;
      // Attempt to reconnect
      if (reconnect()) {
        lastReconnectAttempt = 0;
      }
    }
  } else {
    // Client connected
    client.loop();
  }

} 

const int bufferLen = 256;
char jsonMessage[bufferLen];

void mqttPublish() {
  unsigned long mqttPubMillis = millis();
  if (mqttPubMillis - mqttPreviousMillis >= publishInterval) {
    mqttPreviousMillis = mqttPubMillis;
    const char* jsonTopic = "test/json";
    int length;
    DynamicJsonBuffer  jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();
  
    jsonData(root);
  
    length = root.printTo(jsonMessage, bufferLen);
    client.publish(jsonTopic, jsonMessage, true);  
  }
}

void jsonData(JsonObject& root) {
  root["version"] = ver;
  root["ledChannel1"] = ledChannelOne;
  root["ledChannel2"] = ledChannelTwo;
  root["ledChannel3"] = ledChannelThree;
  root["ledChannel4"] = ledChannelFour;
  root["outlet1"] = outlet1;
  root["outlet2"] = outlet2; 
  root["autoOutlet1"] = autoOutlet1;
  root["starLights"] = starLights;
  root["nightLight"] = nightLight;
}


void ledStatePublish() {
  if (ledChannelOneState == true) {
    char msgBuffer[20];
    client.publish("test/ledChannel1", dtostrf(ledChannelOne, 4, 0, msgBuffer), true);
    client.loop();  
    ledChannelOneState = false;  
  }
  if (ledChannelTwoState == true) {
    char msgBuffer[20];
    client.publish("test/ledChannel2", dtostrf(ledChannelTwo, 4, 0, msgBuffer), true);
    client.loop();
    ledChannelTwoState = false;    
  }
  if (ledChannelThreeState == true) {
    char msgBuffer[20];
    client.publish("test/ledChannel3", dtostrf(ledChannelThree, 4, 0, msgBuffer), true);
    client.loop();   
    ledChannelThreeState = false; 
  }
  if (ledChannelFourState == true) {
    char msgBuffer[20];
    client.publish("test/ledChannel4", dtostrf(ledChannelFour, 4, 0, msgBuffer), true);
    client.loop();   
    ledChannelFourState = false; 
  }
}

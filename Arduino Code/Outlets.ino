//// Setup Outlet Pin(s)
const int outletPin1 = 13;
const int outletPin2 = 14;

void outletSetup()  {
  //// Setup LED for Testing
  pinMode(outletPin1, OUTPUT);
  pinMode(outletPin2, OUTPUT);
  digitalWrite(outletPin1, 1);
  digitalWrite(outletPin2, 1);
}

/*
 * Outlet configuration:
 * oulet1 and outlet2 are MQTT modifiers 0 = off 1 = on
 * outletPin1 and outletPin2 are physical pins on controller
 * outletPin# == 0 the pin is pulled LOW
 * outletPin# == 1 the pin is pulled HIGH
 * Relay module in lab is a LOW trigger on, HIGH trigger off
 */

void outletPort1() {
  if ((outlet1 == 0) && (digitalRead(outletPin1) == 1)) { 
    return;
  }
  else {
    if (outlet1 == 0) {
      digitalWrite(outletPin1, 1);
      client.publish("test/status", "Turned Outlet 1 - Off");
      #ifdef DEBUG
      Serial.println(F("Turn Outlet 1 Off"));
      #endif
    }
  }
  if ((outlet1 == 1) && (digitalRead(outletPin1) == 0)) {
    return;
     }
     else {
      if (outlet1 == 1) {
        digitalWrite(outletPin1, 0);
        client.publish("test/status", "Turned Outlet 1 - On");
        #ifdef DEBUG
        Serial.println(F("Turn Outlet 1 On"));
        #endif
        
      }
   }
}

void outletPort2() {
  if ((outlet2 == 0) && (digitalRead(outletPin2) == 1)) {
  return;
  }
  else {
    if (outlet2 == 0) {
      digitalWrite(outletPin2, 1);
      client.publish("test/status", "Turned Outlet 2 - Off");
      #ifdef DEBUG
      Serial.println(F("Turn Outlet 2 Off"));
      #endif
    }
  }
  if ((outlet2 == 1) && (digitalRead(outletPin2) == 0)) {
    return;
     }
     else {
      if (outlet2 == 1) {
        digitalWrite(outletPin2, 0);
        client.publish("test/status", "Turned Outlet 2 - On");
        #ifdef DEBUG
        Serial.println(F("Turn Outlet 2 On"));
        #endif 
      }
   }
}

void autoOutlet1Control() {
  unsigned long currentMillis = millis();
  if ((unsigned long)(currentMillis - previousMillis) >= interval) {
    previousMillis = currentMillis;
    digitalWrite(outletPin1,1);         // Turn outlet off after time has passed
    autoOutlet1 = false;                // Set Auto Outlet Control value back to off
    outlet1 = 0;                        // Set the outlet value back to zero
    client.publish("test/status", "Turned Automated Outlet 1 - Off");
    client.publish("test/autoOutlet1", "0", true);
  }
}


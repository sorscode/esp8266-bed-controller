//// Setup LED Pin(s)
const int channel1 = 2;
const int channel2 = 4;
const int channel3 = 5;
const int channel4 = 12;

void ledSetup(){
  //// Setup LED for Testing
  pinMode(channel1, OUTPUT);
  pinMode(channel2, OUTPUT);
  pinMode(channel3, OUTPUT);
  pinMode(channel4, OUTPUT);
}


//// Setup PWM for LED(s)
void leds() {
  channelOne();
  channelTwo();
  channelThree();
  channelFour();
}

void channelOne() {
  analogWrite(channel1, ledChannelOne); 
}

void channelTwo() {
  analogWrite(channel2, ledChannelTwo);
}

void channelThree() {
  analogWrite(channel3, ledChannelThree);
}

void channelFour() {
  analogWrite(channel4, ledChannelFour);
}

void starLightsControl() {
   unsigned long currentMillis = millis();
      if ((unsigned long)(currentMillis - starPreviousMillis) >= starInterval) {
        starPreviousMillis = currentMillis;
        ledChannelOne = 0;
        ledChannelTwo = 0;
        ledChannelThree = 0;
        leds();
        ledChannelOneState = true;
        ledChannelTwoState = true;
        ledChannelThreeState = true;
        starLights = false;      
        client.publish("test/status", "Turned Star LEDs Off");
        client.publish("test/starLights", "0", true);
      }
}

void nightLightControl() {
   unsigned long currentMillis = millis();
      if ((unsigned long)(currentMillis - nightPreviousMillis) >= nightInterval) {
        nightPreviousMillis = currentMillis;
        ledChannelFour = 0;
        leds();
        ledChannelFourState = true;
        nightLight = false;      
        client.publish("test/status", "Turned Star LEDs Off");
        client.publish("test/nightLight", "0", true);
      }
}

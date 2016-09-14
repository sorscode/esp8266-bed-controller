# esp8266-bed-controller

## Description:
I built this for my daughters 6th birthday. She wanted star lights in her canopy bed, along with lights under her bed for a night light. So I used an Adafruit ESP8266 Huzzah, with 4 Meanwell LDD Drivers, a 2-Channel Relay Module, and a bunch of LEDs. For power, I currently use a 48V 2A, for the LEDs, and a 5V 1A for the ESP8266.  

There is three folders with all the code. Here is brief information for each:

## Features:
- Arduino code to get everything running
- MQTT
- JSON
- Timers for the LED Channels
- Timers for the Outlets
- Over the Air updating
  
Things you would need to update to make it work:
- MQTT.ino
  - update "if (client.connect("#########"))" Update the "#########" to a unique MQTT Client Name
- OTA.ino
  - update "fqdn.domain.com" to your server that will host your bin files
- esp8266-bed-controller.ino
  - char myhostname[] = "##########"; Update this line to a unique hostname, can be the same as MQTT Client Name
  - const char* ssid = "##########"; Update this line to match your Wireless SSID
  - const char* password = "##########"; Update this line to your Wireless SSID Password
  - const char* mqtt_server = "##########"; Update this line to point to your FQDN MQTT Server
  - const char* ver = "##########"; Update this line for version control, and for OTA to work right
      
## Web Interface:
All the code for the web interface to talk to the ESP8266
- Admin Page (admin.php)
- Full control over the LED PWM, on all 4 channels
- Manually turn outlets on and off, with no timers that shut them back off
- Update button, to make ESP8266 check for updated code

- User Page (index.php)
- Three simple toggle switchs
- Turn Lamp (outlet1) on or off
  - This is also on a timer, and will turn off automatically
- Turn Star Lights on or off
  - This is also on a timer for the first three channels, and will turn off automatically
- Turn night Light on or off
  - This is also on a timer for the fourth channel, and will turn off automatically
  
The remaining files are php files to connect to your MQTT server
- Edit controller.php
    - $host = "mqtt.domain.com"; Update this line to point to your server hosting your MQTT Server
          
## esp8266_ota_webpage:
This is the code I use to update my ESP8266 over-the-air.
- Create a folder where you put this php file on your webserver, and call it "bin"
- When you update your code for the ESP8266 update the "const char* ver = "##########";
- Update this php file, to match the MAC address of your ESP8266 and the "const char* ver"
- Then on the Admin page, you can then click update, and the ESP8266 will send parameters to this PHP, and if the version is different than what was received from the ESP8266 it will send the new bin file, if not, it will send back No Update code. It's important to name your bin files, with the same name as "const char* ver". 
  - Example const char* ver = "testdevice-v1.0.6a"; 
  - bin file bin/testdevice-v1.0.6a.bin

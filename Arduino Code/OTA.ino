//// Check for Firmware Update - Checks to see if new version is available
void espUpdate(){
  if (checkForUpdate == 1) {
    t_httpUpdate_return ret = ESPhttpUpdate.update("fqdn.domain.com", 80, "/arduino.php", ver); /// Need to update fqdn.domain.com to your repository
    switch(ret) {
      case HTTP_UPDATE_FAILED:
        client.publish("test/status", "Update failed");
        client.publish("test/update", "0", true);
        #ifdef DEBUG
        Serial.println("Update failed");
        #endif
        break;
      case HTTP_UPDATE_NO_UPDATES:
        client.publish("test/status", "No Update");
        client.publish("test/update", "0", true);
        #ifdef DEBUG
        Serial.println("No Update");
        #endif
        break;
 /*     case HTTP_UPDATE_OK:
        #ifdef DEBUG
        Serial.println("Update ok.");
        #endif
*/          
    }
  }
 else {
  return;
 }
}


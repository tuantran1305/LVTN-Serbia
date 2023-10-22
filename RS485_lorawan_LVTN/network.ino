void setup_lora() {
  if (!lora.init()) {
    Serial.println("RFM95 not detected");
    delay(2000);
    return;
  }
  lora.setDeviceClass(CLASS_C);
  lora.setDataRate(SF10BW125);
  lora.setChannel(MULTI);
  lora.setDevEUI(DEV_EUI.c_str());
  lora.setAppEUI(APP_EUI.c_str());
  lora.setAppKey(APP_KEY.c_str());
  bool isJoined;
  do {
    for (int i = 0; i < 4; i++) {
      if (millis() - Millis > 3000) {
        Serial.println("Joining...");
        isJoined = lora.join();
        Millis = millis();
      }
      chain = "----";
      led_7segment();
    }
  } while (!isJoined);
  Serial.println("Joined to network");
  delay(500);
  char myStr[50] = "{\"state\":\"true\"}";
  Serial.print("Sending: ");
  Serial.println(myStr);
  lora.sendUplink(myStr, strlen(myStr), 0, 1);
  lora_state = true;
  LED_ON();
  delay(100);
}
void uplink_lorawan() {
  Data_Lorawan = "{\"temp\":\"" + String(float(Temp / 10.0))
                 + "\"," + "\"hum\":\"" + String(float(Hum / 10.0)) + "\"," + "\"pH\":\"" + String(pHValue, 2) + "\"," + "\"pump\":\"" + statePump + "\"}";
  /* Processing myStr. */
  int str_len = Data_Lorawan.length() + 1;
  char Data[str_len];
  Data_Lorawan.toCharArray(Data, str_len);
  Serial.println((char *)Data);
  LED_ON();
  delay(150);
  LED_OFF();
  lora.sendUplink(Data, strlen(Data), 0, 1);
  counter++;
}
void restartESP() {
  buttonState = digitalRead(SMART_CONFIG);
  if (buttonState != lastButtonState) {
    if (buttonState == LOW) {
      buttonCounter++;
      //      Serial.println(buttonCounter);
    }
    lastButtonState = buttonState;
    timeButton = millis();
  }
  if (millis() - timeButton > 3000) {
    buttonCounter = 0;
  }
  if (buttonCounter == 3) {
    Serial.println("Restart");
    ESP.restart();
  }
}

void Read_Eui_From_EEPROM()
{
  for (int i = 300; i < 330; ++i)
  {
    DEV_EUI += char(EEPROM.read(i));
  }
  DEV_EUI.remove(DEV_EUI.indexOf(0));
  for (int i = 330; i < 360; ++i)
  {
    APP_EUI += char(EEPROM.read(i));
  }
  APP_EUI.remove(APP_EUI.indexOf(0));
  for (int i = 360; i < 400; ++i)
  {
    APP_KEY += char(EEPROM.read(i));
  }
  APP_KEY.remove(APP_KEY.indexOf(0));

  for (int i = 400; i < 401; ++i)
  {
    battery_state = EEPROM.read(i);
  }
  Serial.println(DEV_EUI);
  Serial.println(APP_EUI);
  Serial.println(APP_KEY);
  Serial.println(battery_state);
}

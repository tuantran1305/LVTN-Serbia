void check_pos()
{
  if (!lora_state && !rs485_state)
  {
    for (int i = 0; i < 4; i++)
    {
      pos_led[i] = pos[i];
    } 
  }
  else if (lora_state && !rs485_state)
  {
    for (int i = 0; i < 4; i++)
    {
      pos_led[i] = pos[i];
      pos_led[i] |= 0x20;
    }
  }
  else if (!lora_state && rs485_state)
  {
    for (int i = 0; i < 4; i++)
    {
      pos_led[i] = pos[i];
      pos_led[i] |= 0x10;
    }
  }
  else
  {
    for (int i = 0; i < 4; i++)
    {
      pos_led[i] = pos[i];
      pos_led[i] |= 0x30;
    }
  }
}
void callback()
{
  if (count_led != 3)
  {
    count_led = count_led + 1;
  }
  else
  {
    count_led = 0;
  }
  digitalWrite(LATCH_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, hex[count_led]);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, pos_led[count_led]);
  digitalWrite(LATCH_PIN, HIGH);
}
void led_7segment()
{
  dot = -1;
  String chain_ = chain;
  if (chain_.length() == 5)
  {
    for (int i = 0; i < chain_.length(); i++) {
      char character = chain_.charAt(i);
      if (character == '.')
      {
        dot = i - 1;
        chain_.remove( dot + 1, 1);
      }
    }
  }
  for (int i = 0; i < chain_.length(); i++) {
    char character = chain_.charAt(i);
    byte HexText = charTohex(character);
    if (dot == i)
    {
      HexText |= 0x80;
    }
    hex[i] = HexText;
  }
}

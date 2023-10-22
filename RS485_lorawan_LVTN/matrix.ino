byte charTohex(char index)
{
  byte hex_char_value;
  char char_index = index;
  if (char_index == ' ')
  {
    hex_char_value = 0x00;
  }
  if (char_index == 'A')
  {
    hex_char_value = 0x77;
  }
  if (char_index == 'C')
  {
    hex_char_value = 0x39;
  }
  if (char_index == 'D')
  {
    hex_char_value = 0x3F;
  }
  if (char_index == 'E')
  {
    hex_char_value = 0x79;
  }
  if (char_index == 'F')
  {
    hex_char_value = 0x71;
  }
  if (char_index == 'H')
  {
    hex_char_value = 0x76;
  }
  if (char_index == 'L')
  {
    hex_char_value = 0x38;
  }
  if (char_index == 'O')
  {
    hex_char_value = 0x3F;
  }
  if (char_index == 'N')
  {
    hex_char_value = 0x54;
  }
  if (char_index == 'P')
  {
    hex_char_value = 0x73;
  }
  if (char_index == 'R')
  {
    hex_char_value = 0x31;
  }
  if (char_index == 'S')
  {
    hex_char_value = 0x6D;
  }
  if (char_index == 'U')
  {
    hex_char_value = 0x3E;
  }
  if (char_index == '-')
  {
    hex_char_value = 0x40;
  }


  if (char_index == '0')
  {
    hex_char_value = 0x3F;
  }
  if (char_index == '1')
  {
    hex_char_value = 0x06;
  }
  if (char_index == '2')
  {
    hex_char_value = 0x5B;
  }
  if (char_index == '3')
  {
    hex_char_value = 0x4F;
  }
  if (char_index == '4')
  {
    hex_char_value = 0x66;
  }
  if (char_index == '5')
  {
    hex_char_value = 0x6D;
  }
  if (char_index == '6')
  {
    hex_char_value = 0x7D;
  }
  if (char_index == '7')
  {
    hex_char_value = 0x07;
  }
  if (char_index == '8')
  {
    hex_char_value = 0x7F;
  }
  if (char_index == '9')
  {
    hex_char_value = 0x6F;
  }

  return hex_char_value;
}

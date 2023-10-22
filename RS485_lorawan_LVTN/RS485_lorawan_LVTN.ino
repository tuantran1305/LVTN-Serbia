/* Library. */
#include "main.h"
#include "FreeRTOS.h"
/* Word FreeRtos*/
void Main_Process(void *parameter) {
  while (1) {
    check_pos();
    led_7segment();
    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}
void Display_Led(void *parameter) {
  while (1) {
    if (millis() - previous_led > 1500) {
      if (led_number < 3) {
        ++led_number;
      } else {
        led_number = 0;
      }
      chain = led_string[led_number];
      Serial.println(chain);
      previous_led = millis();
    }
    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}
void Read_Temp(void *parameter) {
  while (1) {
    static unsigned long samplingTime = millis();
    if (millis() - samplingTime > samplingInterval) {
      pHArray[pHArrayIndex++] = analogRead(SensorPin);
      if (pHArrayIndex == ArrayLenth) pHArrayIndex = 0;
      voltage = avergearray(pHArray, ArrayLenth) * 5.0 / 4095;
      pHValue = 2.5 * voltage + Offset;
      samplingTime = millis();
    }
    if (statePump && control) {
      controlRS485On();
      delay(100);
      control = false;
    }
    if (!statePump && control) {
      controlRS485Off();
      delay(100);
      control = false;
    }
    if (millis() - previous_time_sensor > 10000) {
      readRS485();
      Serial.print("pH value: ");
      Serial.println(pHValue, 2);
      // led_string[5] = String(pHValue) + "PH";
      previous_time_sensor = millis();
    }
  }
}
void Send_Data_To_Server(void *parameter) {
  while (1) {
    if (millis() - previousMillis_data > interval_data) {
      uplink_lorawan();
      previousMillis_data = millis();
      vTaskDelay(100 / portTICK_PERIOD_MS);
    }
    recvStatus = lora.readData(outStr);
    if (recvStatus) {
      int count_label = 0;
      Serial.println(outStr);
      JSONVar object = JSON.parse(outStr);
      JSONVar key = object.keys();
      Serial.println(key);
      Serial.println(object);
      for (int i = 0; i < key.length(); i++) {
        if (JSON.stringify(key[i]).indexOf("relay") != -1) {
          control = true;
          delay(100);
          if (bool((object[key[i]])) == true) {
            statePump = true;
            controlRS485On();
          } else {
            statePump = false;
            controlRS485Off();
          }
        }
      }
    }
    lora.update();
    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}
void setup() {
  setCpuFrequencyMhz(240);
  /* Basic Setting */
  Serial.begin(9600);
  EEPROM.begin(512);
  /* Setting Input/Output. */
  pinMode(LDO, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(PIN_LED, OUTPUT);
  pinMode(SMART_CONFIG, INPUT);
  pinMode(RS485_PIN_DIR, OUTPUT);
  digitalWrite(LDO, HIGH);

  digitalWrite(RS485_PIN_DIR, RS485Transmit);
  RS485Serial.begin(9600, SWSERIAL_8N1);
  LED_OFF();
  delay(20);
  Read_Eui_From_EEPROM();
  delay(1000);
  timer.attach(0.005, callback);
  timer1.attach(0.1, restartESP);
  Serial.println("active mode");
  /* Setting RS485. */
  setup_lora();
  /*Set up FreeRtos. */
  xTaskCreatePinnedToCore(Main_Process, "Task0", 4000, NULL, 1, &Main_Process_p, 1);
  xTaskCreatePinnedToCore(Read_Temp, "Task1", 4000, NULL, 1, &Read_Temp_p, 0);
  xTaskCreatePinnedToCore(Send_Data_To_Server, "Task2", 6000, NULL, 1, &Send_Data_To_Server_p, 0);
  xTaskCreatePinnedToCore(Display_Led, "Task3", 6000, NULL, 1, &Display_Led_p, 1);
  disableCore0WDT();
}
void loop() {
}

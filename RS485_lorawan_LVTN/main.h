/*Library */
#include <EEPROM.h>
#include <SoftwareSerial.h>
#include <Crc16.h>
#include <math.h>
#include <Ticker.h>
#include <lorawan.h>
#include <Arduino_JSON.h>
Ticker timer;
Ticker timer1;
Crc16 crc;
/***************************** Lorawan *****************************/
/* LORAWAN EUI */
String DEV_EUI = "";
String APP_EUI = "";
String APP_KEY = "";
/* LORAWAN Setpin */
const sRFM_pins RFM_pins{
  .CS = 15,
  .RST = 33,
  .DIO0 = 32,
  .DIO1 = 35,
  .DIO2 = 23,
  .DIO5 = 23,
};
/* LORAWAN downlink */
char outStr[255];
byte recvStatus = 0;
/***************************** pH*****************************/
int percent;
float humground = 0;
static float pHValue, voltage;
#define SensorPin 36  //pH meter Analog output to Arduino Analog Input 0
#define Offset 0.00   //deviation compensate
#define samplingInterval 20
#define printInterval 800
#define ArrayLenth 40     //times of collection
int pHArray[ArrayLenth];  //Store the average value of the sensor feedback
int pHArrayIndex = 0;
/***************************** RS485 *****************************/
int count_RS485 = 0;
int RS485_count = 0;
/* Declare RS485. */
#define RXD2 26
#define TXD2 27
#define RS485_PIN_DIR 25
#define RS485Transmit HIGH
#define RS485Receive LOW
SoftwareSerial RS485Serial(RXD2, TXD2);
/* Declare Variable. */
uint8_t byteTemperature[6] = { 0x02, 0x03, 0x00, 0x00, 0x00, 0x02 };
uint8_t controlOn[8] = { 0x01, 0x05, 0x00, 0x00, 0xFF, 0x00, 0x8C, 0x3A };
uint8_t controlOff[8] = { 0x01, 0x05, 0x00, 0x00, 0x00, 0x00, 0xCD, 0xCA };

uint8_t byteSend_RS485[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
uint8_t byte_RS485[6] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
uint8_t byteReceived_RS485[9];
int Hum, Temp;
float temperature_float = 0, humidity_float = 0;
bool statePump = false;
String Data_Lorawan;
bool control = false;
/***************************** Setup Variable and Pin *****************************/
/* Time variable. */
unsigned long Millis = 0;
unsigned long previousMillis_data = 0;
unsigned long interval_data = 20000;
unsigned long previous_time = 0;
unsigned long previous_time_sensor = 0;
unsigned long previous_led = 0;
unsigned int counter = 0;  // message counter
unsigned int timer_previous = 0;
/*Setting GPIO*/
/* Declare RS485. */
#define LDO 4
#define PIN_LED 18
#define LED_ON() digitalWrite(PIN_LED, HIGH)
#define LED_OFF() digitalWrite(PIN_LED, LOW)
/*Setting EEPROM*/
#define SMART_CONFIG 5
int buttonState = 0;
int lastButtonState = 0;
int buttonCounter = 0;
long timeButton = 0;
bool battery_state = false;
bool state = true;
/***************************** LED 7 Segment *****************************/
/*Setting pin LED7Segment*/
int led_number = 0;
String led_string[] = { "RS--", "---H", "HU--", "PH--", "--PH" };
byte hex[] = { 0x00, 0x00, 0x00, 0x00 };
int count_led = 0, dot;
String chain = "----";
#define LATCH_PIN 21  // ST_CP
#define CLOCK_PIN 22  // SH_CP
#define DATA_PIN 19   //DS
/*Setting variable LED7Segment*/
byte ledSegments[] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F };  //K common
byte pos[] = { 0x0E, 0x0D, 0x0B, 0x07 };
byte pos_led[] = { 0x0E, 0x0D, 0x0B, 0x07 };
int arr[] = { 0, 0, 0, 0 };
boolean lora_state = false;
boolean rs485_state = true;
/***************************** Deepsleep Mode *****************************/
#define uS_TO_S_FACTOR 1000000
#define TIME_TO_SLEEP 120

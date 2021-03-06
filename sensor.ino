// Ethanol Sensor
// Arduino [BME Sensor, RTC, LCD, SD]

// Ryan Luk
// rcluk@ucsc.edu

// BME [TEMP, HUMIDITY, PRESSURE, GAS]
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"
#define BME_SCK 13 //21
#define BME_MISO 12 //not using
#define BME_MOSI 11 //20
#define BME_CS 10 //not using
#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME680 bme; // I2C
//Adafruit_BME680 bme(BME_CS); // hardware SPI
//Adafruit_BME680 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK);

// RTC [CLOCK]
#include "RTClib.h"
RTC_PCF8523 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// LCD [DISPLAY]
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //I forgot what these numbers correspond to
// something to do with the data transfer (look up documentation)

// SD [DATA]
#include <SPI.h>
#include <SD.h>
File myFile;
int pinCS = 53; // chip select for Arduino MEGA
//SCK = 52
//"MOSI" on sd reader = 51 (should really be MISO?)
//"MISO" on sd reader = 50 (should really be MOSI?)

void setup() {

  // Serial
  while (!Serial) {
    // wait until serial console is open
    delay(1);
  }
  Serial.begin(9600);

  // SD
  SD.begin(pinCS);
  // resets file
  if(SD.exists("data.txt")){
    SD.remove("data.txt");
  }

  // RTC
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (!rtc.initialized()) {
    Serial.println("RTC is NOT running!");

    //sets datetime to computers date and time
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  // BME
  if (!bme.begin()) {
    Serial.println(F("Could not find a valid BME680 sensor, check wiring!"));
    while (1);
  }
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms

  // LCD
  lcd.begin(20, 4);
  lcd.setCursor(0, 0);

}

void loop() {

  // UV
  float sensorVoltage;
  float sensorValue;
  sensorValue = analogRead(A1);
  sensorVoltage = sensorValue / 1023 * 3.3;

  // BME
  unsigned long endTime = bme.beginReading();
  if (endTime == 0) {
    Serial.println(F("Failed to begin reading :("));
    return;
  }
  if (!bme.endReading()) {
    Serial.println(F("Failed to complete reading :("));
    return;
  }

  lcd.setCursor(0, 0);

  // RTC
  DateTime now = rtc.now();
  if(now.second() == 0){
    lcd.clear();
    lcd.print(now.hour(), DEC);
    lcd.print(':');
    lcd.print(now.minute(), DEC);
    lcd.print(':');
    lcd.print(now.second(), DEC); 
  }
  else{
    lcd.print(now.hour(), DEC);
    lcd.print(':');
    lcd.print(now.minute(), DEC);
    lcd.print(':');
    lcd.print(now.second(), DEC);
  }
  
  // BME
  lcd.setCursor(0,1);
  lcd.print(bme.temperature);
  lcd.setCursor(6,1);
  lcd.print("*C");

  lcd.setCursor(9,1);
  lcd.print(bme.humidity);
  lcd.setCursor(15,1);
  lcd.print("%");

  lcd.setCursor(0,2);
  lcd.print(bme.pressure / 100.0);
  lcd.setCursor(7,2);
  lcd.print("hPa");

  lcd.setCursor(0,3);
  lcd.print(bme.gas_resistance / 1000.0);
  lcd.setCursor(7,3);
  lcd.print("KOhms");

  // UV
  lcd.setCursor(9,0);
  lcd.print(sensorVoltage);
  lcd.setCursor(14,0);
  lcd.print("V");

  Serial.println();
  Serial.println(now.hour());
  Serial.println(now.minute());
  Serial.println(now.second());
//  Serial.println(bme.temperature, 3);
//  Serial.println(bme.humidity, 3);
//  Serial.println(bme.pressure / 100.0, 3);
//  Serial.println(bme.gas_resistance / 1000.0, 3);
//  Serial.println(sensorVoltage);

  myFile = SD.open("data.txt", FILE_WRITE);
  if(myFile) {
    myFile.println(String(bme.temperature));
    myFile.println(String(bme.humidity));
    myFile.println(String(bme.pressure / 100.0));
    myFile.println(String(bme.gas_resistance / 1000.0));
    myFile.println(String(sensorVoltage));
    myFile.println();
    myFile.close();
  }
  
  delay(1000);
  
}

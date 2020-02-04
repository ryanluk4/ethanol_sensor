#include <Wire.h>
#include <SparkFun_HIH4030.h>

// Date and time functions using a PCF8523 RTC connected via I2C and Wire lib
#include "RTClib.h"

RTC_PCF8523 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

#include <LiquidCrystal.h>

// Example Variables
int tempAddress = 0x48;             // I2C: TMP102 Slave Address with ADD0 Grounded
float temp = 0;                     // Temperature Value either Static or Sensor Reading

// Are You Using a Temperature Sensor? 1 = YES / 0 = NO
int tempSensor = 0;

// Analog IO Pin Connected to OUT
#define HIH4030_OUT A0

// Supply Voltage - Typically 5 V
#define HIH4030_SUPPLY 5

// Library Variables
HIH4030 sensorSpecs(HIH4030_OUT, HIH4030_SUPPLY);

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {

  while (!Serial) {
    delay(1);  // for Leonardo/Micro/Zero
  }

  Serial.begin(57600);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (! rtc.initialized()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  //initializes 20 columns and 4 rows
  lcd.begin(20, 4);

  //sets the cursor to first column and first row
  lcd.setCursor(0, 0);

  Wire.begin();

  //print
  //lcd.print("Eth:");

  //sets the cursor to first column and third row
  //lcd.setCursor(0, 2);

  //print
  //lcd.print("Air:");

  //begin transmitting analog voltage data
  //Serial.begin(9600);

}

/* Serial Output of Temperature C, Sensor Voltage V, SensorRH %, and TrueRH % */
void printData(HIH4030 sensor, float temperature){
  
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.print(" C ("); Serial.print((temperature * 9/5) + 32); Serial.println(" F)");
  Serial.print("Sensor Voltage = ");
  Serial.print(sensor.vout());
  Serial.println(" V");
  Serial.print("Relative Humidity = ");
  Serial.print(sensor.getSensorRH());
  Serial.println(" %");
  Serial.print("True Relative Humidity = ");
  Serial.print(sensor.getTrueRH(temperature));
  Serial.println(" %");
  
}

void loop() {

  //print
  lcd.setCursor(0, 0);

  DateTime now = (rtc.now() - TimeSpan(0,1,26,0));

  if(now.second() == 0){
    
    lcd.clear();
    lcd.print(now.hour(), DEC);
    lcd.print(':');
    lcd.print(now.minute(), DEC);
    lcd.print(':');
    lcd.print(now.second(), DEC);

    lcd.setCursor(0,1);
    lcd.print(sensorSpecs.getTrueRH(25));
    lcd.setCursor(5,1);
    lcd.print("%");
    
  }

  else{

    lcd.print(now.hour(), DEC);
    lcd.print(':');
    lcd.print(now.minute(), DEC);
    lcd.print(':');
    lcd.print(now.second(), DEC);

    lcd.setCursor(0,1);
    lcd.print(sensorSpecs.getTrueRH(25));
    lcd.setCursor(5,1);
    lcd.print("%");

  }

  /*  IF tempSensor = 1 Utilizing a Temperature Sensor             */
  /*  IF tempSensor = 0 Utilizing a Static Value for Temperature   */
  if (tempSensor == 1) {
    temp = getTemperature();        // Get Temperature Sensor Reading
  } else if (tempSensor == 0) {
    temp = 25;                      // Static Temperature Value in C
                                    // Set by User to Desired Temperature                            
  } else {
    while (tempSensor != 1 || tempSensor != 0){
      Serial.println("ERROR: tempSensor Value Out of Range");
    }
  }

  printData(sensorSpecs, temp);     // Print Sensor Readings
  Serial.println("");               // Return Space Between Readings

  delay(1000);
  
}

/* Only Called IF Temperature Sensor is Being Used */
float getTemperature(){

  /*  IF Temperature Sensor is different from the TMP102 and not   */      
  /*    utilizing I2C via the Wire.h library, replace the code     */ 
  /*    within the getTemperature() function.                      */ 
  
  Wire.requestFrom(tempAddress,2);  // Wire.requestFrom(address, # of bytes to request)

  byte MSB = Wire.read();           // Receive byte as MSB or left-most bit
  byte LSB = Wire.read();           // Receive byte as LSB or right-most bit

  /*  TMP102 Temperature Register 12-bit, read-only, two's compliment for negative */
  /*  << is bit shift left ; >> is bit shift right ; | is bitwise OR               */
  /*  Syntax:   variable << number_of_bits                                         */
  /*            variable >> number_of_bits                                         */
  int TemperatureSum = ((MSB << 8) | LSB) >> 4; 

  float celsius = TemperatureSum*0.0625;  //One LSB equals 0.0625 C
  return celsius;
  
}

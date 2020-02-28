# Ethanol Sensor

This is Arduino and related code for an ethanol sensor being designed by Peter Weiss and team.

Team members include: 
- James Zhou (electrical design)
- Ryan Luk (coding)
- Sharukh "Sharky" Lal (physical design)

# Objective

Design an ethanol sensor product that can be used for research or in wineries to regulate ethanol concentrations.

# Hardware

[Arduino Mega2560](https://www.adafruit.com/product/191)

[Adafruit BME680](https://www.adafruit.com/product/3660) - Temperature, Humidity, Pressure, and Gas Sensor
> Measures temperature, relative humidity, atmospheric pressure, and gas (VOC) resistance. Runs on 3.3V or 5V.

[Adafruit GUVA-S12SD](https://www.adafruit.com/product/1918) - UV Sensor
> Measures UV light (240-370nm) via analog input. Output is a voltage, which can be converted to UV Index by dividing by 0.1V. Runs on 3.3V or 5V.

[Adafruit PCF8523](https://www.adafruit.com/product/3295) - Real time clock (RTC)
> Real time clock for timing and date purposes. Runs on 3.3V or 5V.

[Unknown Brand](https://www.dx.com/p/sd-tf-card-adapter-module-for-arduino-3-3v-5v-compatible-multi-functional-reading-writing-module-2044018.html#.XlROd2hKjb0) - SD Card Reader
> Arduino writes data to SD card. **Note:** The documentation for the Adafruit version (which we assume is essentially identical) has the MISO/MOSI pins reversed. Runs on 5V, not sure about 3.3V.

[Unknown Brand](https://www.pololu.com/product/1219/specs) - 20x4 LCD
> Used for displaying time stamp and sensor data (usable pinout given by: 1. ground | 2. power | 3. ground | 4. pin 12 | 5. ground | 6. pin 11 | 7 | 8 | 9 | 10 | 11. pin 5 | 12. pin 4 | 13. pin 3 | 14. pin 2 | 15. power | 16. ground | 17 | 18). Runs on 5V. 

**Wiring Color Schema:** Red = Power, Black = Ground, Green = SDA, Yellow = SCL

# Code

sensor.ino
> Main file for LCD, RTC, sensors, and SD card reader. Currently displays time, temperature, humidity, pressure, gas resistance, and UV as a voltage on the LCD and writes data to the SD card.

data.pde
> Side file for data collection on computer. Since Arduino does not have a native Serial-to-file data system, this processing code is allowed to listen to the Serial output and writes it to a text file. Not going to be used once the SD card is implemented. This also requires a high baud rate for some reason (otherwise the readings get really messed up).
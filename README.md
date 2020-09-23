# Ethanol Sensor

This is Arduino and related code for an ethanol sensor being designed by Peter Weiss and team.

# Objective

Design an ethanol sensor product that can be used for research or in wineries to regulate ethanol concentrations.

# Quick-Start

## Code
- Run `git clone $CLONE_URL`
- Open `sensor.ino` in Arduino IDE, make changes
- Upload to Arduino
- Commit changes, push

## Wiring
- Power: 5V (can use rail on breadboard)
- Ground: Ground (can use rail on breadboard)
- SCK/SCK: Marked on Arduino
- SDA/SLI: Marked on Arduino
- Analog: A1 on Arduino (can be changed in `sensor.ino`)
- MISO: MISO from SD card reader goes to 50 on Arduino
- MOSI: MOSI from SD card reader goes to 51 on Arduino
- SCK: SCK from SD card reader goes to 52 on Arduino
- CS: CS from SD card reader goes to 53 on Arduino (chip select)

# Hardware

[Arduino Mega2560](https://www.adafruit.com/product/191)

[Adafruit BME680](https://www.adafruit.com/product/3660) - Temperature, Humidity, Pressure, and Gas Sensor
> Measures temperature, relative humidity, atmospheric pressure, and gas (VOC) resistance. Runs on 3.3V or 5V.

> **Required pins:** power, ground, SCK/SCL, SDI/SDA

[Adafruit GUVA-S12SD](https://www.adafruit.com/product/1918) - UV Sensor
> Measures UV light (240-370nm) via analog input. Output is a voltage, which can be converted to UV Index by dividing by 0.1V. Runs on 3.3V or 5V.

> **Required pins:** power, ground, analog

[Adafruit PCF8523](https://www.adafruit.com/product/3295) - Real time clock (RTC)
> Real time clock for timing and date purposes. Runs on 3.3V or 5V.

> **Required pins:** power, ground, SCL/SCK, SDA/SDI

[Unknown Brand](https://www.dx.com/p/sd-tf-card-adapter-module-for-arduino-3-3v-5v-compatible-multi-functional-reading-writing-module-2044018.html#.XlROd2hKjb0) - SD Card Reader
> Arduino writes data to SD card. **Note:** The documentation for the Adafruit version (which we assume is essentially identical) has the MISO/MOSI pins reversed. Runs on 5V, not sure about 3.3V.

> **Required pins:** power, ground, MISO (50), MOSI (51), SCK (52), CS (53)

[Unknown Brand](https://www.pololu.com/product/1219/specs) - 20x4 LCD
> Used for displaying time stamp and sensor data (usable pinout given by: 1. ground | 2. power | 3. ground | 4. pin 12 | 5. ground | 6. pin 11 | 7 | 8 | 9 | 10 | 11. pin 5 | 12. pin 4 | 13. pin 3 | 14. pin 2 | 15. power | 16. ground | 17 | 18). Runs on 5V. (For example: `1. ground` means pin 1 on the LCD corresponds to a ground pin - any empty pins like 7, 8, 9, 10, 17, 18 are not used) [Some more documentation](https://www.instructables.com/id/Interfacing-20x4-LCD-with-Arduino/)

**Multi-use Wiring For PCB Lines**
- 6 power (BME sensor, UV sensor, RTC, SD card reader, LCD 2x)
- 8 ground (BME sensor, UV sensor, RTC, SD card reader, LCD 4x)
- 2 SCL/SCK (BME sensor, RTC)
- 2 SDA/SDI (BME sensor, RTC)

> The SD card reader uses its own set of digital MISO, MOSI, SCK, CS pins and thus, is not included in this multi-use section.

> Most components have the option to scale down from 5V to 3.3V. I use 5V and haven't tested all components with 3.3V.

# Code

sensor.ino
> Main file for LCD, RTC, sensors, and SD card reader. Currently displays time, temperature, humidity, pressure, gas resistance, and UV as a voltage on the LCD and writes data to the SD card.

# To-do

- [ ] Solidify connections? Rework PCB design?
- [ ] Solder RTC
- [ ] Solder SD card reader
- [ ] Find mounting screw or bolt that will fit UV sensor
- [ ] Solder and mount UV sensor
- [ ] Plug up holes near BME sensor location
- [ ] Solder and mount BME sensor
- [ ] Solder and mount LCD
# Ethanol Sensor

This is Arduino (and related) code for an ethanol sensor being designed by Peter Weiss and team.

Team members include: James Zhou, Ryan Luk, Sharukh "Sharky" Lal

# Objective

Design an ethanol sensor product that can be used for research or in wineries to regulate ethanol concentrations.

# Components

[Adafruit BME680](https://www.adafruit.com/product/3660) - Temperature, Humidity, Pressure, and Gas Sensor
> Measures temperature, relative humidity, atmospheric pressure, and gas (VOC) resistance.

[Adafruit GUVA-S12SD](https://www.adafruit.com/product/1918) - UV Sensor
> Measures UV light (240-370nm) via analog input. Output is a voltage, which can be converted to UV Index by dividing by 0.1V.

[Adafruit PCF8523](https://www.adafruit.com/product/3295) - Real time clock (RTC)
> Real time clock for timing and date purposes.

# Code

sensor.ino
> Main file for LCD, RTC, and sensors. Currently displays time, temperature, humidity, pressure, gas resistance, and UV as a voltage. Need to finish implementing data system (writing to an SD card).

data.pde
> Side file for data collection on computer. Since Arduino does not have a native Serial-to-file data system, this processing code is allowed to listen to the Serial output and writes it to a text file. Not really going to be used once the SD card is implemented.
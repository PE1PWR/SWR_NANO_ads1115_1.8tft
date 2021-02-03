# SWR_NANO_asd1115_1.8tft
 The software is free to use. It is a SWR meter built with an NANO, ASD1115 and a tft 1.8 ST7735. 
 Current version has a relay protection.

The script was written for a TFT 1.8 128 X 160 screen. 

100 watts is the maximum power for this SWR version. A higher power is possible if you adjust the calculation and set the scale X100. 
Also make sure that the input voltage at the ADS1115 does not exceed 5 volts. In that situation, use 2 resistors to divide the voltage.


They ADS1115 is quite linear over a wide range. 
It is very stable.

The formula used for the SWR calculation VSWR = 1+ (Pref / Pfwd) / 1− (Pref / Pfwd) 
In the programming you can adjust the scale yourself and calibrate it if necessary.

Note the design has been tested with USB 5 volts. In practice this will be around 4.5V. 
If you want to use a battery of 3.7 volts, put in a converter to 5 volts. 
If the values expire after using a 5v module, you can adjust them yourself in the code. 
Will perform a test itself to check progress. If this is the case, 
I will enter 2 codes one for USB 5v and one for a battery with 5 volt module. 

You can use the free contact of your relay to protect your amplifier in many ways.

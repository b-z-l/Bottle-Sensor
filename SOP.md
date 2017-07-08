# Bottle Sensor Operational Overview

## Bill of Materials

Item	                                           | Cost(USD) | Source
-------------------------------------------------|-----------|-------------------------------------------------------------------------
Shinyei PPD42NJ Dust Sensor                      |      $10  | [Link](https://www.aliexpress.com/item/SHINYEI-dust-sensor-PPD42NS-PPD4NS-PPD42NJ-dust-sensor-with-cable/32305336628.html) or [Link](http://www.ebay.com/itm/ORIGINAL-Brand-New-SHINYEI-Dust-Sensor-PPD42NJ-PPD42NS-with-Cable-/271927031774)
DHT22 Temperature Humidity Sensor                |       $3  | [Link](https://www.aliexpress.com/item/50PCS-LOT-DHT22-AM2302-Digital-Temperature-and-Humidity-Sensor-DHT22-Free-shiping/1699337492.html)
Arduino Pro Micro, ATMega32U4-5V 16Mhz 	         |       $4  | [Link](http://www.ebay.com/itm/332166215715)
Mini Datalogger with microSD card reader and RTC |       $4  | [Link](http://www.ebay.com/itm/112160970687)
Datalogger/Screw Terminal Adapter                |       $6  | 
MicroSD Card                                     |       $5  | [Link](http://www.ebay.com/itm/New-Sandisk-4GB-Class-4-MicroSD-MicroSDHC-SD-SDHC-Flash-Memory-Card-With-Adapter-/190889743342)
Plastic Chassis                                  |       $6  | 
USB Charger	                                     |       $8  | [Link](https://www.digikey.com/product-detail/en/qualtek/QFAW-05-05/Q971-ND/6412289) or [Link](https://www.sparkfun.com/products/11456)
#4-40 3/8" Self-Tapping Screws                   |       $1  | [Link](http://www.homedepot.com/p/Everbilt-4-x-3-8-in-Zinc-Plated-Steel-Phillips-Pan-Head-Sheet-Metal-Screw-16-per-Pack-812661/204275188)
Battery		                                       |      $30  | [Link](http://www.ebay.com/itm/Anker-PowerCore-10000-Portable-Charger-One-of-the-Smallest-and-Lightest-10000mA/331901490667)
**Total**                                        |    **$82**|
**Total w/o battery or USB charger/cable**       |    **$39**|



**Note:** The Shinyei PPD42 is sensitive to small fluctuations in voltage, so using quality power supply components is recommended. Because the quality of USB chargers vary widely it is recommended to use a USB battery or charger from a major manufacturer.  [See here for more information](http://www.righto.com/2012/10/a-dozen-usb-chargers-in-lab-apple-is.html).

## Software

The Arduino sketch responsible for taking readings from sensors and logging them to the SD card can be found here:  
https://github.com/b-z-l/Bottle-Sensor/blob/master/ShinyeiPPD42_Logger/ShinyeiPPD42_Logger.ino

## Assembly

1. Begin by snapping the Shinyei PPD42 into place in the rear of the insert. Make sure the sensor is held by the retaining clips and sits flush against the plastic holder.

![](https://raw.githubusercontent.com/b-z-l/Bottle-Sensor/master/resources/SOP%20images/shinyei_insert.jpg)
![Make sure it snaps in securely!](https://github.com/b-z-l/Bottle-Sensor/blob/master/resources/SOP%20images/460f16bbf04a518b9f902d04d744144d.gif)

2. Secure the Shinyei in place with a screw. Only make this snug, don't overtighten.

![Securing Shinyei PPD42 with a #4 screw](https://github.com/b-z-l/Bottle-Sensor/blob/master/resources/SOP%20images/IMG_6278.JPG)

3. If required, mate the Pro Micro and the adapter shield together so they snap into place. Orient the USB port on the Pro Micro with the "USB" label on the adapter board.

![](https://github.com/b-z-l/Bottle-Sensor/blob/master/resources/SOP%20images/IMG_6213.JPG?raw=true)

4. Screw the adapter board onto the front of the plastic insert so that the Pro Micro sits inside the unit.

![](https://github.com/b-z-l/Bottle-Sensor/blob/master/resources/SOP%20images/IMG_6240.JPG)

### Wiring Sensors
![Sensor wiring diagram](https://github.com/b-z-l/Bottle-Sensor/blob/master/resources/SOP%20images/sensor_wiring.jpg)

5. Wire the sensors to the Arduino using the screw terminal. The Shinyei and DHT22 must share 5V and GND connections from the screw terminal. 

Start by twisting the GND wires (black, brown, or gray) from the Shinyei and DHT22 together and secure them into the GND terminal. 

![Twisting together wires and screwing into terminals](https://github.com/b-z-l/Bottle-Sensor/blob/master/resources/SOP%20images/IMG_6273.JPG)

Next, do the same with the 5V wires (red). 

**NOTE:** Do NOT wire the two yellow wires together!

The yellow wire from the Shinyei goes to terminal 5. The middle wire from the DHT22 (yellow or purple) goes to terminal 6.

![Completed sensor wiring](https://github.com/b-z-l/Bottle-Sensor/blob/master/resources/SOP%20images/IMG_6275.JPG?raw=true)

### Wiring the Datalogging Shield

![Datalogger Wiring diagram](https://github.com/b-z-l/Bottle-Sensor/blob/master/resources/SOP%20images/datashield_wiring.jpg)

![Wiring the logging shield to the adapter board](https://github.com/b-z-l/Bottle-Sensor/blob/master/resources/SOP%20images/IMG_6265.JPG)

![Wiring power and GND](https://github.com/b-z-l/Bottle-Sensor/blob/master/resources/SOP%20images/IMG_6267.JPG)

![Wiring pins 10, 11, 12, 13, SDA, and SCL](https://github.com/b-z-l/Bottle-Sensor/blob/master/resources/SOP%20images/IMG_6268.JPG)

![Completed wiring](https://github.com/b-z-l/Bottle-Sensor/blob/master/resources/SOP%20images/IMG_6276.JPG)

## Operation

### Blinking lights?
No? Check wiring first.

### Pulling Data
Naming scheme


![Assembled sensor](https://github.com/b-z-l/Bottle-Sensor/blob/master/resources/SOP%20images/IMG_6286.JPG)

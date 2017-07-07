# Bottle Sensor Operational Overview

## Bill of Materials

## Assembly

1. Begin by snapping the Shinyei PPD42 into place in the rear of the insert. Make sure the sensor is held by the retaining clips and sits flush against the plastic holder.

![](https://raw.githubusercontent.com/b-z-l/Bottle-Sensor/master/resources/SOP%20images/shinyei_insert.jpg)

2. Secure the Shinyei in place with a screw. Only make this snug, don't overtighten.

![]()

3. Mate the Pro Micro and the adapter shield together so they snap into place. Orient the USB port on the Pro Micro with the "USB" label on the adapter board.

![]()

4. Screw the adapter board onto the front of the plastic insert so that the Pro Micro sits inside the unit.

![]()

### Wiring

5. Wire the sensors to the Arduino using the screw terminal. The Shinyei and DHT22 must share 5V and GND connections from the screw terminal. Start by twisting the GND wires (black, brown, or gray) from the Shinyei and DHT22 together and secure them into the GND terminal. Next, do the same with the 5V wires (red). 

**NOTE:** Do NOT wire the two yellow wires together!

The yellow wire from the Shinyei goes to terminal 5. The middle wire from the DHT22 (yellow or purple) goes to pin 

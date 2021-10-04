README.md

# Robosapien Redeaux
<img src="photos/Robosapien_2588.jpg" align="right" width="300px">
I found this Robosapien robot in a collection of old toys my kids had.  
We had some fun with this guy and I got to thinking if I could spruce him
up a bit.  With modern embedded machines and Raspery Pis with WiFi, couldn't we 
drive him through a web portal.  Maybe give it a bit of autonomy?

## Starting out

Baby steps first. I could try to control the movement directly but looking
through the old [remote control codes](src/RoboSapien Codes.md) and a fairly well matched controller, it would 
seem that a high level conroller is all that is needed.  We shall see.  I'll start
using an Arduino which is electrically easy to control and interface.  Sorry, about my pal's image.
I left is pants off so I could monitor a repair I had to effect on his erector spinae springs.
Spinal muscular surgery isn't my thing, but they seem to be holding up.  We'll see if I can get him
back into break dancing shape later.

## Async Serial Control

With an oscilloscope and some finagling I managed to send coherent control signals to the 
IR signal line to command the available routines in the master control.  This seems to be the
most flexible way to manage the robot.  I found I needed a 100$\Omega$ resistor to feed in the signal
at the connector point or the 5V high signal partially powered the eyes.

## I2C Control

ATTiny85 are my new go-to device. Since I, ultimately, want to control the Robotsapien with 
a RaspPi I need an interface that can handle 3.3V signals as well as 5V. Using the ATTiny85 
as an I2C Slave is probably the most flexible way to do this. I have a seperate project for
these experiments but it's pretty easy to develop the device.

## Success
By moving the RoboSap Commands to the loop (never was going to work inside the ISRs) I can send commands
using I2C 2 byte commands. I also have access to a bicolor LED for some additional signalling. The major hiccup
was getting the timing off the ATTiny85 to work right. Surprise! microsecond delay is a little off.  Even the 
UNO test platform was about 8% off. The ATTiny was off by almost 35% which brought it out of range for the 
controller in the RoboSap to recognize.  Adjusting the base timing frequency used in the signalling routine
solved the problem.  I plan to start another project to build an I2C controller for the WS2812s.  Oooh googly eyes?

By adding peripherals using I2C I can put all kinds of things on my little friend.
# CUBE16x
Cube 16x is a Hardware Project to control a LED-Cube with 16-LEDs on each side. All of the 4096 LED`s can be controlled individually via an control board or over the network via TCP.
This Repository contains the hardware-near software projects to control the Cube as well as all the hardware construction related stuff.

## About
Cube16x a passion Project, that started some jears back in my study days and has been stored for a long time on a shelf to wait for its completion.

## Repository
This is the Breakdown of this Repository and all its Projects in it.

* Software-Projects
  * **driver-board**
    * Software for the Driver-Board that acts as a screen buffer that is responsible for the actual control of all the shift-latch-registers and plane-drivers.
    * AVR-Studio/Microship-Studio AVR Project
  * **psu-board**
    * Software for the small PSU distribution board that controlls the stand-by power and the power distribution.
    * AVR-Studio/Microship-Studio AVR Project
  * **cube-updater**
    * Programm that can run Animation-Files, code-based animations or an stream from the network. It controls the driver-board and sends it all the neccessery data.
    * 
* Hardware-Projects
  * 

## Work in Progress
This Project is far from finished. Excpecially the Software is nearly nothing and has a long way to go. Even the acutal Control-Board choices are not final. BeagleBone-Black, RaspberryPi, Teensy, ... nothig is tied currently, so it is likely that the Control-Plattform is gonna change.
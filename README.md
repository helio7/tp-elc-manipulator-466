# tp-elc-manipulator-466
A project to control the Degem System's module via Bluetooth using Arduino.

"TP-ELC Manipulator" is the name of a didactic module designed by Degem Systems about robotics.
The machine needs a computer with an obsolete serial port and the proper software to work. If you don't have those things, the device won't work.
This project is another way to operate this equipment, doing a few alterations in its circuitry before. All you will need is an Arduino MEGA, one cheap Bluetooth module and patience.

The project consists in:
- An Arduino Mega (loaded with the sketch here provided) and an Arduino Bluetooth module GW-040 (also called HC-06) both inside the manipulator.
- An application installed in an Android smartphone connected via Bluetooth to the HC-06.

The Bluetooth part of the projects is optional. You could control the module simply using some of the digital inputs of the Arduino, with cables as switches in a protoboard for example. Even you could use an Arduino UNO, if you find the way of course, because the project is tought to work with Bluetooth.

Instructions for use (once installed the Arduino inside the device):
- Turn on the manipulator.
- Link your smartphone with the Bluetooth module inside the manipulator (just the first time).
  Bluetooth device name: TP-ELC Manipulator (this MUST be the HC-06 name, as you'll see forward)      
  pass: whatever pass you chose or the default pass
- Open the app.
- Press connect.
- Command the machine using the buttons.

Programming the Arduino and the Bluetooth Module:
For the Arduino, you only need to load the sketch "tp-elc-manipulator-controller.ino". But the HC-06 will request you a little more work, because the app is designed to search a Bluetooth module named exactly "TP-ELC Manipulator". The HC-06 modules are named "linvor" or "HC-O6" as default, so you have to change this via AT commands.
This page show how to change the pass and name in a HC-06 module. It's in Spanish, sorry:
https://naylampmechatronics.com/blog/15_Configuraci%C3%B3n--del-m%C3%B3dulo-bluetooth-HC-06-usa.html

Installation instructions:
- Disconnect the manipulator from the energy supply.
- Disarm and open the manipulator.
- Unplug all the connectors of the main board (the big, square one in the center) to work easier.
- Locate the ports labeled as J1, J6 and J9. Connect them to the Arduino following the indications in the pages A, B and C.
- Locate the connectors J6 and J9. Connect them as indicated in the pages.
- Connect the Bluetooth Module to the Arduino.
- Connect all the remaining connectores to their respectives ports. Some connectors (J6 and J9) will remain "in the air", you can connect them to their ports using protoboard cables.
- Close the manipulator if you want, connect the energy supply and proceed to the instructions for use.

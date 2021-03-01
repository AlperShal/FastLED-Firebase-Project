# FastLED-Firebase-Project
An Arduino strip led project made using ESP8266 and Firebase with FastLED library.

**Requirements**

 - Equipments: NodeMCU ESP8266, WS2812 Strip Led
 - Libraries: [FastLED](https://github.com/FastLED/FastLED), [ArduinoJson](https://github.com/bblanchon/ArduinoJson), [FirebaseArduino](https://github.com/FirebaseExtended/firebase-arduino)
 - Board Manager: NodeMCU 1.0, Core 2.4.2
 - Firebase Account
 - Public WiFi for ESP8266

## Usage
 - First, log-in into your Firebase account and create a project. (Project name does not matter.)
 - Second, create a Realtime Database and choose Test Mode while creating it.
 - Third, create "Firebase Items" in Realtime Database

 ![Third.1](https://i.imgur.com/m1pRiid.png) |..|..|..|![Third.2](https://i.imgur.com/c78br9I.png)
 - Fourth, take your "FIREBASE_AUTH" from Settings > Project Settings > Service Accounts > Database Secrets and paste it into the "Firebase" section in the code.

 ![Fourth.1](https://i.imgur.com/KZYZF9f.png)
 
 - Fifth, copy your "PROJECT_HOST" from Realtime Database window and paste it into the "Firebase" section in the code. (Without "https", ":" and "/"es.)

 ![REALTIMEDB](https://i.imgur.com/3CBe7AM.png)
 ![Firebase](https://i.imgur.com/fF7Qd8C.png)

 - Sixth, type your WiFi credentials into the "Wi-Fi" section in the code.

 ![WiFi](https://i.imgur.com/LYTgoFS.png)
 
 - Now, we should prepare libraries and choose right board manager. (I am not going to write how to prepare ESP8266 and how to install ESP8266's board manager etc.)
 - While you are installing "esp8266" board manager please download version 2.4.2! Newer versions are not working.
 - Seventh, download, install and run Ardudino IDE, then go Tools > Manage Libraries > Search "FastLED" by Daniel Garcia (Latest version or v3.4.0) and "ArduinoJson" by Benoit Blanchon (**v5.13.5, not higher!**) and install them.
 - Eighth, download [FirebaseArduino](https://github.com/FirebaseExtended/firebase-arduino/archive/master.zip) and install it. (Sketch > Include Library > Add .ZIP Library > firebase-arduino-master.zip)
 - Nineth, save your file (Ctrl + S) and upload the code to your ESP8266. (Do not forget chosing ESP8266's communication port at Tools > Port)
 - Tenth, make wiring. Connect 5V electricity to strip led. (Should be 5 cables in your strip led. Color data, positive currency, negative currency, additional positive currency for ESP and additional negative currency for ESP.)
 - Eleventh, connect additional negative to G (ground), connect additional positive to VIN and connect color data to D4 pin.
 - Twelveth, press RST button and wait code to start. When code starts first led of your led strip will light in tree different color. (Colors should light Red, Green and Blue color in order.)
 If it is true: Congragulations, you can change your Led Mode from Firebase and use it however you want.
LedModes; 
 - Off - Turns lef off
 - Custom - Custom colors
 - White - White Color
 - Blue - Blue Color
 - Purple - Purple Color
 - Study - It is my personal mode. First 20 leds in the strip lits up white colored.
 - Rainbow - Floating colors.
 If it is not true: Change <#define COLOR_ORDER GRB> to what it should be. (Ex: RGB, RBG, GBR, BRG, BGR)
The End

---
If you have problems, just open an issue on GitHub. Bye.

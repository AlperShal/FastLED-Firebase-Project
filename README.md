# FastLED-Firebase-Project
An Arduino strip led project made using ESP8266 and Firebase with FastLED library.

**Requirements**

 - Equipments: NodeMCU ESP8266, FastLED Supported Strip Led (I use WS2812)
 - Libraries: [FastLED](https://github.com/FastLED/FastLED), [Firebase-ESP8266](https://github.com/mobizt/Firebase-ESP8266)
 - Board Manager: NodeMCU 1.0, Latest (Tested 3.0.0)
 - Firebase Account
 - Wifi

## Setup
 - First, log-in into your Firebase account and create a project. (Project name does not matter.)
 - Second, create a Realtime Database and choose Test Mode while creating it.
 - Third, create "Firebase Items" in Realtime Database

 ![Third.2](https://i.imgur.com/c78br9I.png)
 - Fourth, go into Build > Authentication > Sign-in Method and enable "Email/Password". Then in the same page go to Users and add a user. (As mail write your own mail, as password it doesn't have to be your mail password. It is for Firebase authentication.)

 ![Fourth.1](https://i.imgur.com/OWuFpXh.png)
 ![Fourth.1](https://i.imgur.com/zDsySaG.png)
 
 - Fifth, copy your "DATABASE_URL" from Realtime Database window and copy your "API_KEY" from project settings and paste them into the "Firebase" section in the code. (Don't copy https://)

 ![REALTIMEDB](https://i.imgur.com/3CBe7AM.png)
 ![Firebase](https://i.imgur.com/SrrGLG9.png)

 - Sixth, type your WiFi credentials into the "Wi-Fi" section in the code.

 ![WiFi](https://i.imgur.com/LYTgoFS.png)
 
 - Now, we should prepare libraries and choose right board manager. (I am not going to write how to prepare ESP8266 and how to install ESP8266's board manager etc.)
 - Seventh, go Tools > Manage Libraries > Search "FastLED" by Daniel Garcia and "Firebase-ESP8266" by mobizt and install them.
 - Eighth, save your file (Ctrl + S) and upload the code to your ESP8266. (Do not forget choosing ESP8266's communication port at Tools > Port)
 - Nineth, make wiring. Connect 5V electricity and ground to strip led. (Should be 5 cables in your strip led. Color data, positive currency, negative currency, additional positive currency for ESP and additional negative currency for ESP.)
 - Tenth, connect additional negative to G (ground) on yourboard, connect additional positive to VIN and connect color data to D4 pin.
 - Eleventh, press RST button and wait for code to start. When code starts running, first led of your led strip will light in three different color. Led should light Red, Green and Blue color in order.
 If it is true: Congratulations, you can change your Led Mode in Firebase and use it however you want.
 If it is not true: Change <#define COLOR_ORDER GRB> to what it should be. (Ex: RGB, RBG, GBR, BRG, BGR)
LedModes; 
 - Off - Turns leds off
 - Custom - Custom colors
 - White - White Color
 - Blue - Blue Color
 - Purple - Purple Color
 - Study - It is my personal mode. First 20 leds in the strip lits up white colored.
 - Rainbow - Floating colors.

The End

---
If you have problems, just open an issue on GitHub. Bye.

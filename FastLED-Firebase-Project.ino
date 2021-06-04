//Requirements;
//NodeMCU ESP8266, Driver, Listed Libraries and Strip Led
//Notes
//Don't forget choosing Tools > Board: > ESP8266 Modules > NodeMCU 1.0
//Don't forget changing details in "Configurations".

//Library List
#include <FastLED.h>
#include <FirebaseESP8266.h>
#include <string> //Not a downloadable library
#include <ESP8266WiFi.h> //Inclueded with board manager
#include "addons/TokenHelper.h" //Included with Firebase library
#include "addons/RTDBHelper.h" //Included with Firebase library
//Configurations
#define LED_PIN     D4
#define NUM_LEDS    30
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
#define UPDATES_PER_SECOND 200


//Wi-Fi
#define WIFI_SSID "Your SSID"
#define WIFI_PASS "Your PASS"


//Firebase
#define API_KEY "Your API Key" //Project Settings > General > Web API Key
#define DATABASE_URL "Your Database URL.firebaseio.com" //Realtime Database > Data (Copy without "https:" and "/"es)
#define USER_EMAIL "Mail you registered" //Build > Authentication > Sign-in Method and enable "Email/Password". Then in the same page go to Users and add a user.
#define USER_PASSWORD "Password you set" //Build > Authentication > Sign-in Method and enable "Email/Password". Then in the same page go to Users and add a user.

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
unsigned long dataMillis = 0;
int count = 0;

//FastLED
CRGB leds[NUM_LEDS];
CRGBPalette16 currentPalette;
TBlendType    currentBlending;
extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;


//Variables
String oldFireStatus;
int oldBRIGHTNESS;
int oldCustomRed;
int oldCustomGreen;
int oldCustomBlue;

String fireStatus;
int BRIGHTNESS;
int customRed;
int customGreen;
int customBlue;


void setup() {
  delay(3600); //Power-up safety
  Serial.begin(9600); //Serial baud

  //FastLED
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  currentPalette = RainbowColors_p;
  currentBlending = LINEARBLEND;


  //Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();


  //Connect to Firebase
  Serial.printf("Firebase Client Version:", FIREBASE_CLIENT_VERSION);
  config.api_key = API_KEY;
  
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.database_url = DATABASE_URL;
  config.token_status_callback = tokenStatusCallback;

  Firebase.begin(&config, &auth);
  Serial.println("Connected to Firebase!");

  //Startup Cleaner
  fireStatus = "0";
  BRIGHTNESS = 0;
  customRed = 0;
  customGreen = 0;
  customBlue = 0;
}


void loop() {
  oldFireStatus = fireStatus;
  oldBRIGHTNESS = BRIGHTNESS;
  oldCustomRed = customRed;
  oldCustomGreen = customGreen;
  oldCustomBlue = customBlue;

  //Firebase Items
  Firebase.getString(fbdo, "/LED_STATUS", fireStatus);
  Firebase.getInt(fbdo, "/BRIGHTNESS", BRIGHTNESS);
  Firebase.getInt(fbdo, "/customRed", customRed);
  Firebase.getInt(fbdo, "/customGreen", customGreen);
  Firebase.getInt(fbdo, "/customBlue", customBlue);

  if(fireStatus != oldFireStatus || fireStatus == "custom"){
    //Modes
    if (fireStatus == "off") {
      Serial.println("Led Turned Off");
      for (int i = 0; i < NUM_LEDS; i = i + 1) {
      leds[i] = CRGB::Black;
      }
      FastLED.show();
    }

    else if (fireStatus == "custom") {
      Serial.println("Mode: Custom");
      FastLED.setBrightness(BRIGHTNESS);
      for (int i = 0; i < NUM_LEDS; i = i + 1) {
        leds[i] = CRGB(customRed, customGreen, customBlue);
      }
      FastLED.show();
    }

    else if (fireStatus == "white") {
      Serial.println("Mode: White");
      FastLED.setBrightness(BRIGHTNESS);
      for (int i = 0; i < NUM_LEDS; i = i + 1) {
        leds[i] = CRGB(255, 255, 255);
      }
      FastLED.show();
    }

    else if (fireStatus == "blue") {
      Serial.println("Mode: Blue");
      FastLED.setBrightness(BRIGHTNESS);
      for (int j = 0; j < NUM_LEDS; j++) {
        leds[j] = CRGB(0, 255, 255);
      }
      FastLED.show();
    }

    else if (fireStatus == "purple") {
      Serial.println("Mode: Purple");
      FastLED.setBrightness(BRIGHTNESS);
      for (int i = 0; i < NUM_LEDS; i = i + 1) {
      leds[i] = CRGB(173, 31, 225);
      }
      FastLED.show();
    }

    else if (fireStatus == "green") {
      Serial.println("Mode: Green");
      FastLED.setBrightness(BRIGHTNESS);
      for (int i = 0; i < NUM_LEDS; i = i + 1) {
        leds[i] = CRGB(0, 255, 0);
      }
      FastLED.show();
    }
  
    else if (fireStatus == "study") {
      Serial.println("Mode: Study");
      FastLED.setBrightness(BRIGHTNESS);
      for (int i = 0; i < 20; i = i + 1) {
        leds[i] = CRGB::Black;
      }
      for (int i = 0; i < 20; i = i + 1) {
        leds[i] = CRGB(255, 255, 255);
      }
      FastLED.show();
    }

    else if (fireStatus == "rainbow") {
      Serial.println("Mode: Rainbow");
      FastLED.setBrightness(BRIGHTNESS);
      for (int i = 0; i < 1000; i++) {
        ChangePalettePeriodically();
        static uint8_t startIndex = 0;
        startIndex = startIndex + 1;  
        FillLEDsFromPaletteColors( startIndex);
        FastLED.show();
        FastLED.delay(1000 / UPDATES_PER_SECOND);
      }
    }

    else {
      Serial.print(fireStatus);
      Serial.println(" is an invalid command! Please change LED_STATUS!");
    }
  }
  else {
    delay(500);
  }
}


//Palettes (All of them are just for rainbow effect. If you will not use them you can delete them.)
void FillLEDsFromPaletteColors( uint8_t colorIndex) {
  uint8_t brightness = BRIGHTNESS;
  for ( int i = 0; i < NUM_LEDS; ++i) {
    leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
    colorIndex += 3;
  }
}


void ChangePalettePeriodically() {
  uint8_t secondHand = (millis() / 1000) % 60;
  static uint8_t lastSecond = 99;
  if ( lastSecond != secondHand) {
    lastSecond = secondHand;
    if ( secondHand ==  0) {
      currentPalette = RainbowColors_p;
      currentBlending = LINEARBLEND;
    }
  }
}

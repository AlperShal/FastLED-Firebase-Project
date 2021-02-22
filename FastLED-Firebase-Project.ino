//Requirements;
//NodeMCU ESP8266, Core !!2.4.2!!, Driver, Libraries and Strip Led (WS2812)
//ArduinoJson 5.13.5 (Can use lower version down to 5.x but not higher)
//FirebaseArduino https://github.com/FirebaseExtended/firebase-arduino

//Libraries
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <FastLED.h>
#include <string>


//Configurations
#define LED_PIN     4
#define NUM_LEDS    30
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
#define UPDATES_PER_SECOND 200
CRGB leds[NUM_LEDS];


//Wi-Fi
#define WIFI_SSID "Berker - Alper"
#define WIFI_PASS "salmalikanesininmisafirleri159"


//Firebase
#define FIREBASE_HOST "masa-led.firebaseio.com"
#define FIREBASE_AUTH "3qIRUuS4qCw4dVT0j4djZCNyRvsmuLMyVPJauczP"


//FastLED
CRGBPalette16 currentPalette;
TBlendType    currentBlending;
extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;


extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;


//On-time Run
void setup() {
  delay(3000); //Power-up safety


  //FastLED
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  currentPalette = RainbowColors_p;
  currentBlending = LINEARBLEND;
  Serial.begin(9600);


  //Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();


  //Connect to Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Serial.println("Connected to Firebase!");

  //RGB Order Test (If first led does not run in red-green-blue order change "#define COLOR_ORDER")
  leds[0] = CRGB::Red;
  FastLED.show();
  delay(500);
  leds[0] = CRGB::Green;
  FastLED.show();
  delay(500);
  leds[0] = CRGB::Blue;
  FastLED.show();
  delay(500);
}


//Loop Run
void loop() {
#define fireStatus Firebase.getString("LED_STATUS")
#define BRIGHTNESS Firebase.getInt("BRIGHTNESS")
#define SATURATION Firebase.getInt("SATURATION")
#define customRed Firebase.getInt("customRed")
#define customGreen Firebase.getInt("customGreen")
#define customBlue Firebase.getInt("customBlue")


  //Modes
  if (fireStatus == "off") {
    for (int i = 0; i < NUM_LEDS; i = i + 1) {
      leds[i] = CRGB::Black;
    }
    FastLED.show();
    Serial.println("Led Turned Off");
  }

  else if (fireStatus == "custom") {
    FastLED.setBrightness(BRIGHTNESS);
    delay(200);
    for (int i = 0; i < 30; i = i + 1) {
      leds[i].r = customRed;
      leds[i].g = customGreen;
      leds[i].b = customBlue;
    }
    FastLED.show();
    Serial.println("Mode: Custom");
  }

  else if (fireStatus == "white") {
    FastLED.setBrightness(BRIGHTNESS);
    for (int i = 0; i < NUM_LEDS; i = i + 1) {
      leds[i] = CRGB(255, 255, 255);
    }
    FastLED.show();
    Serial.println("Mode: White");
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

  else if (fireStatus == "study") {
    Serial.println("Mode: Study");
    FastLED.setBrightness(BRIGHTNESS);
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
    Serial.println("Invalid command! Please change LED_STATUS!");
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

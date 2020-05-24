//Boards
//Arduino nano 5v (but will run down to 2.8 so Lipo ok to power via 5v rail
//TPL5110 5v (but runs on lipo)
//433mhz Transmitter 3v rail
//RFID Reader 3v rail
//DFPlayer 3.2-5 (let's take the 5v rail)
//Batteries 2 x 18650 in parallel for long life


#include <Adafruit_NeoPixel.h>
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include "MFRC522.h"
#include <RH_ASK.h>
#include <SPI.h>

RH_ASK driver(2000,4,7,5,false);   // change the library default from tx pin 12 to pin 7. RX=4 PTT=5
static const uint8_t PIN_MP3_TX = 2; // Connects to DFPlayer module's RX
static const uint8_t PIN_MP3_RX = 3; // Connects to DFPlayer module's TX
#define DONEPIN 6  //Pin to Power Down TPL5110  pin 6
#define RF_DATA_PIN 7 //433mhz Transmitter
#define PIN     8  //LED WS2812b Data Pin
#define RSTPIN  9  //RFID
#define SDAPIN 10 //RFID
#define MOSIPIN 11 //RFID
#define MISOPIN 12 //RFID
#define SCKPIN 13 //RFID
bool RFIDON = false; // set the rfid to false for oneshot button to work

MFRC522 mfrc522(SDAPIN, RSTPIN);  // Create MFRC522 instance


#define N_LEDS 37  //Number of WS2812 LED's


SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);
DFRobotDFPlayerMini player;

//Pixels
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);
 
void setup() {
  pinMode(DONEPIN, OUTPUT);
  digitalWrite(DONEPIN, LOW);
  softwareSerial.begin(9600);
  driver.init();
  strip.begin();
  strip.show();
  Serial.begin(9600);    // Initialize serial communications with the PC
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();      // Init SPI bus
  Serial.println(F("Init"));
  mfrc522.PCD_Init();   // Init MFRC522
  delay(4);       // Optional delay. Some board do need more time after init to be ready, see Readme
  mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
 // mfrc522.PCD_SetAntennaGain(mfrc522.RxGain_max);
}
 
void loop() {
  strip.clear();
  if (RFIDON == true) {
       if ( ! mfrc522.PICC_IsNewCardPresent()) {
       return;
       }
       if ( ! mfrc522.PICC_ReadCardSerial()) {
       return;
       }
       String tag = "";
       for (byte i = 0; i < mfrc522.uid.size; i++)
       {
       tag.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
       tag.concat(String(mfrc522.uid.uidByte[i], HEX));
       }
       tag.toUpperCase();
       if (tag.substring(1) == "C9 FB 87 59") //change here the UID of the card/cards that you want to give access
       {
          // If UID of tag is matched.
          chase(strip.Color(0, 0, 255));
          if (player.begin(softwareSerial)) {
              // Set volume to maximum (0 to 30).
              player.volume(25);
              // Play the first MP3 file on the SD card
              player.play(1);
          }
       delay(400);
       brighten();
       darken();
       strip.clear();
       delay(1000);
       digitalWrite(DONEPIN, HIGH);
       delay(10);
       digitalWrite(DONEPIN, LOW);
       }
       if (tag.substring(1) == "9E 13 64 31") //change here the UID of the card/cards that you want to give access
       {
        // If UID of tag is matched.
       chase(strip.Color(255,255,255));
          if (player.begin(softwareSerial)) {
              // Set volume to maximum (0 to 30).
              player.volume(25);
              // Play the first MP3 file on the SD card
              player.play(1);
          }
       delay(400);
       brighten();
       darken();
       strip.clear();
       delay(1000);
       digitalWrite(DONEPIN, HIGH);
       delay(10);
       digitalWrite(DONEPIN, LOW);
       }
  }
  if (RFIDON == false) {
  Serial.println(F("Else Statement"));
  int RandNumber = random(2);
  const char *msg = "Doorbell"; //Doorbell transmission
  driver.send((uint8_t *)msg, strlen(msg));
  driver.waitPacketSent();
  switch(RandNumber)
  {
    case 2:  chase(strip.Color(0, 255, 0)); // Green
             break;
    case 0:  chase(strip.Color(0, 0, 255)); // Blue
             break;
    case 1:  chase(strip.Color(255,255,255)); // White
             break;
  }
  Serial.println(F("Mp3 Start"));
  if (player.begin(softwareSerial)) {
    // Set volume to maximum (0 to 30).
    player.volume(25);
    // Play the first MP3 file on the SD card
    player.play(1);
  }
  delay(400);
  brighten();
  darken();
  strip.clear();
  Serial.println("LED OFF");
  delay(1000);
  digitalWrite(DONEPIN, HIGH);
  Serial.println("PIN DONE");
  delay(10);
  digitalWrite(DONEPIN, LOW);
  RFIDON = true;
  } v                            m
}
 
static void chase(uint32_t c) {
  uint16_t m, n=20;
  for (m=0;  m<15 ; m++) {
    for(uint16_t i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i  , c); // Draw new pixel
        strip.setPixelColor(i-4, 0); // Erase pixel a few steps back
        if (i<4) {
          strip.setPixelColor(i+33, 0);
        }
        strip.show();
        delay(n);
    }
  n=n*7/8;  
  }
  for(uint16_t i=31; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, 0); // Erase pixel a few steps back
    strip.show();
    delay(n);
  }
  strip.clear();
}

void brighten() {
  uint16_t i, j;
  for (j = 0; j < 255; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, 0, j, 0);
    }
    strip.show();
    delay(2);
  }
}

void darken() {
  uint16_t i, j, q=0, r=0;
  for (j = 255; j > 0; j=j*13/14) {
    for (i = 0; i < strip.numPixels(); i++) {
      if (j>30){ 
        if (i!= r) {
        strip.setPixelColor(i, 0, j, 0);
        }
      }
      else {
        strip.setPixelColor(i, 0, j, 0);  
      }
    }
    strip.show();
    delay(30);
  // put in the twinkle here
    q=q+1;
    if (q=300) { 
      r = random(46);
      strip.setPixelColor(r, 255,255,255);
      strip.show();
      q=0;
    }
  }

   strip.clear();
   strip.show();
}

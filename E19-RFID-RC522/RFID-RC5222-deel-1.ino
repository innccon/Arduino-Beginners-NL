/*
 * Bas on Tech - RFID lezer
 * Deze les is onderdeel van de lessen op https://arduino-lessen.nl
 *  
 * (c) Copyright 2018 - Bas van Dijk / Bas on Tech
 * Deze code en inhoud van de lessen mag zonder schriftelijke toestemming 
 * niet voor commerciele doeleinden worden gebruikt
 * 
 * YouTube:    https://www.youtube.com/c/BasOnTechNL
 * Facebook:   https://www.facebook.com/BasOnTechChannel
 * Instagram:  https://www.instagram.com/BasOnTech
 * Twitter:    https://twitter.com/BasOnTech
 * 
 * ---------------------------------------------------------------------------
 *  * 
 * LET OP: De beveiliging van deze kaarten is zwak. Niet gebruiken voor beveiliging. De
 * kaartnummers hoeven niet perse uniek te zijn. Sommige Chinese kaarten staan toe dat
 * het nummer kan worden veranderd.
 * 
 * Pin layout:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 */

#include <SPI.h>                      // SPI bibliotheek
#include <MFRC522.h>                  // MFRC522 bibliotheek

const int pinRST =  9;                // Reset pin
const int pinSS =  10;                // Serial data pin

MFRC522 mfrc522(pinSS, pinRST);       // Instantieer MFRC522 op pinSS en pinRST

// Print alle kaart data naar seriele monitor
void dumpCardData() {
  
  // Als geen nieuwe kaart is gevonden EN
  // Als geen kaart data wordt gelezen
  // PICC = Proximity Integrated Circuit Card
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
      // Lees de kaart uit naar de seriele monitor
      mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
  }

}

void setup() {
  Serial.begin(9600);   // Stel de seriële monitor in

  SPI.begin();          // Initialiseer de SPI bus
  mfrc522.PCD_Init();   // Initialiseer de MFRC522 lezer

  // Print MFRC522 Card Reader details naar seriële monitor
  mfrc522.PCD_DumpVersionToSerial();

  Serial.println("Houd kaart voor RFID scanner...");
}

void loop() {
  dumpCardData();
}
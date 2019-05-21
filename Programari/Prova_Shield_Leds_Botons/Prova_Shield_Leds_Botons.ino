#include <Wire.h>
#include "Adafruit_MCP23017.h"
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"


/*
 * Pins de l'expansor MCP23017:
*/
#define LLFE 8
#define LLFD 10
#define LLP 12
#define LDFE 0
#define LDFC 9
#define LDFD 1
#define LDD 2
#define LDE 11
#define LDP 3
#define RGB_R 4
#define RGB_G 13
#define RGB_B 5
#define B2 14
#define B3 15
#define B4 6
#define B5 7

Adafruit_MCP23017 mcp;

// 0X3C+SA0 - 0x3C or 0x3D
#define I2C_ADDRESS 0x3C
// Define proper RST_PIN if required.
#define RST_PIN -1

SSD1306AsciiWire pantalla;

void setup() {  
  // Freqüència de l'I2C a 400kHz
  Wire.setClock(400000L);
  // Iniciem l'expansor MCP23017:
  mcp.begin();
  // Definim tots els leds com a sortides:
  mcp.pinMode(LDFE, OUTPUT);
  mcp.pinMode(LDFC, OUTPUT);
  mcp.pinMode(LDFD, OUTPUT);
  mcp.pinMode(LDE, OUTPUT);
  mcp.pinMode(LDD, OUTPUT);
  mcp.pinMode(LDP, OUTPUT);
  mcp.pinMode(LLFE, OUTPUT);
  mcp.pinMode(LLFD, OUTPUT);
  mcp.pinMode(LLP, OUTPUT);
  mcp.pinMode(RGB_R, OUTPUT);
  mcp.pinMode(RGB_G, OUTPUT);
  mcp.pinMode(RGB_B, OUTPUT);
  // Definim els botons com a entrades:
  mcp.pinMode(B2, INPUT);
  mcp.pinMode(B3, INPUT);
  mcp.pinMode(B4, INPUT);
  mcp.pinMode(B5, INPUT);
  // Apagam tots els leds:
  mcp.digitalWrite(LDFE, LOW);
  mcp.digitalWrite(LDFC, LOW);
  mcp.digitalWrite(LDFD, LOW);
  mcp.digitalWrite(LDE, LOW);
  mcp.digitalWrite(LDP, LOW);
  mcp.digitalWrite(LDD, LOW);
  mcp.digitalWrite(LLFE, LOW);
  mcp.digitalWrite(LLFD, LOW);
  mcp.digitalWrite(LLP, LOW);
  mcp.digitalWrite(RGB_R, LOW);
  mcp.digitalWrite(RGB_G, LOW);
  mcp.digitalWrite(RGB_B, LOW);
  // Iniciem la pantalla:
  pantalla.begin(&Adafruit128x64, I2C_ADDRESS);
  pantalla.setFont(Adafruit5x7);
  pantalla.set1X();
  pantalla.setScrollMode(SCROLL_MODE_AUTO);
  pantalla.clear();
  // Iniciem el port sèrie:
  Serial.begin(115200);
}


void loop() {
  mcp.digitalWrite(LDFE, HIGH);
  Serial.print("LDFE"); Serial.println(", pulsa B2");
  pantalla.print("LDFE"); pantalla.println(", pulsa B2");
  while(mcp.digitalRead(B2)==LOW);
  mcp.digitalWrite(LDFE, LOW);
  mcp.digitalWrite(LDFC, HIGH);
  Serial.print("LDFC"); Serial.println(", pulsa B2");
  pantalla.print("LDFC"); pantalla.println(", pulsa B2");
  while(mcp.digitalRead(B2)==HIGH);
  while(mcp.digitalRead(B2)==LOW);
  mcp.digitalWrite(LDFC, LOW);
  mcp.digitalWrite(LDFD, HIGH);
  Serial.print("LDFD"); Serial.println(", pulsa B2");
  pantalla.print("LDFD"); pantalla.println(", pulsa B2");
  while(mcp.digitalRead(B2)==HIGH);
  while(mcp.digitalRead(B2)==LOW);
  mcp.digitalWrite(LDFD, LOW);
  mcp.digitalWrite(LDD, HIGH);
  Serial.print("LDD"); Serial.println(", pulsa B2");
  pantalla.print("LDD"); pantalla.println(", pulsa B2");
  while(mcp.digitalRead(B2)==HIGH);
  while(mcp.digitalRead(B2)==LOW);
  mcp.digitalWrite(LDD, LOW);
  mcp.digitalWrite(LDP, HIGH);
  Serial.print("LDP"); Serial.println(", pulsa B2");
  pantalla.print("LDP"); pantalla.println(", pulsa B2");
  while(mcp.digitalRead(B2)==HIGH);
  while(mcp.digitalRead(B2)==LOW);
  mcp.digitalWrite(LDP, LOW);
  mcp.digitalWrite(LDE, HIGH);
  Serial.print("LDE"); Serial.println(", pulsa B2");
  pantalla.print("LDE"); pantalla.println(", pulsa B2");
  while(mcp.digitalRead(B2)==HIGH);
  while(mcp.digitalRead(B2)==LOW);
  mcp.digitalWrite(LDE, LOW);
  mcp.digitalWrite(LLFE, HIGH);
  Serial.print("LLFE"); Serial.println(", pulsa B3");
  pantalla.print("LLFE"); pantalla.println(", pulsa B3");
  while(mcp.digitalRead(B2)==HIGH);
  while(mcp.digitalRead(B3)==LOW);
  mcp.digitalWrite(LLFE, LOW);
  mcp.digitalWrite(LLFD, HIGH);
  Serial.print("LLFD"); Serial.println(", pulsa B3");
  pantalla.print("LLFD"); pantalla.println(", pulsa B3");
  while(mcp.digitalRead(B3)==HIGH);
  while(mcp.digitalRead(B3)==LOW);
  mcp.digitalWrite(LLFD, LOW);
  mcp.digitalWrite(LLP, HIGH);
  Serial.print("LLP"); Serial.println(", pulsa B3");
  pantalla.print("LLP"); pantalla.println(", pulsa B3");
  while(mcp.digitalRead(B3)==HIGH);
  while(mcp.digitalRead(B3)==LOW);
  mcp.digitalWrite(LLP, LOW);
  mcp.digitalWrite(RGB_R, HIGH);
  Serial.print("RGB_R"); Serial.println(", pulsa B4");
  pantalla.print("RGB_R"); pantalla.println(", pulsa B4");
  while(mcp.digitalRead(B3)==HIGH);
  while(mcp.digitalRead(B4)==LOW);
  mcp.digitalWrite(RGB_R, LOW);
  mcp.digitalWrite(RGB_G, HIGH);
  Serial.print("RGB_G"); Serial.println(", pulsa B4");
  pantalla.print("RGB_G"); pantalla.println(", pulsa B4");
  while(mcp.digitalRead(B4)==HIGH);
  while(mcp.digitalRead(B4)==LOW);
  mcp.digitalWrite(RGB_G, LOW);
  mcp.digitalWrite(RGB_B, HIGH);
  Serial.print("RGB_B"); Serial.println(", pulsa B5");
  pantalla.print("RGB_B"); pantalla.println(", pulsa B5");
  while(mcp.digitalRead(B4)==HIGH);
  while(mcp.digitalRead(B5)==LOW);
  mcp.digitalWrite(RGB_B, LOW);
  while(mcp.digitalRead(B5)==HIGH);
  pantalla.clear();
}

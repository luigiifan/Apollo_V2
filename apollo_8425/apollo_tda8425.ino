#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <TDA8425.h>

TDA8425 audio;

LiquidCrystal_I2C lcd(0x27, 16, 2);

//ROTARY
#define CLK 2
#define DT 3
#define SW 4

//VAR
int counter = 1;
int aState;
int aLastState;
int vol;
int treb;
int bass;
String select = "T";
unsigned long lastTime;

void setup() {
  audio.begin();
  lcd.begin();
  lcd.backlight();
//  Serial.begin(9600);
  audio.setVolume(70, 70);
  audio.setMuteChannel(false, 0);
  pinMode(CLK, INPUT_PULLUP);
  pinMode(DT, INPUT_PULLUP);
  pinMode(SW, INPUT_PULLUP);
  aLastState = digitalRead(CLK);
//  lcd.setCursor(4,0);
//  lcd.print("TDA 8425");
//  lcd.setCursor(2,1);
//  lcd.print("=====<>=====");
//  delay(2000);
//  lcd.clear();
}

void loop() {
//  if(digitalRead(SW) == 0){
//    if(millis() - lastTime >= 500){
//      counter++;
//      if(counter >= 4) counter = 1;
////      lcd.clear();
////      lcd.setCursor(0,0);
////      lcd.print("INPUT SELECT: 1");
////      Serial.println("SELECT: " + String(counter));
//      lastTime = millis();
//    }
//  }
  aState = digitalRead(CLK);
  if(counter == 1){
    if (aState != aLastState && aState == 1){
      if (digitalRead(DT) != aState) {
        vol -= 2;
        if(vol <= 0) vol = 0;
        audio.setVolume(vol, vol);
//        Serial.println("VOLUME: " + String(vol));
      }
      else {
        vol += 2;
        if(vol >= 100) vol = 100;
        audio.setVolume(vol, vol);
//        Serial.println("VOLUME: " + String(vol));
      }
    }
    lcd.setCursor(0,1);
    lcd.print("VOLUME: " + String(vol) + "%     ");
    aLastState = aState;
  }
  if(counter == 2){
    if (aState != aLastState && aState == 1){
      if (digitalRead(DT) != aState) {
        treb -= 2;
        if(treb <= 0) treb = 0;
        audio.setBassTreble(bass, treb);
//        Serial.println("TREBLE: " + String(treb));
      }
      else {
        treb += 2;
        if(treb >= 100) treb = 100;
        audio.setBassTreble(bass, treb);
//        Serial.println("TREBLE: " + String(treb));
      }
    }
    aLastState = aState;
  }
  if(counter == 3){
    if (aState != aLastState && aState == 1){
      if (digitalRead(DT) != aState) {
        bass -= 2;
        if(bass <= 0) bass = 0;
        audio.setBassTreble(bass, treb);
//        Serial.println("BASS: " + String(bass));
      }
      else {
        bass += 2;
        if(bass >= 100) bass = 100;
        audio.setBassTreble(bass, treb);
//        Serial.println("BASS: " + String(bass));
      }
    }
    aLastState = aState;
  }
}

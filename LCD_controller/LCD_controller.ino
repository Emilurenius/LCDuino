#include <Wire.h>
#include <LiquidCrystal.h>
// KODE FOR SLAVE
const int rs = 2, en = 3, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const char text[63] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ "; // 0 - 9: numbers  10 - 35: lowercase  36 - 61: UPPERCASE
const int rows = 16;
const int collums = 2;

int i2cRcv[3] = {0, 0, 0}; // Array for data from I2C port.
bool newData = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin(0x01);
  Wire.onReceive(dataRcv);
  lcd.begin(16, 2); // Set rows and collums
}

void loop() {
  // put your main code here, to run repeatedly:
  if (newData && i2cRcv[0] < rows && i2cRcv[0] >= 0 && i2cRcv[1] < collums && i2cRcv[1] >= 0) {
    lcd.setCursor(i2cRcv[0], i2cRcv[1]);
    lcd.print(text[i2cRcv[2]]);
    newData = false;
  }
}

void dataRcv(int numBytes) {
  int i = 0;
  while(Wire.available()) {
    i2cRcv[i] = Wire.read();
    i ++;
  }
  newData = true;
}

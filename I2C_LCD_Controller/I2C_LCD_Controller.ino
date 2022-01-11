#include <Wire.h>
const char text[63] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ "; // 0 - 9: numbers  10 - 36: lowercase  37 - 61: UPPERCASE
const int rows = 16;
const int collums = 2;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
  sendChars(0x01, 0, 0, "Hello world", 11);
}

void loop() {
  // put your main code here, to run repeatedly:
//  char millisString[4];
//  dtostrf(millis() / 1000, 4, 0, millisString);
//  Serial.println(millisString);
//  sendChars(0x01, 0, 1, millisString, 4);
  sendChars(0x01, 0, 0, "Hello world", 11);
  delay(500);
  clearRow(0x01, 0);
  sendChars(0x01, 0, 0, "Cemil", 5);
  delay(500);
}

int getIndex(char val) {
  for (int i=0; i<69; i++) {
    if (val == text[i]) {
      return i;
      break;
    }
  }
}

void sendCharID(int address, int row, int collumn, int charID) {
  delayMicroseconds(250);
  Wire.beginTransmission(address);
  Wire.write(row);
  Wire.write(collumn);
  Wire.write(charID);
  Wire.endTransmission();
  //Serial.println(charID);
}

void sendChars(int sAddress, int row, int collumn, char chars[], int charLen) {

  for (int i=0; i<charLen; i++) {
    sendCharID(sAddress, row + i, collumn, getIndex(chars[i]));
    Serial.print(chars[i]);
  }
  Serial.println();
}

void clearRow(int address, int row) {
  for (int i=0; i<rows; i++) {
    sendCharID(address, i, row, 62);
  }
}

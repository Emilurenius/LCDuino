#include <Wire.h>
// KODE FOR MASTER
char text[63] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ "; // 0 - 9: numbers  10 - 35: lowercase  36 - 61: UPPERCASE
int last[16] = {};
int temp;
int sendVal = 0;
int lowerCaseMod = -87;
int upperCaseMod = -29;
int numberCaseMod = -48;
bool endOfLine = false;
bool tooMany = false;

//Benjamin var her
int getIndex(char val) {
  for (int i=0; i<63; i++) {
    if (val == text[i]) {
      return i;
      break;
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  for (int i=0;i<16;i++) {
        last[i] = 62;
      }
}

void loop() {
  // put your main code here, to run repeatedly:
//  Wire.beginTransmission(0x01);
//  Wire.write(0);
//  Wire.write(0);
//  Wire.write(textI);
//  Wire.endTransmission();
//  textI ++;
//
  
  int row = 0;
  while (Serial.available()) {

    if (row > 16) {
      while (Serial.available()) {
        temp = Serial.read();
        if (temp == 10) {
          tooMany = true;
          break;
        }
      }
    }
    
    endOfLine = false;
    if (!tooMany) {
      temp = Serial.read();
    }
    Serial.print("Raw: ");
    Serial.println(temp);

    
    if (temp > 96 && temp < 123) {
      Serial.print("lowercase Ourscii: ");
      Serial.println(temp + lowerCaseMod);
      sendVal = temp + lowerCaseMod;
    }
    else if (temp > 64 && temp < 91) {
      Serial.print("Uppercase Ourscii: ");
      Serial.println(temp + upperCaseMod);
      sendVal = temp + upperCaseMod;
    }
    else if (temp > 47 && temp < 58) {
      Serial.print("Uppercase Ourscii: ");
      Serial.println(temp + numberCaseMod);
      sendVal = temp + numberCaseMod;
    }
    else if (temp == 32) {
      Serial.print("Space: ");
      Serial.println(62);
      sendVal = 62;
    }
    else if (temp == 10) {
      Serial.print("End of line: ");
      Serial.println(temp);
      endOfLine = true;
      sendVal = 62;
    }
    else {
      Serial.println("Sad arduino noises: Incompatible stuff written");
    }
    delay(20);
    Wire.beginTransmission(0x01);
    Wire.write(row);
    Wire.write(0);
    Wire.write(sendVal);
    Wire.endTransmission();
    delay(20);
    Wire.beginTransmission(0x01);
    Wire.write(row);
    Wire.write(1);
    Wire.write(last[row]);
    Wire.endTransmission();
    
    if (endOfLine) {
      for (int i=row;i<16;i++) {
        delay(20);
        Wire.beginTransmission(0x01);
        Wire.write(i);
        Wire.write(0);
        Wire.write(62);
        Wire.endTransmission();
        delay(20);
        Wire.beginTransmission(0x01);
        Wire.write(i);
        Wire.write(1);
        Wire.write(last[i]);
        Wire.endTransmission();        
        
        last[row] = 62;
        
      }
      Serial.println("Benjamin & Mil");
      endOfLine = false;
    }
    last[row] = sendVal;
    row ++;
  }
}

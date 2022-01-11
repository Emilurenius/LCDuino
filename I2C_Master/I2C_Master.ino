#include <Wire.h>

String ascii[128] = { // 10 per line for readability
    "NUL", "SOH", "STX", "ETX", "EOT", "ENQ", "ACK", "BEL", "BS" , "TAB", //  0-9
    "LF" , "VT" , "FF" , "CR" , "SO" , "SI" , "DLE", "DC1", "DC2", "DC3", //  10-19
    "DC4", "NAK", "SYN", "ETB", "CAN", "EM" , "SUB", "ESC", "FS" , "GS" , //  20-29
    "RS" , "US" , " "  , "!"  , "\"" , "#"  , "$"  , "%"  , "&"  , "'"  , //  30-39
    "("  , ")"  , "*"  , "+"  , ","  , "-"  , "."  , "/"  , "0"  , "1"  , //  40-49
    "2"  , "3"  , "4"  , "5"  , "6"  , "7"  , "8"  , "9"  , ":"  , ";"  , //  50-59
    "<"  , "="  , ">"  , "?"  , "@"  , "A"  , "B"  , "C"  , "D"  , "E"  , //  60-69
    "F"  , "G"  , "H"  , "I"  , "J"  , "K"  , "L"  , "M"  , "N"  , "O"  , //  70-79
    "P"  , "Q"  , "R"  , "S"  , "T"  , "U"  , "V"  , "W"  , "X"  , "Y"  , //  80-89
    "Z"  , "["  , "\\" , "]"  , "^"  , "_"  , "`"  , "a"  , "b"  , "c"  , // 90-99
    "d"  , "e"  , "f"  , "g"  , "h"  , "i"  , "j"  , "k"  , "l"  , "m"  , // 100-109
    "n"  , "o"  , "p"  , "q"  , "r"  , "s"  , "t"  , "u"  , "v"  , "w"  , // 110-119
    "x"  , "y"  , "z"  , "{"  , "|"  , "}"  , "~"  , "DEL"                // 120-128
  };

int asciiCode = 0;

byte i2c_rcv;               // data received from I2C bus

int getIndex(String val) {
  for (int i=0; i<128; i++) {
    if (val == ascii[i]) {
      return i;
      break;
    }
  }
}

void transmitI2C(char message[], int chars) {
  for (int i=0; i<chars; i++) {
    Serial.print(message[i]);
    Wire.write(getIndex(String(message[i])));
  }
  Serial.println();
}

void setup(){
  Serial.begin(9600);
  Wire.begin(); // join I2C bus as the master
  
  // initialize global variables
  i2c_rcv = 255;
  
  pinMode(13, OUTPUT);    // set pin 13 as an output
}

void loop(){
  Wire.beginTransmission(0x08);
  //transmitI2C("ABCD", 4);
  Wire.write(asciiCode);
  Wire.endTransmission();
  delay(1000);
  asciiCode ++;
}

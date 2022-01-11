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

int i2c_rcv[20] = {};


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin(0x08);

  Wire.onReceive(dataRcv);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i=0; i<20; i++) {
    if (i2c_rcv[i] == 0) {
      break;
    }
    Serial.print(ascii[i2c_rcv[i]]);
  }
  Serial.println("");
}

void dataRcv(int numBytes) {
  int i = 0;
  while(Wire.available()) {
    i2c_rcv[i] = Wire.read();
    i ++;
  }
}

/*  CDCE913 programmer code for Arduino
  ========================================================
  Intended for programing CDCE913 as 25 MHz clock reference for LNB and 40 MHz for ADALM Pluto
  
  Ver. 0.5

Copyright (c) 2020 Mirosław Sadowski, Jakub Sadowski

Permission is hereby granted, free of charge, to any person obtaining 
a copy of this software and associated documentation files (the "Software"), 
to deal in the Software without restriction, including without limitation 
the rights to use, copy, modify, merge, publish, distribute, sublicense, 
and/or sell copies of the Software, and to permit persons to whom the Software 
is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included 
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR 
IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
  
#include <Wire.h>

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  
  Wire.begin();

  // 4 MHz generator may be used for debug purposes - uncomment the line below
  // setup_4MHZ_clk();
  
  program_CDCE913();
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH); 
  delay(750);
  digitalWrite(LED_BUILTIN, LOW);
  delay(250);
}


void setup_4MHZ_clk(){
  pinMode(11,OUTPUT);
  
  TCCR2A = ((1 << WGM21) | (1 << COM2A0));
  TCCR2B = (1 << CS20); // prescaler = 1
  TIMSK2 = 0;
  OCR2A = 1;
}

void program_CDCE913(){
  /*
   * Based on http://sp9uob.verox.pl/pliki/fiberref.pdf
   * 
   * These example values enable Y1=10, Y2=25 and Y3=40 MHz outputs, when 10 MHz CLK nput is connected.
   */
  
  uint8_t addr = 0x65;
  uint8_t comm1[7] = {
    0x01, 0x06, 0x05, 0x34, 0x01, 0x02, 0x50
  };
  uint8_t comm2[14] = {
    0x14, 0x0c, 0x6D, 0x02, 0x08, 0x05, 0xff,
    0x00, 0x02, 0x83, 0xff, 0x00, 0x02, 0x80
  };
  uint8_t comm_save_eeprom[2] = {0x86, 0x01};

  Wire.beginTransmission(addr);
  Wire.write(comm1,7);
  Wire.endTransmission();

  delay(100);
  
  Wire.beginTransmission(addr);
  Wire.write(comm2,14);
  Wire.endTransmission();

  delay(100);

  Wire.beginTransmission(addr);
  Wire.write(comm_save_eeprom,2);
  Wire.endTransmission();
}

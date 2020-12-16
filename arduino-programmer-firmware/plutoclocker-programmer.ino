
#include <Wire.h>

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  
  Wire.begin();

  //may be used for debug purposes
  //setup_4MHZ_clk();
  
  program_CDCE913();
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(750);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
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
   * These example values enable 10,25 and 100MHz outputs, when **10MHz** input is connected.
   */
  
  uint8_t addr = 0x65;
  uint8_t comm1[7] = {
    0x01, 0x06, 0x05, 0x34, 0x01, 0x02, 0x50
  };
  uint8_t comm2[14] = {
    0x14, 0x0c, 0x6D, 0x02, 0x08, 0x02, 0xff,
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

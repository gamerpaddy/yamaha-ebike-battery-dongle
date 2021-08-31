//calibration
#define SENDDELAY 23600 //delay between datasets. capture must be 164ms  https://i.imgur.com/LXj3fqW.png
#define BITTIME 59.7 // bit duration. adjust for start bit in 0xFF for 417µs length https://i.imgur.com/IWQ1Sz1.png
#define BITDELAY 1.04 // bit length modifier. capture must be (0xFF, first 2 bits for reference) 3337µs https://i.imgur.com/xPBU9pW.png
#define PARITYDELAY 0.968 //parity bit length modifier. capture must be 417µs https://i.imgur.com/W9EwHV5.png
#define ENDBITDELAY 0.9843 // end bit length must be 0.4165ms aswell https://i.imgur.com/it98XEF.png

//to check data, capture on pin PB0 and decode in saleae logic for Serial, 2400 BAUD, 8 bits, 1 stop bit, even parity. LSB, Non inverted, no special mode.



//default data. 100% 19.15°C 38V 400Wh 1024mA 
byte data[] = {0xFF, 0xFF, 0x0E, 0x06,   0x64,   0x19,   0x01, 0x7F,   0x02, 0xF8,   0x2A,   0xF8, 0x01,   0x18, 0x11, 0xF0,   0x04, 0x00,   0x00};

void setup() {
  pinMode(0,OUTPUT); //TX
  analogReference(INTERNAL);
}

byte chksum() {
  int _t = data[0];
  for (char i = 17; i > 0; i--) {
    _t = _t - data[i];
  } return ((_t % 256) + 256);
}

//PORTB &= B11111110; // set pin 0 high
//PORTB |= B00000001; //set pin 0 low

const byte averages = 40;

void sendChar(char c){
  noInterrupts();          
  byte bits = 0;
  PORTB &= B11111110;
  delayMicroseconds(BITTIME);
   for (char i=0; i<8;i++){
     byte bitr = bitRead(c,i);
     if(bitr == 1){bits++;}
     if(bitr > 0){
      PORTB |= B00000001;
     }else{
      PORTB &= B11111110;
     }
     delayMicroseconds(BITTIME/BITDELAY);
   }
   if((bits % 2) == 0 && bits != 1){
    PORTB &= B11111110;
   }else{
    PORTB |= B00000001;
   }
   bits = 0;
   delayMicroseconds(BITTIME/PARITYDELAY);
   PORTB |= B00000001;
   interrupts();
   delayMicroseconds(BITTIME/ENDBITDELAY);
}

long avg = 0;
int sample = 0;
byte ctr = 0;
char batt_percent = 100;
void loop() {
  delayMicroseconds(SENDDELAY);
  sample = analogRead(A1);
  if(sample>=900){sample=900;}
  if(sample<=720){sample=720;}
  //avg = (((avg<<2) - avg + sample) + 2) >> 2;
  avg = avg + sample;
  ctr++;
  if(ctr == averages){
      batt_percent = (char)map((avg/averages),720,900,0,100);
      ctr = 0;
      avg = 0;
  }

  if(batt_percent<=5){batt_percent=5;} 
  if(batt_percent>=100){batt_percent=100;}
  
  data[4] = batt_percent;
  data[18] = chksum();

  for (char i = 0; i <= 18; i++) {
    sendChar(data[i]);
  }
  
}


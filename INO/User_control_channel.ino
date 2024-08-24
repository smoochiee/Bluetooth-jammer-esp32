#include "RF24.h"
/*
rf24 pin ESP32 pin VSPI

3 (CE) 22
4 (CSN) 21
5 (SCK) 18
6 (MOSI) 23
7 (MISO) 19
*/
//BTF ~= 2403-2480M


RF24 radio(22, 21, 16000000);   ///ce-csn////Spi communicaton Speed///
byte hopping_channel[] = { 32, 34, 46, 48, 50, 52, 0, 1, 2, 4, 6, 8, 22, 24, 26, 28, 30, 74, 76, 78, 80, 82, 84, 86 };  //allow user to choose what channel to attack// channel to hop you can Add 1-125 channels
//byte hopping_channel[] = { 2,80,26};  //ble advertise  channel to hop


byte ptr_hop = 0;  // Pointer to the hopping array

void setup(void) {
  Serial.begin(115200);
  RF();
}
void RF() {
  radio.begin();
  radio.startConstCarrier(RF24_PA_MAX, 45);
  radio.setDataRate(RF24_2MBPS);
}


void loop(void) {


  ptr_hop++;     /// perform next channel change
  if (ptr_hop >= sizeof(hopping_channel)) ptr_hop = 0;  // To avoid array indexing overflow
  radio.setChannel(hopping_channel[ptr_hop]);           // Change channel
}

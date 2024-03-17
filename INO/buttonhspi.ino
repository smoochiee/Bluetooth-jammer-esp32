#include "RF24.h"
#include <ezButton.h>
#include "esp_bt.h"
#include "esp_wifi.h"

SPIClass *hp = nullptr;

RF24 radio(16, 15, 16000000);

byte i = 45;

unsigned int flag = 0;

ezButton toggleSwitch(33);


void setup(void) {
  esp_bt_controller_deinit();
  esp_wifi_stop();
  esp_wifi_deinit();
  Serial.begin(115200);
  toggleSwitch.setDebounceTime(50);
  initHP();
}
void initHP() {
  hp = new SPIClass(HSPI);
  hp->begin();
  if (radio.begin(hp)) {
    delay(200);
    Serial.println("Hp Started !!!");
    radio.setAutoAck(false);
    radio.stopListening();
    radio.setRetries(0, 0);
    radio.setPayloadSize(5);   ////SET VALUE ON RF24.CPP
    radio.setAddressWidth(3);  ////SET VALUE ON RF24.CPP
    radio.setPALevel(RF24_PA_MAX, true);
    radio.setDataRate(RF24_2MBPS);
    radio.setCRCLength(RF24_CRC_DISABLED);
    radio.printPrettyDetails();
    radio.startConstCarrier(RF24_PA_MAX, i);
  } else {
    Serial.println("HP couldn't start !!!");
  }
}
void two() {

  ///CHANNEL WITH 2 SPACING HOPPING
  if (flag == 0) {
    i += 2;
  } else {
    i -= 2;
  }

  if ((i > 79) && (flag == 0)) {
    flag = 1;
  } else if ((i < 2) && (flag == 1)) {
    flag = 0;
  }

  radio.setChannel(i);
  //Serial.println(i);
}

void one() {
  ////SWEEP CHANNEL
  for (int i = 0; i < 79; i++) {
    radio.setChannel(i);
  }
}

/*YOU CAN DO RANDOM CHANNEL 

radio.setChannel(random(79));
*/




void loop(void) {

  toggleSwitch.loop();  // MUST call the loop() function first

  /* if (toggleSwitch.isPressed())
    Serial.println("one");
  if (toggleSwitch.isReleased())
    Serial.println("two");*/

  int state = toggleSwitch.getState();


  if (state == HIGH)
    two();

  else {
    one();
  }
}

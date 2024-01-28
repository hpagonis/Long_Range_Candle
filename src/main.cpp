#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>

#define INPUT_NUM 6

int input_pin[INPUT_NUM] = {PB9, PB8, PB7, PB6, PB5, PB4};
// int counter = 1;

void setup() {
  // Serial.begin(115200);
  // while (!Serial);
  for (int i=0; i < INPUT_NUM; i++) {
    pinMode(input_pin[i], INPUT);
  }
  pinMode(PC13, OUTPUT);
  digitalWrite(PC13, LOW);

  LoRa.setPins(PA4, -1, -1);
  LoRa.setSpreadingFactor(12);
  LoRa.setCodingRate4(8);
  LoRa.setSignalBandwidth(7.8E3);
  LoRa.setTxPower(20);
  LoRa.setSyncWord(0xBA);
  if (!LoRa.begin(433E6)) {
    // Serial.println("Starting LoRa failed!");
    while (1) {
      digitalWrite(PC13, LOW);
      delay(500);
      digitalWrite(PC13, HIGH);
      delay(500);
    }
  }
  digitalWrite(PC13, HIGH);
}

void loop() {
  // Serial.print("Sending packet ");
  // Serial.println(counter);

  uint8_t packet = 0;

  for (unsigned int i = 0 ;i < INPUT_NUM; i++) {
    packet |= digitalRead(input_pin[i]) ? 0 : 1 <<  i;
  }
    digitalWrite(PC13, LOW);
    LoRa.beginPacket();
    // LoRa.write('1' + i);
    // LoRa.write(digitalRead(i) ? 'O' : 'I');
    LoRa.write(packet);
    LoRa.endPacket();
    digitalWrite(PC13, HIGH);
    delay(100);

  // counter++;
}
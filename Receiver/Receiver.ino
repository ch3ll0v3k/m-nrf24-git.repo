// Load up the libraries
#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <printf.h>
#include "Receiver.h"

// define the pins
#define CE_PIN 9
#define CSN_PIN 10

// Create a Radio
RF24 radio(CE_PIN, CSN_PIN);

// The tx/rx address
const uint64_t pipe = 0xE8E8F0F0E1LL; // Define the transmit pipe
// const byte pipe[6] = "00001";
const byte address[6] = "00001";

Data_Package data; //Create a variable with the above structure

unsigned long lastReceiveTime = 0;
unsigned long currentTime = 0;

/*
  Check the reading and writing pipe addresses.
  First, the default is 0xE7E7E7E7E7 for pipe 0 (RX_ADDR_P0) and 0xC2C2C2C2C2 for pipe 1
  (RX_ADDR_P1), see the data sheet.
  Check that the transmitter (TX) address is the same as the
  receiver (RX) pipe address.
*/

void setup(){

  Serial.begin(9600);
  printf_begin();
  // Start the serial
  // pinMode(CSN_PIN, OUTPUT);
  while (!Serial);
  Serial.println("NRF24L01P Receiver Starting...");

  /*
  // Start the radio, again set to min & slow as I'm guessing while testing theire really close to each other
  radio.begin();
  radio.setPALevel( RF24_PA_MIN ); // RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
  radio.setDataRate( RF24_250KBPS ); // RF24_250KBPS, RF24_1MBPS, RF24_2MBPS
  radio.setChannel( 110 );

  radio.setPayloadSize(sizeof(Data_Package));
  // radio.setCRCLength(RF24_CRC_16);

  radio.openWritingPipe(pipe);
  radio.openReadingPipe( 1, pipe  );
  radio.startListening();
  radio.printDetails();
  */

  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening(); //  Set the module as receiver

  setInitialPacketData();

}

void loop(){
  if (radio.available()) {
    radio.read(&data, sizeof(Data_Package));
    Serial.print(" got data.i32_0: => "); Serial.print(data.i32_0); 
    Serial.println();
  }
}

void setInitialPacketData(){

  data.i32_0 = 0;
  data.i32_1 = 0;
  data.i32_2 = 0;
  data.i32_3 = 0;
  data.i32_4 = 0;
  data.i32_5 = 0;
  data.i32_6 = 0;
  data.i32_7 = 0;

  // data.i32_8 = 0;
  // data.i32_9 = 0;
  // data.i32_a = 0;
  // data.i32_b = 0;
  // data.i32_c = 0;
  // data.i32_d = 0;
  // data.i32_e = 0;
  // data.i32_f = 0;

}

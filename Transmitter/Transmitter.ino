// Transmitter.ino

// Load in the libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <printf.h>
#include "Transmitter.h"

// Set the CE & CSN pins
#define CE_PIN   9
#define CSN_PIN 10

// This is the address used to send/receive
// const byte rxAddr[6] = "00001";
const byte address[6] = "00001"; // Address

const uint64_t pipe = 0xE8E8F0F0E1LL; // Define the transmit pipe

// Create a Radio
RF24 radio(CE_PIN, CSN_PIN); 


Data_Package data; //Create a variable with the above structure

uint8_t USE_SERIAL = 1;

// SPI: 10 (SS), 11 (MOSI), 12 (MISO), 13 (SCK). 
void setup() {

  if( USE_SERIAL ){
    while (!Serial);
    Serial.begin(9600);
    printf_begin();   
  }

  // pinMode(CSN_PIN, OUTPUT);
  // Start the Radio!
  radio.begin();
  
  // Power setting. Due to likelihood of close proximity of the devices, set as RF24_PA_MIN (RF24_PA_MAX is default)
  // radio.setPALevel( RF24_PA_MIN ); // RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX

  // radio.setPayloadSize(sizeof(Data_Package));
  // // Slower data rate for better range
  // radio.setDataRate( RF24_250KBPS ); // RF24_250KBPS, RF24_1MBPS, RF24_2MBPS
  // // radio.setChannel( 110 );

  // // Number of retries and set tx/rx address
  // radio.setRetries(15, 15);
  // radio.openWritingPipe(pipe);
  // // radio.openReadingPipe( 1, pipe  );

  // // Stop listening, so we can send!
  // radio.stopListening();

  /*
  radio.setPALevel( RF24_PA_MIN ); // RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
  radio.setDataRate( RF24_250KBPS ); // RF24_250KBPS, RF24_1MBPS, RF24_2MBPS
  radio.setChannel( 110 );

  radio.setPayloadSize(sizeof(Data_Package));

  radio.openWritingPipe(pipe);
  radio.stopListening();

  setInitialPacketData();
  */


  radio.openWritingPipe( address );
  radio.setAutoAck( false );
  radio.setDataRate( RF24_250KBPS );
  radio.setPALevel( RF24_PA_LOW );

  if( USE_SERIAL ){
    // And cruically print the details
    Serial.println(" init: done ... ");
    radio.printDetails();    
  }

}

uint32_t cc = 0;
void loop() {

  data.i32_0++;

  // Serial.println( (++cc ) );
  radio.write(&data, sizeof(Data_Package));
  // Wait a short while before sending the other one
  delay( 500 );

  if( USE_SERIAL ){
    Serial.print(" data.i32_0: => ");
    Serial.println( data.i32_0 );
  }

}

void setInitialPacketData(){

  data.i32_0 = 0;
  data.i32_1 = 1;
  data.i32_2 = 2;
  data.i32_3 = 3;
  data.i32_4 = 4;
  data.i32_5 = 5;
  data.i32_6 = 6;
  data.i32_7 = 7;

  // data.i32_8 = 8;
  // data.i32_9 = 9;
  // data.i32_a = 10;
  // data.i32_b = 11;
  // data.i32_c = 12;
  // data.i32_d = 13;
  // data.i32_e = 14;
  // data.i32_f = 15;

}

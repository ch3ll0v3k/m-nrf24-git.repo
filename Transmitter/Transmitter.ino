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

#define J_LX A6
#define J_LY A7

// #define A5 // MPU: (0)
// #define A4 // MPU: (1)

#define J_RX A3
#define J_RY A2


// This is the address used to send/receive
// const byte rxAddr[6] = "00001";
const byte address[6] = "00001"; // Address

const uint64_t pipe = 0xE8E8F0F0E1LL; // Define the transmit pipe

// Create a Radio
RF24 radio(CE_PIN, CSN_PIN); // , SPI_CLOCK_DIV2); 


Data_Package data; //Create a variable with the above structure

uint8_t USE_SERIAL = 1;

// SPI: 10 (SS), 11 (MOSI), 12 (MISO), 13 (SCK). 
void setup() {

  if( USE_SERIAL ){
    Serial.begin(9600);
    printf_begin();   
    while (!Serial);
  }

  // pinMode(CSN_PIN, OUTPUT);
  // Start the Radio!
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


  radio.begin();
  delay(2);
  // radio.setChannel( 110 );
  radio.setAutoAck( false );
  radio.setDataRate( RF24_250KBPS );
  radio.setPALevel( RF24_PA_MIN );
  radio.openWritingPipe( address );

  delay(2);
  radio.printDetails();

  if( USE_SERIAL ){
    // And cruically print the details
    Serial.println(" init: done ... ");
    // radio.printDetails();    
  }

}

void loop() {

  // return;

  data.i32_0++;

  // data.j_ly = (2500 +750) - map( analogRead( J_LY ), 300, 700, 750, 2500);

  /*
  data.j_ly = map( analogRead( J_LY ), 300, 700, 0, 400) - 200;
  data.j_lx = map( analogRead( J_LX ), 300, 700, 0, 400) - 200;

  data.j_ry = map( analogRead( J_RY ), 300, 700, 0, 400) - 200;
  data.j_rx = map( analogRead( J_RX ), 300, 700, 0, 400) - 200;
  */

  Serial.println( data.i32_0 );
  radio.write(&data, sizeof(Data_Package));

  /*
  if( USE_SERIAL ){
    // Serial.print(" out data.i32_0: => "); Serial.println( data.i32_0 );

    // Serial.print( 210 ); Serial.print(","); 
    Serial.print( analogRead( J_LY ) ); Serial.print(","); 
    Serial.print( data.j_ly ); Serial.print(","); 
    // Serial.print( j_rx ); Serial.print(","); 
    // Serial.print( j_ry ); Serial.print(","); 
    // Serial.print( -210 ); Serial.print(","); 
    Serial.println();

  }else{
    Serial.println( data.i32_0 );
  }
  */

  delay( 500 );

}

void setInitialPacketData(){

  data.i32_0 = 0;
  data.j_lx = 0;
  data.j_ly = 0;
  data.j_rx = 0;
  data.j_ry = 0;

}

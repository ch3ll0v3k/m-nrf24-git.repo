// Load up the libraries
#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <printf.h>
#include <Servo.h>

#include "Receiver.h"
// #include "ESC.h"

// define the pins
#define CE_PIN 9
#define CSN_PIN 10

// Create a Radio
RF24 radio(CE_PIN, CSN_PIN);

// The tx/rx address
const uint64_t pipe = 0xE8E8F0F0E1LL; // Define the transmit pipe
// const byte address[6] = "00001";
const byte address[5] = {'R','x','A','A','A'};

Data_Package data; //Create a variable with the above structure

Servo ESC;

unsigned long lastReceiveTime = 0;
unsigned long currentTime = 0;

uint8_t radioParamsInited = 0;

/*
  Check the reading and writing pipe addresses.
  First, the default is 0xE7E7E7E7E7 for pipe 0 (RX_ADDR_P0) and 0xC2C2C2C2C2 for pipe 1
  (RX_ADDR_P1), see the data sheet.
  Check that the transmitter (TX) address is the same as the
  receiver (RX) pipe address.
*/

int8_t _speed = 0;

// ESC myESC (6, 1000, 2000, 500);   // ESC_Name (ESC PIN, Minimum Value, Maximum Value, Arm Value)

int32_t getSerialVal( String req );

void setup(){

  Serial.begin(9600);
  printf_begin();
  // Start the serial
  pinMode(CE_PIN, OUTPUT);
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
  // delay(2);
  radio.setChannel( 120 );
  // radio.openReadingPipe( 1, address );
  radio.setAutoAck( false );
  radio.setDataRate( RF24_250KBPS);
  radio.setPALevel( RF24_PA_HIGH );
  // radio.setCRCLength( RF24_CRC_8 );
  // radio.setPayloadSize(sizeof(Data_Package));

  // radio.openWritingPipe( address );
  radio.openReadingPipe( 1, address );

  radio.startListening(); //  Set the module as receiver
  delay( 2 );
  radio.printDetails();

  setInitialPacketData();



  ESC.attach( 6 );
  // ESC.write( 800 );


  uint32_t v0 = getSerialVal(" v0 => ");
  ESC.write( v0 );

  uint32_t v1 = getSerialVal(" v1 => ");
  ESC.write( v1 );


  getSerialVal(" Press any key to start");

}

void loop(){

    //return;

   // int32_t loopVal= getSerialVal(" loopVal ");
   // ESC.write( loopVal );
   // return;
 
  if( radio.available()) {
    radio.read(&data, sizeof(Data_Package));

    // Serial.println( data.j_ly );
    // Serial.println( data.i32_0 );
    ESC.write( data.j_ly );
    Serial.println( data.j_ly );

    // Adjust values => 
    // radioParamsInited = 1;

    // Serial.print( 210 ); Serial.print(","); 
    // Serial.print( data.i32_0 ); Serial.print(","); 
    // Serial.print( data.j_lx ); Serial.print(","); 
    // Serial.print( data.j_ly ); Serial.print(","); 
    // Serial.print( data.j_rx ); Serial.print(","); 
    // Serial.print( data.j_ry ); Serial.print(","); 
    // Serial.print( -210 ); Serial.print(","); 
    // Serial.println();
  
  }

 
  // Serial.println( ++_speed );
  // ESC.write( _speed ); // SPEED

  // delay(50);
}

void setInitialPacketData(){

  data.i32_0 = 0;
  data.j_lx = 0;
  data.j_ly = 800;
  data.j_rx = 0;
  data.j_ry = 0;

}


int32_t getSerialVal( String req ){

  Serial.println( req);
  while( !Serial.available() );

  int32_t res = Serial.parseInt();
  Serial.print(" Got: "); Serial.println( res );
  return res; 
}

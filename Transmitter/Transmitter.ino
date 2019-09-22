// Transmitter.ino

// Load in the libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Set the CE & CSN pins
#define CE_PIN   9
#define CSN_PIN 10

// This is the address used to send/receive
// const byte rxAddr[6] = "00001";

const uint64_t pipe = 0xE8E8F0F0E1LL; // Define the transmit pipe

// Create a Radio
RF24 radio(CE_PIN, CSN_PIN); 

struct Data_Package {
  byte b0;
  byte b1;
  byte b2;
  byte b3;
  byte b4;
  byte b5;
  byte b6;
  byte b7;
  byte b8;
  byte b9;
  byte ba;
  byte bb;
  byte bc;
  byte bd;
};

Data_Package data; //Create a variable with the above structure


void setup() {
  
  // Start up the Serial connection
  while (!Serial);
  Serial.begin(9600);
  // pinMode(CSN_PIN, OUTPUT);
  // Start the Radio!
  radio.begin();
  
  // Power setting. Due to likelihood of close proximity of the devices, set as RF24_PA_MIN (RF24_PA_MAX is default)
  radio.setPALevel(RF24_PA_MIN); // RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX

  radio.setPayloadSize(sizeof(Data_Package));
  // Slower data rate for better range
  radio.setDataRate( RF24_250KBPS ); // RF24_250KBPS, RF24_1MBPS, RF24_2MBPS
  radio.setChannel( 110 );

  // Number of retries and set tx/rx address
  // radio.setRetries(15, 15);
  radio.openWritingPipe(pipe);
  radio.openReadingPipe( 1, pipe  );

  // Stop listening, so we can send!
  radio.stopListening();
  Serial.println(" init: done ... ");

  data.ba = 1;
  data.bb = 10;
  data.bc = 20;
  data.bd = 50;

}

uint32_t cc = 0;
void loop() {

  data.b3 = 4;
  data.b7 = 10;
  data.ba = 2;
  // Serial.println( (++cc ) );
  radio.write(&data, sizeof(Data_Package));
  // Wait a short while before sending the other one
  delay(1000);

  /*
    Serial.println(" Sending: ");
    Serial.print(data.b0); Serial.print(","); 
    Serial.print(data.b1); Serial.print(","); 
    Serial.print(data.b2); Serial.print(","); 
    Serial.print(data.b3); Serial.print(","); 
    Serial.print(data.b4); Serial.print(","); 
    Serial.print(data.b5); Serial.print(","); 
    Serial.print(data.b6); Serial.print(","); 
    Serial.print(data.b7); Serial.print(","); 
    Serial.print(data.b8); Serial.print(","); 
    Serial.print(data.b9); Serial.print(","); 
    Serial.print(data.b2); Serial.print(","); 
    Serial.print(data.ba); Serial.print(","); 
    Serial.print(data.bb); Serial.print(","); 
    Serial.print(data.bc); Serial.print(","); 
    Serial.print(data.bd); Serial.print(","); 
    Serial.println();
    */


}

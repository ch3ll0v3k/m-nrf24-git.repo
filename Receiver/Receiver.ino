// Load up the libraries
#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <printf.h>

// define the pins
#define CE_PIN  9
#define CSN_PIN 10

// Create a Radio
RF24 radio(CE_PIN, CSN_PIN);

// The tx/rx address
const byte rxAddr[6] = "00001";

const uint64_t pipe = 0xE8E8F0F0E1LL; // Define the transmit pipe

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

unsigned long lastReceiveTime = 0;
unsigned long currentTime = 0;

/*

  Check the reading and writing pipe addresses.

  First, the default is 0xE7E7E7E7E7 for pipe 0 (RX_ADDR_P0) and 0xC2C2C2C2C2 for pipe 1
  (RX_ADDR_P1), see the data sheet.
  Check that the transmitter (TX) address is the same as the
  receiver (RX) pipe address.
*/

void setup()
{

  Serial.begin(9600);
  printf_begin();
  // Start the serial
  // pinMode(CSN_PIN, OUTPUT);
  while (!Serial);
  Serial.println("NRF24L01P Receiver Starting...");

  // Start the radio, again set to min & slow as I'm guessing while testing theire really close to each other
  radio.begin();
  // radio.setChannel(118);
  radio.setPALevel(RF24_PA_MIN);   // RF24_PA_MIN ,RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
  radio.setDataRate( RF24_250KBPS ); // RF24_250KBPS, RF24_1MBPS, RF24_2MBPS
  radio.setChannel( 110 );
  /*
    radio.setCRCLength(RF24_CRC_DISABLED);
    radio.setAddressWidth(addr_len);
    radio.setPayloadSize(len);
    radio.setChannel(chan);
  */
  radio.setPayloadSize(sizeof(Data_Package));
  // radio.setCRCLength(RF24_CRC_16);
  // Set the reading pipe and start listening
  radio.openWritingPipe(pipe);
  radio.openReadingPipe( 1, pipe  );
  radio.startListening();
  // resetDataPacket();

  radio.printDetails();
}

void loop()
{
  if (radio.available()) {
    // while( radio.available() ){
    radio.read(&data, sizeof(Data_Package));
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
    // delay(1);
    //}
  }
}



void resetDataPacket() {
  data.b0 = 0; // byte
  data.b1 = 0; // byte
  data.b2 = 0; // byte
  data.b3 = 0; // byte
  data.b4 = 0; // byte
  data.b5 = 0; // byte
  data.b6 = 0; // byte
  data.b7 = 0; // byte
  data.b8 = 0; // byte
  data.b9 = 0; // byte
  data.ba = 0; // byte
  data.bb = 0; // byte
  data.bc = 0; // byte
  data.bd = 0; // byte
}

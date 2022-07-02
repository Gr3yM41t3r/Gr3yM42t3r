/*
  Arduino Wireless Network - Multiple NRF24L01 Tutorial
        == Node 02 (Child of Master node 00) ==    
*/

#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>

RF24 radio(7, 8);               // nRF24L01 (CE,CSN)
RF24Network network(radio);      // Include the radio in the network

const uint16_t this_node = 011;   // Address of our node in Octal format ( 04,031, etc)
const uint16_t master00 = 00;    // Address of the other node in Octal format
int counter=0;
char message[32]=";"; ;
String stringOne = "20;30;40;50;";
String abc;
char buffer2[5];



void setup() {
  SPI.begin();
  radio.begin();
  Serial.begin(9600);
  network.begin(90, this_node);  //(channel, node address)
  radio.setDataRate(RF24_2MBPS);
}

void loop() {
  
  abc=stringOne+counter;
  abc.toCharArray(message, 32);

  network.update();
  RF24NetworkHeader header(master00);     // (Address where the data is going)
  bool ok = network.write(header, &message, sizeof(message)); // 
  Serial.println(ok);
  delay(1000);
  counter++;
}

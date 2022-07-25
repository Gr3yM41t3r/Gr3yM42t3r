//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>

int counterSending=0;
int counterReceived=0;
const uint16_t this_node = 00;   // Address of this node in Octal format ( 04,031, etc)
const uint16_t accesspoint1 = 01;      // Address of the other node in Octal format
const uint16_t slaveNode1 = 011;

String incomingByte ; // for incoming serial data

RF24 radio(7, 8);               // nRF24L01 (CE,CSN)
RF24Network network(radio); 
String amine;
int counter =0;
char message[32];
int attemptCounter;

void setup()
{
  Serial.begin(9600);
  SPI.begin();
  radio.begin();
  network.begin(90, this_node);  //(channel, node address)
  radio.setDataRate(RF24_2MBPS);
  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(50);                       // wait for a second
  digitalWrite(5, LOW);    // turn the LED off by making the voltage LOW
  delay(50);                       // wait for a second
  digitalWrite(5, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(50);                       // wait for a second
  digitalWrite(5, LOW);  
  pinMode(13, OUTPUT);

    

}


void loop()
{
  attemptCounter=0;
  counter++;
  network.update();
  //===== Receiving =====//
  while ( network.available() ) {     // Is there any incoming data?
    RF24NetworkHeader header;
    char message[32];
    network.read(header, &message, sizeof(message)); // Read the incoming data
    counterReceived++;
    Serial.println(message);    
    digitalWrite(5, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(50);                       // wait for a second
    digitalWrite(5, LOW);  
    }
    if (Serial.available() > 0) {
    // read the incoming byte:
        amine = Serial.readString();
        Serial.println(amine);
        amine.toCharArray(message, 32);
        network.update();
        RF24NetworkHeader header(accesspoint1); 
        bool ok = network.write(header, &message, sizeof(message));
        Serial.println(ok);
        while(!ok){
          attemptCounter++;
          Serial.println("sending again");
          delay(1000);
          ok = network.write(header, &message, sizeof(message));
          Serial.println(ok);
          if(attemptCounter>10){
             Serial.print("node is unreacheable");
             digitalWrite(5, HIGH);   // turn the LED on (HIGH is the voltage level)
                delay(5000);                       // wait for a second
                digitalWrite(5, LOW); 
              break;
                
          }
        }
        Serial.print("received");
  
   
 
  }
  delay(1000);

  

  
  
}

/*
  Arduino Wireless Network - Multiple NRF24L01 Tutorial
        == Node 02 (Child of Master node 00) ==
*/

#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN 2  
#define DHTTYPE    DHT11     // DHT 22 (AM2302)

RF24 radio(7, 8);               // nRF24L01 (CE,CSN)
RF24Network network(radio);      // Include the radio in the network

const uint16_t this_node = 011;   // Address of our node in Octal format ( 04,031, etc)
const uint16_t master00 = 00;    // Address of the other node in Octal format
int counter = 0;
char message[32] = ";"; ;
String stringOne = "amine";
String abc;
char buffer2[5];

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;



struct student{
   String name;
   int age;
   int roll_no;
};

struct Payload{
  char sender[32];
  int counter;
};


Payload payload;

Payload payload2;
void setup() {
  SPI.begin();
  radio.begin();
  Serial.begin(9600);
  network.begin(90, this_node);  //(channel, node address)
  radio.setDataRate(RF24_2MBPS);
  pinMode(5, OUTPUT);                    // wait for a second
  digitalWrite(5, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);                       // wait for a second
  digitalWrite(5, LOW);
   dht.begin();
     sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);
  delayMS = sensor.min_delay / 1000;

}

void loop() {


  /*String(this_node).toCharArray(payload.sender,32);
  payload.counter=counter;
  network.update();
  RF24NetworkHeader header(master00);     // (Address where the data is going)
  bool ok = network.write(header, &payload, sizeof(payload)); //
  
     while(!ok){
         ok = network.write(header, &payload, sizeof(payload));
      }
   Serial.println(payload.sender);
   Serial.println(payload.counter);

  delay(1000);
  counter++;
  
*/

  
  network.update();
  //===== Receiving =====//
  while ( network.available() ) {  
     Serial.println("33333333333dfoqsokmdklj3");// Is there any incoming data?
    RF24NetworkHeader header;
    char message[32];
    network.read(header, &payload2, sizeof(payload2)); // Read the incoming data
     Serial.println(String(payload2.sender));
    if(String(payload2.sender)=="ON"){
        digitalWrite(5, HIGH);
    }else{
    digitalWrite(5, LOW); 
    }
      // turn the LED on (HIGH is the voltage level)
   

    } 
    

    
}

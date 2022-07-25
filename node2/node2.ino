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

const uint16_t this_node = 01;   // Address of our node in Octal format ( 04,031, etc)
const uint16_t master00 = 00;    // Address of the other node in Octal format
int counter = 0;
char message[32] = ";"; ;
String stringOne = "20;30;40;50;";
String abc;
char buffer2[5];

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;

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

  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  Serial.print(F("Temperature: "));
  Serial.print(event.temperature);
  Serial.println(F("°C"));
  dht.humidity().getEvent(&event);
  Serial.print(F("Humidity: "));
  Serial.print(event.relative_humidity);
  Serial.println(F("%"));

  
 // abc = stringOne + counter;
  //abc.toCharArray(message, 32);
  abc="temp: "+ String(event.temperature) +" hum: "+String(event.relative_humidity);
  abc.toCharArray(message, 32);
  network.update();
  RF24NetworkHeader header(master00);     // (Address where the data is going)
  bool ok = network.write(header, &message, sizeof(message)); //
  Serial.println(ok);
  delay(2500);
  counter++;
  /*network.update();
  //===== Receiving =====//
  while ( network.available() ) {     // Is there any incoming data?
    RF24NetworkHeader header;
    char message[32];
    network.read(header, &message, sizeof(message)); // Read the incoming data
    Serial.println(String(message)); 
    if(String(message)=="ON"){
      
    digitalWrite(4, HIGH);   // turn the LED on (HIGH is the voltage level)

    }else if (String(message)=="OFF"){
            // wait for a second
    digitalWrite(4, LOW); 

    }

    }*/
}

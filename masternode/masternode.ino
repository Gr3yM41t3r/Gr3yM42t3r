//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
int counterSending=0;
int counterReceived=0;
const uint16_t this_node = 00;   // Address of this node in Octal format ( 04,031, etc)
const uint16_t accesspoint1 = 01;      // Address of the other node in Octal format
const uint16_t slaveNode1 = 011;


RF24 radio(7, 8);               // nRF24L01 (CE,CSN)
RF24Network network(radio); 


void setup()
{
  Serial.begin(9600);
  lcd.init();                      
  lcd.backlight();
  SPI.begin();
  radio.begin();
  network.begin(90, this_node);  //(channel, node address)
  radio.setDataRate(RF24_2MBPS);
  Serial.println("started program listening online...");

}


void loop()
{

  network.update();
  //===== Receiving =====//
  while ( network.available() ) {     // Is there any incoming data?
    RF24NetworkHeader header;
    char message[32];
    network.read(header, &message, sizeof(message)); // Read the incoming data
    lcd.setCursor(0,3);
    lcd.print("packet received node");
    counterReceived++;
    Serial.println(message);    
    }

  lcd.setCursor(5,0);
  lcd.print("Master node");
  lcd.setCursor(0,1);
  lcd.print("*packet sent:");
  lcd.print(counterSending);
  lcd.setCursor(0,2);
  lcd.print("count:");
  lcd.print(counterReceived);
    lcd.setCursor(0,3);
  lcd.print("                 ");
  

  
  
}

#include <PZEM004Tv30.h>
#include <SoftwareSerial.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>

const uint16_t this_node = 01;   // Address of this node in Octal format ( 04,031, etc)
const uint16_t master = 00;  


#define PZEM_RX_PIN 3
#define PZEM_TX_PIN 4



SoftwareSerial pzemSWSerial(PZEM_RX_PIN, PZEM_TX_PIN);
PZEM004Tv30 pzem(pzemSWSerial);
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
RF24 radio(7, 8);               // nRF24L01 (CE,CSN)
RF24Network network(radio); 


int shouldSend=0;
String message;


struct Payload{
  char pl[64];
  int counter;
};


Payload payload;
Payload payload2;

void setup() {
  // put your setup code here, to run once:
    SPI.begin();
    radio.begin();
    network.begin(90, this_node);  //(channel, node address)
    radio.setDataRate(RF24_2MBPS);
    lcd.init(); 
    lcd.backlight();

}

void loop() {
  // put your main code here, to run repeatedly:

    float voltage = pzem.voltage();
    float current = pzem.current();
    float power = pzem.power();
    float energy = pzem.energy();
    float frequency = pzem.frequency();
    float pf = pzem.pf();

    lcd.setCursor(2,0);
    lcd.print(String(voltage));
    lcd.print("  V  ");
    lcd.setCursor(2,1);
    lcd.print(String(current)+"  Ah  ");
    lcd.setCursor(2,2);
    lcd.print(String(power)+"  Wh   ");
    lcd.setCursor(2,3);
    lcd.print(String(energy)+"  kWh");
    lcd.print(" "+String(pf));

    if(shouldSend==15){
      shouldSend=0;
      message=String(voltage)+";"+String(current)+";"+String(power)+";"+String(energy)+";"+String(frequency)+";"+String(pf)+";";
      message.toCharArray(payload.pl,64);
      RF24NetworkHeader header(master); 
      if(!network.write(header, &payload, sizeof(payload))){
          delay(200);
          bool ok = network.write(header, &payload, sizeof(payload));
        }
      
    }
    shouldSend++;

    
    network.update();
    while ( network.available() ) {     // Is there any incoming data?
        RF24NetworkHeader header2;
        network.read(header2, &payload2, sizeof(payload2)); // Read the incoming data
        if(String(payload2.pl)=="BLOFF"){
          lcd.noBacklight();
        }else if(String(payload2.pl)=="BLON"){
          lcd.backlight();
        }else if(String(payload2.pl)=="RSTPWR"){
          pzem.resetEnergy();
        }
       }
      delay(2000);
    


    

}

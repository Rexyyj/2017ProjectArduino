#include <SoftwareSerial.h>
//SIM800 TX is connected to Arduino D8
#define SIM800_TX_PIN 5
//SIM800 RX is connected to Arduino D7
#define SIM800_RX_PIN 4
//Create software serial object to communicate with SIM800
SoftwareSerial serialSIM800(SIM800_TX_PIN,SIM800_RX_PIN);
void setup() {
//Begin serial comunication with Arduino and Arduino IDE (Serial Monitor)
    Serial.begin(9600);
    while(!Serial);
//Being serial communication witj Arduino and SIM800
    serialSIM800.begin(9600);
    delay(1000);
    Serial.println("Setup Complete!");
    Serial.println("Sending SMS...");
//Set SMS format to ASCII
    serialSIM800.write("AT\r\n");
    //Serial.write(serialSIM800.read());
    delay(1000);
    serialSIM800.write("AT+CMGF=1\r\n");
    delay(1000);
   // Serial.write(serialSIM800.read());
    delay(1000);
//Send new SMS command and message number
    serialSIM800.write("AT+CMGS=\"+8618916129865\"\r\n");
    delay(1000);
    //Serial.write(serialSIM800.read());
    delay(1000);
//Send SMS content
    serialSIM800.println("UNO !!!");
    delay(1000);
    //Serial.write(serialSIM800.read());
    delay(1000);
//Send Ctrl+Z / ESC to denote SMS message is complete
    serialSIM800.write(0x1A);
    delay(1000);
    //Serial.write(serialSIM800.read());
    delay(1000);
    Serial.println("SMS Sent!");
}
void loop() {
}

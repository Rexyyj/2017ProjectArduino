//SIM800 TX is connected to Arduino D8
#define SIM800_TX_PIN 5
//SIM800 RX is connected to Arduino D7
#define SIM800_RX_PIN 4

String MSG("");
//Create software serial object to communicate with SIM800
SoftwareSerial serialSIM800(SIM800_TX_PIN,SIM800_RX_PIN);
void setup(){
//Begin serial comunication with Arduino and Arduino IDE (Serial Monitor)
delay(1000);
Serial.begin(9600);
while(!Serial);
//Being serial communication witj Arduino and SIM800
serialSIM800.begin(9600);
delay(1000);
Serial.println("Setup Complete!");
serialSIM800.write("AT\r\n");
}
void getMSG(String &p_MSG,SoftwareSerial &p_serial)
{
    p_MSG="";
    //while(!p_serial.available()) ;
    for(char in='\0',flag=0;p_serial.available();)
    {
     // Serial.println("24532543535:");
      in=p_serial.read();
        if(in=='+')
            flag=1;
        if(flag&&((in=='\r')||(in=='\n')))
            break;
        if(flag)
            p_MSG+=in;
        delay(100);
    }
    p_MSG.trim();
    p_serial.flush();
   //Serial.println( p_MSG);
}

bool chkMSG(String &p_MSG)
{
    for(int p_begin=0;(p_begin+4)<p_MSG.length()+1;p_begin++)
    {
        if(p_MSG.substring(p_begin,p_begin+4)=="+CMT")
            return true;
    }
    return false;
}
void loop()
{
  getMSG(MSG,serialSIM800);
 if(chkMSG(MSG))
  {
    Serial.println("SUCCEED");   
  }
  
}

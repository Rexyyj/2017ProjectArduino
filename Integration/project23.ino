#include <SoftwareSerial.h>

int human1=10;
int human2=11;
int human3=12;
//human detector
int buzzerPin=13;//buzzer
int speakerPin=9;//speaker
int modeLED=8;

const int  buttonPin = 7;
int buttonPushCounter = 0;   
int buttonState = 0;         
int lastButtonState = 0;     
int duration = 1;//vibration sensor

unsigned long tLeft=3000;
volatile int mode=1;
volatile int newmode=1;

volatile int Pin2state=LOW;
unsigned long tmax=33720000;


/*SMS SETUP*************************************************************/
#define SIM800_TX_PIN 5
#define SIM800_RX_PIN 4
SoftwareSerial serialSIM800(SIM800_TX_PIN,SIM800_RX_PIN);

/************/
String MSG("");

/**************************************************************/

void setup() {
pinMode(human1,INPUT);
pinMode(human2,INPUT);
pinMode(human3,INPUT);
pinMode(modeLED,OUTPUT);

 Serial.begin(9600);
 pinMode(buttonPin, INPUT);
  pinMode(speakerPin,OUTPUT);

   while(!Serial);
    serialSIM800.begin(9600);
    delay(1000);
    serialSIM800.write("AT\r\n");
    delay(1000);
}

int infraredSensor()
{
  int state1=digitalRead(human1);
  int state2=digitalRead(human2);
  int state3=digitalRead(human3);

  if(state1==HIGH||state2==HIGH||state3==HIGH)
    return 1;
  else
    return 0;
}

void GPSposition()
{


 
}

void buzzer()
{ 
//  pinMode(buzzerPin,OUTPUT);
//  for(int i=200;i<=800;i++)                    //用循环的方式将频率从200HZ 增加到800HZ
//{
//  tone(buzzerPin,i);                            //在四号端口输出频率
// delay(1);                              //该频率维持1毫秒   
//}
//delay(300);                            //最高频率下维持0.3秒钟
//for(int i=800;i>=200;i--)
//{
//  tone(buzzerPin,i);
// delay(1);
//}
//digitalWrite(buzzerPin,0);

pinMode(buzzerPin,OUTPUT);
digitalWrite(buzzerPin,HIGH);
delay(2000);
digitalWrite(buzzerPin,LOW);

}

void warning1()
{
 digitalWrite(speakerPin,HIGH);
 delay(100);
 digitalWrite(speakerPin,LOW);
 delay(5000);

}

void sendMessage()
{

    serialSIM800.write("AT+CMGF=1\r\n");
    delay(1000);
    serialSIM800.write("AT+CMGS=\"+8618121330102\"\r\n");
    delay(1000);
    serialSIM800.println("UNO !!!");
    delay(1000);
    serialSIM800.write(0x1A);
    delay(1000);
    Serial.println("SMS Sent!");
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



void receiveMessage()
{
   getMSG(MSG,serialSIM800);
 if(chkMSG(MSG))
  {  
    newmode=2;
  }
  else
  {newmode=1;}
}

int modeJudge()
{
  receiveMessage();
  int temp;
  temp=mode;
  mode=newmode;
  if(temp==mode)
  {return 0;}
  else
  {return 1;}
}




void modeCase1()
{
  digitalWrite(modeLED,LOW);
   while(infraredSensor())
  {
      buzzer();
      delay(100);
      if(modeJudge()==1)
      {return;}
      delay(100);
      warning1();
      delay(100);
      if(modeJudge()==1)
      {return;}
      delay(100);
         buzzer();
      delay(100);
      if(modeJudge()==1)
      {return;}
      delay(100);
      warning1();
      delay(100);
      if(modeJudge()==1)
      {return;}
      delay(100);
      if(infraredSensor()==1)
      {
         GPSposition();
    //sendMessage();
      }
  }
  delay(500);
}

void modeCase2_sub()
{
 
   while(infraredSensor())
  {
    GPSposition();
    //sendMessage();
    buzzer();
    warning1();
    buzzer();
    warning1();
  }
}
void tranPass()
{
  
    // read the pushbutton input pin:
    while(!digitalRead(buttonPin))
    {
       modeCase2_sub();
    }
    while(digitalRead(buttonPin))
    {
       modeCase2_sub();
    }//无变化时一直在循环中，直到遇到变化时接连跳出两个循环——开启
    
    while(1){
        duration = pulseIn(buttonPin,HIGH,5000000);
   //读取引脚上的高电平持续时间，并且把结果赋值给duration变量，超时返回0(unsigned long);pulseIn默认单位微秒(us)
        if(duration==0) {
          duration=1;
        return ;
       }
        }
    // Delay a little bit to avoid bouncing
    delay(50);
}
void  modeCase2()
{ 
   digitalWrite(modeLED,HIGH);
  unsigned long t1,t2,t;
  t1=millis();
  while(1)
  {
    modeCase2_sub();
    t2=millis();
    if(t2<t1)
 { t=tmax-t2+t1;}
  else
{  t=t2-t1;}
  if(t>10000)
  break;
  }
  tranPass();
  mode=1;
  return ;
}



int tranState=0;
void loop()
{
  switch(mode)
 { case 1: modeCase1();break;//normal detection
  case 2: modeCase2();break;//special detection
 }
 delay(500);
}

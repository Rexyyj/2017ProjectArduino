double data[100];
double temp;
const int soundPin=7;
void setup() 
{
  Serial.begin(9600);
  pinMode(soundPin,INPUT);
}
void loop() 
{ 
  int num=0;
  if(digitalRead(soundPin))
{
  do
  {
  for (int i=0;i<1000;i++)
  {
    temp=analogRead(A0);
    data[i]=(temp*120.0/1024.0*1.515);
    Serial.print("db:");
    Serial.println(data[i]);
  }
  delay(1000);
  }while(num<5);
}
}

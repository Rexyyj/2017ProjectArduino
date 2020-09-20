int human1=10;
int state=0;
int bzzzpin=13;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode (human1,INPUT);
  pinMode(bzzzpin,OUTPUT);
}

void loop() {
 state=digitalRead(human1);
 if(state==HIGH)
{ digitalWrite(bzzzpin,HIGH);
delay(2000);
}
 delay(100);
 digitalWrite(bzzzpin,LOW);
 // put your main code here, to run repeatedly:

}

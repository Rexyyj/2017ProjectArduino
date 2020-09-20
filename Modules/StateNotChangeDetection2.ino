// this constant won't change:
const int  buttonPin = 2;    // the pin that the pushbutton is attached to


// Variables will change:
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button
int duration = 1;

void setup() {
  // initialize the button pin as a input:
  pinMode(buttonPin, INPUT);
  // initialize serial communication:
  Serial.begin(9600);
}


void loop() {
     // read the pushbutton input pin:
    while(!digitalRead(buttonPin)); //低电平时一直在循环中，直到遇到高电平才跳出——开启
    
    while(1){
    lastButtonState = buttonState;
    buttonState = digitalRead(buttonPin);
    if (buttonState != lastButtonState) {
      delay(50);
      buttonState = digitalRead(buttonPin);//更新buttonState
      if (buttonState == LOW) {
        duration = pulseIn(buttonPin,LOW,5000000); //读取引脚上的低电平持续时间，最大时间间隔为5秒(timeout)，并且把结果赋值给duration变量,超时返回0(unsigned long)
        if(duration==0) {
        Serial.println(1);
        break;}//如果持续时间大于指定时间，通过串口输出1
        }
    // Delay a little bit to avoid bouncing
    delay(50);
    }
  // save the current state as the last state, for next time through the loop
    }
    lastButtonState = buttonState;
}

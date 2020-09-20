void setup()
{
}

void loop()
{
  while(1){
    for(int count=0;count<10;count++){
    for(int i=200;i<=800;i++)                    //用循环的方式将频率从200HZ 增加到800HZ
    {
      pinMode(13,OUTPUT);
      tone(13,i);                            //在四号端口输出频率
      delay(1);                              //该频率维持1毫秒   
      }
      delay(300);                            //最高频率下维持0.3秒钟
      for(int i=800;i>=200;i--)
      {
        pinMode(13,OUTPUT);
        tone(13,i);
        delay(1);
        }
       }
    }
}

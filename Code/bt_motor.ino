#include <SoftwareSerial.h>
//0 - fwd , 1 - rwd
SoftwareSerial bt(11,10); //tx,rx
int in1 = 2 , in2 = 3 , in3 = 4 , in4 = 5,del=200;
void setup() {
  bt.begin(9600);
  Serial.begin(9600); 
  pinMode(in1 , OUTPUT);
 pinMode(in2 , OUTPUT);
 pinMode(in3 , OUTPUT);
 pinMode(in4 , OUTPUT);
 digitalWrite(in1 , LOW);
 digitalWrite(in2 , LOW);
 digitalWrite(in3 , LOW);
 digitalWrite(in4 , LOW);
  
}

void loop() {
if(bt.available())
{
  char data = bt.read();
  int dec;
  Serial.print(data);
  if(data == '1')
  {
    dec = 0;
    yaxis(dec);
  }

  if(data == '2')
  {
    dec = 1;
    yaxis(dec);
  }

  if(data == '3')
  {
    dec = 1;
    xaxis(dec);
  }

  if(data == '4')
  {
    dec = 0;
    xaxis(dec);
  }

}  

}

void yaxis(int x)
{
  if(x == 0)
  {
    digitalWrite(in2, LOW);
    digitalWrite(in4, LOW);

    for(int pul = 0 ; pul<= del ; pul=pul+10)
    {
      digitalWrite(in1 , HIGH);
      digitalWrite(in3 , HIGH);
      delay(pul);
      digitalWrite(in1 , LOW);
      digitalWrite(in3 , LOW);
    }
    //stop_all();

  }

  if(x == 1)
  {
    digitalWrite(in1, LOW);
    digitalWrite(in3, LOW);

    for(int pul = 0 ; pul<= del ; pul=pul+10)
    {
      digitalWrite(in2 , HIGH);
      digitalWrite(in4 , HIGH);
      delay(pul);
      digitalWrite(in2 , LOW);
      digitalWrite(in4 , LOW);
    }
    //stop_all();
  }
}

void xaxis(int x)
{
  if(x == 0)
  {
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);

    for(int pul = 0 ; pul<= del ; pul=pul+10)
    {
      digitalWrite(in1 , HIGH);
      digitalWrite(in4 , HIGH);
      delay(pul);
      digitalWrite(in1 , LOW);
      digitalWrite(in4 , LOW);
    }
    //stop_all();
  }

  if(x == 1)
  {
    digitalWrite(in1, LOW);
    digitalWrite(in4, LOW);

    for(int pul = 0 ; pul<= del ; pul=pul+10)
    {
      digitalWrite(in2 , HIGH);
      digitalWrite(in3 , HIGH);
      delay(pul);
      digitalWrite(in2 , LOW);
      digitalWrite(in3 , LOW);
    }
    //stop_all();
  }
}

/*void stop_all()
{
  delay(del);
  digitalWrite(in1 , LOW);
  digitalWrite(in2 , LOW);
  digitalWrite(in3 , LOW);
  digitalWrite(in4 , LOW);

}*/

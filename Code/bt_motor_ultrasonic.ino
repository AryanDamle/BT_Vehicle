#include <SoftwareSerial.h>

#define CLR_FRONT 0x01
#define CLR_BACK 0x02
#define CLR_ALL_CLEAR 0x00
#define CLR_RIGHT 0x04

#define SAFE_DIST 20

#define DIR_FWD 0
#define DIR_REV 1
#define DIR_RIGHT 1
#define DIR_LEFT 0

#define CMD_FWD '1'
#define CMD_REV '2'
#define CMD_RIGHT '3'
#define CMD_LEFT '4'


//0 - fwd , 1 - rwd
SoftwareSerial bt(11,10); //tx,rx

int in1 = 2 , in2 = 3 , in3 = 4 , in4 = 5, del = 200;
int trig1 = 6 , echo1 = 7 , trig2 = 8 , echo2 = 9;

void setup() 
{
  bt.begin(9600);
  Serial.begin(9600); 
  pinMode(in1 , OUTPUT);
  pinMode(in2 , OUTPUT);
  pinMode(in3 , OUTPUT);
  pinMode(in4 , OUTPUT);

  pinMode(trig1 , OUTPUT);
  pinMode(trig1 , OUTPUT);
  pinMode(echo1 , INPUT_PULLUP);
  pinMode(echo2 , INPUT_PULLUP);

  digitalWrite(in1 , LOW);
  digitalWrite(in2 , LOW);
  digitalWrite(in3 , LOW);
  digitalWrite(in4 , LOW);
}

void loop() 
{
  int clearance = M_Dist();
  delay(100);
  
  if(bt.available())
  {
    char cmd = bt.read();
    
    Serial.print(cmd);
    if(cmd == CMD_FWD && (clearance & CLR_FRONT) != CLR_FRONT)
    {
      yaxis(DIR_FWD);
    }

    if(cmd == CMD_REV && ( clearance & CLR_BACK) != CLR_BACK)
    {
      yaxis(DIR_REV);
    }
      
    if(cmd == CMD_RIGHT)
    { 
      xaxis(DIR_RIGHT);
    }

    if(cmd == CMD_LEFT)
    {
      xaxis(DIR_LEFT);
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
      if(cmd == CMD_FWD && (clearance & CLR_FRONT) != CLR_FRONT)
      {
      digitalWrite(in1 , HIGH);
      digitalWrite(in3 , HIGH);
      delay(pul);
      digitalWrite(in1 , LOW);
      digitalWrite(in3 , LOW);
    }
  }

  }

  if(x == 1)
  {
    digitalWrite(in1, LOW);
    digitalWrite(in3, LOW);

    for(int pul = 0 ; pul<= del ; pul=pul+10)
    {
      if(cmd == CMD_REV && ( clearance & CLR_BACK) != CLR_BACK)
      {
      digitalWrite(in2 , HIGH);
      digitalWrite(in4 , HIGH);
      delay(pul);
      digitalWrite(in2 , LOW);
      digitalWrite(in4 , LOW);
    }
  }
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
  }
}

int M_Dist()
{

  int retVal = CLR_ALL_CLEAR;
  float  speed=0.034,time1, time2;
  double dist1, dist2;


  digitalWrite(trig1 , LOW);
  delayMicroseconds(2);
  digitalWrite(trig1 , HIGH);
  delayMicroseconds(10);

  time1 = pulseIn(echo1 , HIGH);

  digitalWrite(trig2 , LOW);
  delayMicroseconds(2);
  digitalWrite(trig2 , HIGH);
  delayMicroseconds(10);

  time2 = pulseIn(echo2 , HIGH);

  dist1 = (speed * time1)/2.0;
  dist2 = (speed * time2)/2.0;

  char str[100];
  sprintf(str,"Dist1: %d, Dist2: %d\n",(int)dist1,(int)dist2);
  Serial.print(str);

  Serial.print(dist1);
  Serial.print(dist2);

  if(dist1 <= SAFE_DIST )
  {
    retVal = retVal | CLR_FRONT;
  }

  if(dist2 <= SAFE_DIST )
  {
    retVal = retVal | CLR_BACK;
  }
  
  return retVal;
}

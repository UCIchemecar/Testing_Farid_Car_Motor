#include "DualMC33926MotorShield.h"
#include <PololuWheelEncoders.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_TSL2591.h"
DualMC33926MotorShield md;
Adafruit_TSL2591 tsl = Adafruit_TSL2591(2591);
void stopIfFault()
{
  if (md.getFault())
  {
    Serial.println("fault");
    while(1);
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Dual MC33926 Motor Shield");
  md.init();
   PololuWheelEncoders::init(3,5,6,11);
}

void loop()
{
  //adjust one of these two to balance out the car, the min value is 0, the max value is 400
   md.setM1Speed(370);//If M1 is too slow, increase this number, if too fast, decrease this number  
   md.setM2Speed(390);//If M2 is too slow, increase this number, if too fast, decrease this number
   static float total2=0;
  static float total1=0;
  static float oldTotal1;
  static int flag1=0;
  static int flag2=0;
  static int flag3=0;
  static int flag4=0;
  static int flag5=0;
  static int flag6=0;
  static int speed1;
  static int speed2;
  static float runTime=0;
  static float startTime=0;
  static int co;
  static signed int adjust=1;//adjustment to the speed everytime the loop is run
  static int counter=0;//count the total times the loop has been run
  static int lux;
  static int preLux=0;
  static long int count=0;
  static long timer1=0;//Counte until max is reached
  static long timer2=0;//Count until lux 30 is reached
  //static long testtime=27408;
  static long currentT;
  static float tagertRotate=1000;
    static int mode=0;
    static int t1=millis(); //t1 is the time it starts
  int j=PololuWheelEncoders::getCountsAndResetM2();
  int i=PololuWheelEncoders::getCountsAndResetM1();
  if(total1>0.01 && flag6==0)
  {
    startTime=millis();
    flag6=1;
  }
  
  if(flag6==1 && i!=0)
  {
    runTime=millis()-startTime;
    //runTime=runTime/1000.0;    
  }
  total2=total2+abs(j/3591.84);
  total1=total1+abs(i/3591.84);

  Serial.print(runTime/1000.0,4);
  Serial.print("      ");
  Serial.print(total1); Serial.print("    ");
  Serial.println(total2);
}

#include<Wire.h>
#define FSR1 A0
#define FSR2 A1
#define FSR3 A2



const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
 
int minVal=265;
int maxVal=402;
 
double x;
double y;
double z;
 
void setup(){
Wire.begin();
Wire.beginTransmission(MPU_addr);
Wire.write(0x6B);
Wire.write(0);
Wire.endTransmission(true);
Serial.begin(9600);
}
void loop(){

int analogReading0 = analogRead(FSR1);
analogReading0=map(analogReading0,0,1023,0,50);

int analogReading1 = analogRead(FSR2);
analogReading1=map(analogReading1,0,1023,0,50);

int analogReading2 = analogRead(FSR3);
analogReading2=map(analogReading2,0,1023,0,50);

Wire.beginTransmission(MPU_addr);
Wire.write(0x3B);
Wire.endTransmission(false);
Wire.requestFrom(MPU_addr,14,true);
AcX=Wire.read()<<8|Wire.read();
AcY=Wire.read()<<8|Wire.read();
AcZ=Wire.read()<<8|Wire.read();
int xAng = map(AcX,minVal,maxVal,-90,90);
int yAng = map(AcY,minVal,maxVal,-90,90);
int zAng = map(AcZ,minVal,maxVal,-90,90);
 
x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);
 
Serial.print("AngleX= ");
Serial.println(x);
 
Serial.print("AngleY= ");
Serial.println(y);
 
Serial.print("AngleZ= ");
Serial.println(z);


  Serial.print("Force sensor reading1 = ");
  Serial.print(analogReading0); 
   Serial.println("Kg");

   Serial.print("Force sensor reading2 = ");
  Serial.print(analogReading1); 
   Serial.println("Kg");

   Serial.print("Force sensor reading3 = ");
  Serial.print(analogReading2); 
   Serial.println("Kg");
Serial.println("-----------------------------------------");
delay(1000);
}
